/* 意図した違反: 動的確保。tools/check-rules.sh が検出することを確認する（make probe）。 */
#include <stdlib.h>

void *get(size_t n) { return malloc(n); }
