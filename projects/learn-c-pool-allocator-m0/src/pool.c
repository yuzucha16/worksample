#include "pool.h"

#include <limits.h>
#include <stdint.h>

/* 除算命令が無いコア（Cortex-M0 / M0+ など）では、除算と剰余を使わない経路に
 * する（libgcc の補助関数に依存しない。docs/decisions.md の M0 対応の方針）。
 * 切り替えはビルド時。ARM で __ARM_FEATURE_IDIV が無ければ自動で選ぶ。
 * POOL_NO_HW_DIV を定義すると、どのコアでも（ホストのテストでも）選べる。 */
#if defined(POOL_NO_HW_DIV) ||                                                 \
    (defined(__ARM_ARCH) && !defined(__ARM_FEATURE_IDIV))
#define POOL_SOFT_DIV 1
#endif

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

/* room に入るブロック数。引き算を数える（O(ブロック数)。init が全ブロックに
 * 書くので、オーダーは変わらない）。 */
static size_t blocks_in(size_t room, size_t bsize) {
  size_t n = 0;
  while (room >= bsize) {
    room -= bsize;
    n++;
  }
  return n;
}

/* offset（< capacity * block_size）が、ブロックの境界か。ビットごとの剰余
 * （O(size_t のビット数)。一定時間）。bsize はバッファに収まる大きさで、
 * オブジェクトの大きさは PTRDIFF_MAX 以下なので、rem < bsize の左シフトは
 * あふれない。 */
static int on_boundary(size_t offset, size_t bsize) {
  size_t rem = 0;
  size_t i;

  for (i = sizeof(size_t) * CHAR_BIT; i > 0; i--) {
    rem = (rem << 1) | ((offset >> (i - 1)) & 1U);
    if (rem >= bsize) {
      rem -= bsize;
    }
  }
  return rem == 0;
}

/* capacity * block_size は、init で確認済みのバッファに収まる（オーバーフロー
 * しない）。 */
static int in_range(const struct pool *p, size_t offset) {
  return offset < p->capacity * p->block_size;
}

#else

static size_t blocks_in(size_t room, size_t bsize) {
  return room / bsize;
}

static int on_boundary(size_t offset, size_t bsize) {
  return offset % bsize == 0;
}

/* 乗算を避け、除算で比べる（capacity * block_size がオーバーフローしない）。 */
static int in_range(const struct pool *p, size_t offset) {
  return offset / p->block_size < p->capacity;
}

#endif

/* block が、プールのブロックの先頭か。 */
static enum pool_status locate(const struct pool *p, const void *block) {
  uintptr_t addr = (uintptr_t)block;
  uintptr_t base = (uintptr_t)p->base;
  uintptr_t offset;

  if (block == NULL || addr < base) {
    return POOL_ERR_PTR;
  }
  offset = addr - base;
  if (!in_range(p, offset) || !on_boundary(offset, p->block_size)) {
    return POOL_ERR_PTR;
  }
  return POOL_OK;
}

static int is_initialized(const struct pool *p) {
  return p != NULL && p->base != NULL && p->block_size >= sizeof(void *) &&
         p->capacity != 0;
}

enum pool_status pool_init(struct pool *p, void *buf, size_t buf_size,
                           size_t block_size, size_t align) {
  size_t bsize;
  size_t adjust;
  size_t capacity;
  size_t i;
  uintptr_t addr;
  uintptr_t mask;
  unsigned char *base;
  void *next = NULL;

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
  capacity = blocks_in(buf_size - adjust, bsize);
  if (capacity == 0) {
    return POOL_ERR_SIZE;
  }

  /* 末尾から先頭へ連結し、先頭のブロックが free_head
   * になる（昇順に取り出せる）。 */
  base = (unsigned char *)buf + adjust;
  for (i = capacity; i > 0; i--) {
    void *node = base + (i - 1) * bsize;
    node_set_next(node, next);
    next = node;
  }

  p->base = base;
  p->block_size = bsize;
  p->capacity = capacity;
  p->free_head = next;
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

  if (!is_initialized(p)) {
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
