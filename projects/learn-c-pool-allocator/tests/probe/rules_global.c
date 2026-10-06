/* 意図した違反: 初期値つきの .data（g_data）と、ゼロ初期化のグローバル変数（g_zero）。tools/check-rules.sh が検出することを確認する（make probe）。 */
int g_data = 1;
int g_zero;

int next(void) { return g_data + g_zero; }
