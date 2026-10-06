/* pool の単体テスト（観点は docs/design.md の 6 節）。
 * テストは制約（グローバル変数、libc
 * など）の対象外なので、実現のしやすさを優先する。 */
#include <stdalign.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "check.h"
#include "pool.h"

#define GUARD 16
#define GUARD_BYTE 0xA5

/* 前後に番兵つきのバッファ。プールが領域の外に書かないことを確かめる。 */
struct arena {
  alignas(max_align_t) unsigned char raw[GUARD + 1024 + GUARD];
};

static unsigned char *arena_body(struct arena *a) {
  return a->raw + GUARD;
}

static void arena_reset(struct arena *a) {
  memset(a->raw, GUARD_BYTE, sizeof a->raw);
}

static void arena_check_guards(const struct arena *a, size_t body) {
  size_t i;
  for (i = 0; i < GUARD; i++) {
    CHECK(a->raw[i] == GUARD_BYTE);
    CHECK(a->raw[GUARD + body + i] == GUARD_BYTE);
  }
}

static void test_init_args(void) {
  struct arena a;
  struct pool p;
  unsigned char tiny[4];

  arena_reset(&a);
  CHECK(pool_init(NULL, arena_body(&a), 1024, 16, 8) == POOL_ERR_ARG);
  CHECK(pool_init(&p, NULL, 1024, 16, 8) == POOL_ERR_ARG);
  CHECK(pool_init(&p, arena_body(&a), 1024, 0, 8) == POOL_ERR_ARG);
  CHECK(pool_init(&p, arena_body(&a), 1024, 16, 0) == POOL_ERR_ARG);
  CHECK(pool_init(&p, arena_body(&a), 1024, 16, 12) == POOL_ERR_ARG);
  CHECK(pool_init(&p, arena_body(&a), 1024, 16, 1) == POOL_ERR_ARG);
  CHECK(pool_init(&p, tiny, sizeof tiny, 16, 8) == POOL_ERR_SIZE);
  CHECK(pool_init(&p, arena_body(&a), 0, 16, 8) == POOL_ERR_SIZE);
  CHECK(pool_init(&p, arena_body(&a), 1024, SIZE_MAX, 8) == POOL_ERR_SIZE);
  CHECK(pool_init(&p, arena_body(&a), 1024, SIZE_MAX - 3, 8) == POOL_ERR_SIZE);
  arena_check_guards(&a, 1024);
}

static void test_init_failure_keeps_pool(void) {
  struct arena a;
  struct pool p;
  struct pool before;

  arena_reset(&a);
  CHECK(pool_init(&p, arena_body(&a), 1024, 16, 8) == POOL_OK);
  before = p;
  CHECK(pool_init(&p, arena_body(&a), 1024, 16, 3) == POOL_ERR_ARG);
  CHECK(memcmp(&p, &before, sizeof p) == 0);
}

static void test_init_invariants(void) {
  struct arena a;
  struct pool p;
  size_t n;

  arena_reset(&a);
  /* 1024 バイトを 16 バイトのブロックに分ける。先頭を 1
   * ずらして、調整分を作る。 */
  CHECK(pool_init(&p, arena_body(&a) + 1, 1023, 16, 8) == POOL_OK);
  CHECK(p.capacity > 0);
  CHECK(p.block_size == 16);
  CHECK((uintptr_t)p.base % 8 == 0);
  CHECK(p.base >= arena_body(&a) + 1);
  CHECK(pool_check(&p, &n) == POOL_OK);
  CHECK(n == p.capacity);
  CHECK(pool_check(&p, NULL) == POOL_OK);
  arena_check_guards(&a, 1024);
}

static void test_block_size_rounding(void) {
  struct arena a;
  struct pool p;

  arena_reset(&a);
  /* void * より小さい要求は、void * の大きさに切り上がる。 */
  CHECK(pool_init(&p, arena_body(&a), 1024, 1, alignof(void *)) == POOL_OK);
  CHECK(p.block_size == sizeof(void *));
  /* align の倍数に切り上がる。 */
  CHECK(pool_init(&p, arena_body(&a), 1024, 13, 8) == POOL_OK);
  CHECK(p.block_size == 16);
  CHECK(pool_init(&p, arena_body(&a), 1024, 33, 32) == POOL_OK);
  CHECK(p.block_size == 64);
  arena_check_guards(&a, 1024);
}

static void test_alignment_of_all_blocks(void) {
  static const size_t aligns[] = {8, 16, 32, 64};
  size_t ai;
  size_t shift;

  for (ai = 0; ai < sizeof aligns / sizeof aligns[0]; ai++) {
    for (shift = 0; shift < 8; shift++) {
      struct arena a;
      struct pool p;
      void *b;
      size_t count = 0;

      arena_reset(&a);
      CHECK(pool_init(&p, arena_body(&a) + shift, 1024 - shift, 20,
                      aligns[ai]) == POOL_OK);
      while ((b = pool_alloc(&p)) != NULL) {
        CHECK((uintptr_t)b % aligns[ai] == 0);
        CHECK((unsigned char *)b >= arena_body(&a) + shift);
        CHECK((unsigned char *)b + p.block_size <= arena_body(&a) + 1024);
        count++;
      }
      CHECK(count == p.capacity);
      arena_check_guards(&a, 1024);
    }
  }
}

static void test_exhaustion_and_lifo_reuse(void) {
  struct arena a;
  struct pool p;
  void *blocks[128];
  size_t i;
  size_t n;

  arena_reset(&a);
  CHECK(pool_init(&p, arena_body(&a), 1024, 16, 8) == POOL_OK);
  CHECK(p.capacity <= sizeof blocks / sizeof blocks[0]);
  for (i = 0; i < p.capacity; i++) {
    blocks[i] = pool_alloc(&p);
    CHECK(blocks[i] != NULL);
  }
  CHECK(pool_alloc(&p) == NULL);
  CHECK(pool_check(&p, &n) == POOL_OK && n == 0);

  /* 最後に返したブロックが、次に取り出される。 */
  CHECK(pool_free(&p, blocks[3]) == POOL_OK);
  CHECK(pool_free(&p, blocks[7]) == POOL_OK);
  CHECK(pool_alloc(&p) == blocks[7]);
  CHECK(pool_alloc(&p) == blocks[3]);
  CHECK(pool_alloc(&p) == NULL);
}

static void test_blocks_do_not_overlap(void) {
  struct arena a;
  struct pool p;
  unsigned char *blocks[128];
  size_t i;
  size_t j;

  arena_reset(&a);
  CHECK(pool_init(&p, arena_body(&a), 1024, 24, 8) == POOL_OK);
  for (i = 0; i < p.capacity; i++) {
    blocks[i] = pool_alloc(&p);
    CHECK(blocks[i] != NULL);
    memset(blocks[i], (int)(i + 1), p.block_size);
  }
  for (i = 0; i < p.capacity; i++) {
    for (j = 0; j < p.block_size; j++) {
      CHECK(blocks[i][j] == (unsigned char)(i + 1));
    }
  }
  arena_check_guards(&a, 1024);
}

static void test_free_rejects_invalid_pointers(void) {
  struct arena a;
  struct pool p;
  unsigned char *b;
  unsigned char other[64];
  size_t n;

  arena_reset(&a);
  CHECK(pool_init(&p, arena_body(&a), 1024, 16, 8) == POOL_OK);
  b = pool_alloc(&p);
  CHECK(b != NULL);

  CHECK(pool_free(&p, NULL) == POOL_ERR_ARG);
  CHECK(pool_free(NULL, b) == POOL_ERR_ARG);
  CHECK(pool_free(&p, b + 1) == POOL_ERR_PTR); /* ブロックの途中 */
  CHECK(pool_free(&p, b + 8) ==
        POOL_ERR_PTR); /* 境界は揃うが、ブロックの途中 */
  /* 配列の外へのポインタ演算は未定義なので、整数で作る。 */
  CHECK(pool_free(&p, (void *)((uintptr_t)p.base - p.block_size)) ==
        POOL_ERR_PTR);
  CHECK(pool_free(&p, p.base + p.capacity * p.block_size) == POOL_ERR_PTR);
  CHECK(pool_free(&p, other) == POOL_ERR_PTR);
  /* 失敗した free は、プールを変えない。 */
  CHECK(pool_check(&p, &n) == POOL_OK && n == p.capacity - 1);
  CHECK(pool_free(&p, b) == POOL_OK);
  CHECK(pool_check(&p, &n) == POOL_OK && n == p.capacity);
}

static void test_uninitialized_pool_is_rejected(void) {
  struct pool p;

  memset(&p, 0, sizeof p);
  CHECK(pool_alloc(&p) == NULL);
  CHECK(pool_free(&p, &p) == POOL_ERR_ARG);
  CHECK(pool_check(&p, NULL) == POOL_ERR_ARG);
  CHECK(pool_alloc(NULL) == NULL);
  CHECK(pool_check(NULL, NULL) == POOL_ERR_ARG);
}

static void test_check_detects_corruption(void) {
  struct arena a;
  struct pool p;
  void *self;
  void *outside = &a;

  arena_reset(&a);
  CHECK(pool_init(&p, arena_body(&a), 1024, 16, 8) == POOL_OK);

  /* 閉路: 先頭の空きブロックが、自分を指す。 */
  self = p.free_head;
  memcpy(self, &self, sizeof self);
  CHECK(pool_check(&p, NULL) == POOL_ERR_CORRUPT);

  /* 範囲外を指す。 */
  CHECK(pool_init(&p, arena_body(&a), 1024, 16, 8) == POOL_OK);
  memcpy(p.free_head, &outside, sizeof outside);
  CHECK(pool_check(&p, NULL) == POOL_ERR_CORRUPT);

  /* 先頭が範囲外。 */
  CHECK(pool_init(&p, arena_body(&a), 1024, 16, 8) == POOL_OK);
  p.free_head = &a.raw[GUARD + 1];
  CHECK(pool_check(&p, NULL) == POOL_ERR_CORRUPT);
}

/* 決定的な疑似乱数（固定シード）。 */
static uint32_t rng_next(uint32_t *s) {
  *s = *s * 1664525u + 1013904223u;
  return *s >> 8;
}

#define MODEL_BLOCKS 64
#define MODEL_BLOCK_SIZE 24

/* 確保と解放を繰り返し、テスト側のモデル（使用中フラグ）と突き合わせる。
 * モデルは、二重解放を起こさないことと、使用中のブロックの内容が保たれることを保証する。
 */
static void test_model_random_operations(void) {
  alignas(max_align_t) unsigned char buf[MODEL_BLOCKS * MODEL_BLOCK_SIZE];
  struct pool p;
  unsigned char *owner_of[MODEL_BLOCKS] = {0};
  unsigned char tag[MODEL_BLOCKS] = {0};
  uint32_t seed = 12345u;
  size_t used = 0;
  size_t n;
  size_t step;
  size_t i;

  CHECK(pool_init(&p, buf, sizeof buf, MODEL_BLOCK_SIZE, 8) == POOL_OK);
  CHECK(p.capacity == MODEL_BLOCKS);

  for (step = 0; step < 20000; step++) {
    int want_alloc = (rng_next(&seed) & 1u) != 0;
    if (want_alloc) {
      unsigned char *b = pool_alloc(&p);
      if (used == p.capacity) {
        CHECK(b == NULL);
      } else {
        size_t idx;
        CHECK(b != NULL);
        idx = (size_t)(b - p.base) / p.block_size;
        CHECK(idx < p.capacity);
        CHECK(owner_of[idx] == NULL); /* 使用中のブロックを、また渡していない */
        owner_of[idx] = b;
        tag[idx] = (unsigned char)(rng_next(&seed) | 1u);
        memset(b, tag[idx], p.block_size);
        used++;
      }
    } else if (used > 0) {
      size_t idx = rng_next(&seed) % p.capacity;
      size_t k;
      for (k = 0; k < p.capacity && owner_of[idx] == NULL; k++) {
        idx = (idx + 1) % p.capacity;
      }
      CHECK(owner_of[idx] != NULL);
      for (i = 0; i < p.block_size; i++) { /* 使用中の内容が保たれている */
        CHECK(owner_of[idx][i] == tag[idx]);
      }
      CHECK(pool_free(&p, owner_of[idx]) == POOL_OK);
      owner_of[idx] = NULL;
      used--;
    }
    if (step % 500 == 0) {
      CHECK(pool_check(&p, &n) == POOL_OK);
      CHECK(n == p.capacity - used);
    }
  }

  for (i = 0; i < p.capacity; i++) {
    if (owner_of[i] != NULL) {
      CHECK(pool_free(&p, owner_of[i]) == POOL_OK);
    }
  }
  CHECK(pool_check(&p, &n) == POOL_OK);
  CHECK(n == p.capacity);
}

int main(void) {
  test_init_args();
  test_init_failure_keeps_pool();
  test_init_invariants();
  test_block_size_rounding();
  test_alignment_of_all_blocks();
  test_exhaustion_and_lifo_reuse();
  test_blocks_do_not_overlap();
  test_free_rejects_invalid_pointers();
  test_uninitialized_pool_is_rejected();
  test_check_detects_corruption();
  test_model_random_operations();
  puts("ok: test_pool");
  return 0;
}
