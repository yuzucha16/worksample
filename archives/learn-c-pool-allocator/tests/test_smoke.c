/* 骨組みの確認用。テストの仕組み（ビルド、実行、失敗の検出）が動くことだけを見る。
 */
#include <stdio.h>

#include "check.h"

static void test_harness_runs(void) {
  int x = 1 + 1;
  CHECK(x == 2);
}

int main(void) {
  test_harness_runs();
  puts("ok: test_smoke");
  return 0;
}
