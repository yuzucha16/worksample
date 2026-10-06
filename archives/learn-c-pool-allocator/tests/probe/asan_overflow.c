/* 意図したバグ: ヒープの範囲外書き込み。AddressSanitizer が検出して非ゼロで終わることを確認する（make probe）。 */
#include <stdlib.h>

int main(void) {
  char *p = malloc(8);
  p[8] = 1;
  free(p);
  return 0;
}
