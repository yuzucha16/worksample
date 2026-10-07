#include "pool.h"

#include <limits.h>
#include <stdint.h>

/* 空きブロックの先頭に、次の空きブロックへのポインタを置く（侵入型リスト）。
 * バッファの宣言型は呼び出し側の任意なので、strict aliasing の対象になる。
 * ビルドで -fno-strict-aliasing を付ける前提（docs/design.md の判断 E1）。 */
static void node_set_next(void *node, void *next) {
  *(void **)node = next;
}

static void *node_get_next(const void *node) {
  return *(void *const *)node;
}

static int is_pow2(size_t v) {
  return v != 0 && (v & (v - 1)) == 0;
}

/* v を align（2 のべき乗）の倍数に切り上げる。オーバーフローするとき 0 を返す。
 */
static int round_up_size(size_t v, size_t align, size_t *out) {
  size_t add = align - 1;
  if (v > SIZE_MAX - add) {
    return 0;
  }
  *out = (v + add) & ~add;
  return 1;
}

#ifdef POOL_SOFT_DIV

/* 奇数 d の、2^ビット数 を法とする乗法の逆元（ニュートン法。乗算だけ。init
 * でだけ使う）。 */
static size_t inverse_odd(size_t d) {
  size_t x = d; /* d * d = 1 (mod 8): 下位 3 ビットが正しい */
  size_t i;

  for (i = 3; i < sizeof(size_t) * CHAR_BIT; i *= 2) {
    x *= 2 - d * x;
  }
  return x;
}

/* p->block_size（1 以上）から、境界検査に使う shift と inv を設定する。 */
static void set_locator(struct pool *p) {
  size_t odd = p->block_size;
  size_t shift = 0;

  while ((odd & 1U) == 0) {
    odd >>= 1;
    shift++;
  }
  p->shift = shift;
  p->inv = inverse_odd(odd);
}

/* offset が、ブロックの先頭か（範囲内で、block_size の倍数）。
 * block_size = d * 2^shift（d は奇数）とすると、offset が block_size の倍数で
 * あることは、下位 shift ビットが 0 で、(offset >> shift) * inv(d) < capacity
 * で あることと同値（乗法の逆元による可除性の判定。範囲検査も兼ねる。除算も、
 * 剰余のループも使わない）。同値は、capacity * block_size が 2^ビット数 以下
 * （init で確認済み）であることによる。 */
static int is_block_offset(const struct pool *p, size_t offset) {
  if ((offset & (((size_t)1 << p->shift) - 1)) != 0) {
    return 0;
  }
  return (offset >> p->shift) * p->inv < p->capacity;
}

/* base から room バイトを、bsize バイトのブロックに分けて連結する（先頭が
 * base。昇順に取り出せる）。ブロック数を返す（room が bsize 未満なら、何も書か
 * ずに 0）。個数を数える引き算と連結を、1 つのループで行う（O(ブロック数)）。
 */
static size_t link_blocks(unsigned char *base, size_t room, size_t bsize) {
  size_t n = 0;
  unsigned char *node = base;

  if (room < bsize) {
    return 0;
  }
  for (;;) {
    room -= bsize;
    n++;
    if (room < bsize) {
      break;
    }
    node_set_next(node, node + bsize);
    node += bsize;
  }
  node_set_next(node, NULL);
  return n;
}

#else

static void set_locator(struct pool *p) {
  (void)p;
}

static int is_block_offset(const struct pool *p, size_t offset) {
  return offset / p->block_size < p->capacity && offset % p->block_size == 0;
}

static size_t link_blocks(unsigned char *base, size_t room, size_t bsize) {
  size_t capacity = room / bsize;
  size_t i;
  void *next = NULL;

  /* 末尾から先頭へ連結し、先頭のブロックが base になる（昇順に取り出せる）。 */
  for (i = capacity; i > 0; i--) {
    void *node = base + (i - 1) * bsize;
    node_set_next(node, next);
    next = node;
  }
  return capacity;
}

#endif

/* block が、プールのブロックの先頭か。 */
static enum pool_status locate(const struct pool *p, const void *block) {
  uintptr_t addr = (uintptr_t)block;
  uintptr_t base = (uintptr_t)p->base;

  if (block == NULL || addr < base || !is_block_offset(p, addr - base)) {
    return POOL_ERR_PTR;
  }
  return POOL_OK;
}

/* 未初期化（全バイト 0）を弾くだけ。(b) の不変条件は、pool_init が保証し、ここ
 * では再検査しない（pool.h の「初期化の保証」。検査は pool_check）。 */
static int is_initialized(const struct pool *p) {
  return p != NULL && p->base != NULL;
}

enum pool_status pool_init(struct pool *p, void *buf, size_t buf_size,
                           size_t block_size, size_t align) {
  size_t bsize;
  size_t adjust;
  size_t capacity;
  uintptr_t addr;
  uintptr_t mask;
  unsigned char *base;

  if (p == NULL || buf == NULL || block_size == 0 || !is_pow2(align) ||
      align < _Alignof(void *)) {
    return POOL_ERR_ARG;
  }
  bsize = block_size < sizeof(void *) ? sizeof(void *) : block_size;
  if (!round_up_size(bsize, align, &bsize)) {
    return POOL_ERR_SIZE;
  }
  /* buf の先頭を align に切り上げる。切り捨てた分（adjust）は使わない。 */
  addr = (uintptr_t)buf;
  mask = (uintptr_t)align - 1;
  if (addr > UINTPTR_MAX - mask) {
    return POOL_ERR_SIZE;
  }
  adjust = (size_t)(((addr + mask) & ~mask) - addr);
  if (adjust >= buf_size) {
    return POOL_ERR_SIZE;
  }
  base = (unsigned char *)buf + adjust;
  capacity = link_blocks(base, buf_size - adjust, bsize);
  if (capacity == 0) {
    return POOL_ERR_SIZE;
  }

  p->base = base;
  p->block_size = bsize;
  p->capacity = capacity;
  p->free_head = base;
  set_locator(p);
  return POOL_OK;
}

void *pool_alloc(struct pool *p) {
  void *block;

  if (!is_initialized(p) || p->free_head == NULL) {
    return NULL;
  }
  block = p->free_head;
  p->free_head = node_get_next(block);
  return block;
}

enum pool_status pool_free(struct pool *p, void *block) {
  enum pool_status status;

  if (!is_initialized(p) || block == NULL) {
    return POOL_ERR_ARG;
  }
  status = locate(p, block);
  if (status != POOL_OK) {
    return status;
  }
  node_set_next(block, p->free_head);
  p->free_head = block;
  return POOL_OK;
}

enum pool_status pool_check(const struct pool *p, size_t *free_count) {
  const void *node;
  size_t n = 0;

  if (!is_initialized(p) || p->block_size < sizeof(void *) ||
      p->capacity == 0) {
    return POOL_ERR_ARG;
  }
  for (node = p->free_head; node != NULL; node = node_get_next(node)) {
    /* 空きブロックは capacity 個まで。超えたら閉路か重複。 */
    if (n >= p->capacity || locate(p, node) != POOL_OK) {
      return POOL_ERR_CORRUPT;
    }
    n++;
  }
  if (free_count != NULL) {
    *free_count = n;
  }
  return POOL_OK;
}
