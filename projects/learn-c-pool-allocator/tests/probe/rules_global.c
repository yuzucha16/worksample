/* 意図した違反: グローバル変数と、static のローカル変数。tools/check-rules.sh が検出することを確認する（make probe）。 */
int g_counter = 1;

int next(void) {
  static int n;
  return ++n + g_counter;
}
