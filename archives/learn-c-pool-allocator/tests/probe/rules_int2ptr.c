/* 意図した違反: 整数演算の値をポインタとして扱う。tools/check-rules.sh が検出することを確認する（make probe）。 */
#include <stddef.h>
#include <stdint.h>

void *next_block(void *base, size_t offset) {
  return (void *)((uintptr_t)base + offset);
}
