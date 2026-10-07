/* 意図した違反: グローバルでないが、初期値つきの .data（static の初期値つき変数）。tools/check-rules.sh が検出することを確認する（make probe）。 */
int next(void) {
  static int n = 5;
  return ++n;
}
