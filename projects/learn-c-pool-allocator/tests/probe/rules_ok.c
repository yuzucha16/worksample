/* 許可される例（対照）: static const（.rodata）と、グローバルでないゼロ初期化（.bss）。tools/check-rules.sh が通ることを確認する（make probe）。 */
static const int k_limit = 8;

int next(void) {
  static int n;
  return (++n < k_limit) ? n : 0;
}
