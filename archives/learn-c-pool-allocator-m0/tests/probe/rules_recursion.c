/* 意図した違反: 直接の再帰（fact）と、相互再帰（ping と pong）。tools/check-rules.sh が検出することを確認する（make probe）。 */
static unsigned fact(unsigned n) { return n <= 1 ? 1 : n * fact(n - 1); }

static int ping(int n);
static int pong(int n) { return n <= 0 ? 0 : ping(n - 1); }
static int ping(int n) { return n <= 0 ? 0 : pong(n - 1); }

unsigned api(unsigned n) { return fact(n) + (unsigned)ping((int)n); }
