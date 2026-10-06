/* 意図した違反: libc への依存（memset と strlen）。tools/check-rules.sh が検出することを確認する（make probe）。 */
#include <stddef.h>
#include <string.h>

size_t fill(char *buf, size_t n) {
  memset(buf, 0, n);
  return strlen(buf);
}
