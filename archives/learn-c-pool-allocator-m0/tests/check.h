/* テスト用の最小のアサーション。失敗したら、場所と式を出して終了コード 1
 * で終わる。 */
#ifndef CHECK_H
#define CHECK_H

#include <stdio.h>
#include <stdlib.h>

#define CHECK(cond)                                                            \
  do {                                                                         \
    if (!(cond)) {                                                             \
      fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond);          \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)

#endif
