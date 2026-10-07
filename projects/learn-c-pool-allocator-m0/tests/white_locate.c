/* ホワイトボックステスト:
 * ブロックの先頭の判定（is_block_offset）を、除算と剰余による
 * 参照の判定と突き合わせる。pool.c
 * を直接取り込み（リンクしない）、実際のバッファを 作らずに、大きな capacity や
 * block_size の境界を試す。除算なしの経路（乗法の逆元）と、
 * 除算の経路の、どちらでも同じ結果になること。 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "check.h"
#include "pool.c"

static int reference(size_t offset, size_t bsize, size_t cap) {
  return offset / bsize < cap && offset % bsize == 0;
}

/* 決定的な疑似乱数（固定シード）。 */
static uint64_t rng_next(uint64_t *s) {
  *s = *s * 6364136223846793005ULL + 1442695040888963407ULL;
  return *s >> 11;
}

static size_t rand_size(uint64_t *s) {
  return (size_t)((rng_next(s) << 32) ^ (rng_next(s) << 8) ^ rng_next(s));
}

int main(void) {
  uint64_t seed = 20261007u;
  size_t bsize;
  size_t ci;
  long cases = 0;

  for (bsize = 1; bsize <= 700; bsize++) {
    size_t max_cap = SIZE_MAX / bsize; /* capacity * block_size が収まる最大 */
    size_t caps[8] = {1, 2, 3, 7, 100, 1000, max_cap, max_cap - 1};

    for (ci = 0; ci < 8; ci++) {
      struct pool p = {0};
      size_t cap = caps[ci];
      size_t end;
      size_t o;
      int t;

      if (cap == 0) {
        continue;
      }
      p.block_size = bsize;
      p.capacity = cap;
      set_locator(&p);
      end = cap * bsize;

      /* 先頭付近を全オフセットで。 */
      for (o = 0; o < 20000 && o < end + 2000; o++) {
        CHECK(is_block_offset(&p, o) == reference(o, bsize, cap));
        cases++;
      }
      /* 末尾付近と、ブロックの先頭、ランダムな値。 */
      for (t = 0; t < 3000; t++) {
        size_t off = rand_size(&seed);
        if (t % 3 == 0) {
          off = end - (size_t)(rng_next(&seed) % 2000) +
                (size_t)(rng_next(&seed) % 3000);
        } else if (t % 3 == 1) {
          off = (size_t)(rng_next(&seed) % cap) * bsize;
          if (t % 2 == 0) {
            off += (size_t)(rng_next(&seed) % bsize);
          }
        }
        CHECK(is_block_offset(&p, off) == reference(off, bsize, cap));
        cases++;
      }
    }
  }
  printf("ok: white_locate (%ld cases)\n", cases);
  return 0;
}
