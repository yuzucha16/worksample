/* 意図したバグ: 符号付き整数のオーバーフロー。UBSan が検出して非ゼロで終わることを確認する（make probe）。
 * 検出されなければ終了コード 0 で終わる（終了コードが検出の有無だけで決まるようにしてある）。 */
#include <limits.h>

int main(int argc, char **argv) {
  (void)argv;
  volatile int x = INT_MAX - 1 + argc; /* argc >= 1 なので INT_MAX */
  x = x + 1;                           /* オーバーフロー */
  return 0;
}
