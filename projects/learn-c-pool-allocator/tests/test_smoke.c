/* 骨組みの確認用。テストの仕組み（ビルド、実行、失敗の検出）が動くことだけを見る。
 * アロケータの実装ができたら、tests/test_pool.c を足す。 */
#include <stdio.h>
#include <stdlib.h>

#define CHECK(cond)                                                            \
  do {                                                                         \
    if (!(cond)) {                                                             \
      fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond);          \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)

static void test_harness_runs(void) {
  int x = 1 + 1;
  CHECK(x == 2);
}

int main(void) {
  test_harness_runs();
  puts("ok: test_smoke");
  return 0;
}
