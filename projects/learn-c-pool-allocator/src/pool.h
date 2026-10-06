/* 固定長ブロックのメモリプール（設計: docs/design.md）。
 * 領域は呼び出し側が渡す。動的確保、グローバル変数、libc を使わない。
 * 再入しない。割り込みなどと共有するときは、呼び出し側が排他で囲む。 */
#ifndef POOL_H
#define POOL_H

#include <stddef.h>

/* 呼び出し側が置く（スタック、または呼び出し側の static）。
 * メンバは、pool_* 以外から書き換えない。 */
struct pool {
  unsigned char *base; /* ブロック領域の先頭（アライメント調整後） */
  size_t block_size; /* 丸めた後のブロックサイズ */
  size_t capacity;   /* ブロック数 */
  void *free_head;   /* 空きブロックの単方向リスト */
};

enum pool_status {
  POOL_OK = 0,
  POOL_ERR_ARG, /* 引数が不正（NULL、align が 2 のべき乗でない、など） */
  POOL_ERR_SIZE, /* バッファが小さすぎる、またはサイズの計算がオーバーフロー */
  POOL_ERR_PTR,  /* このプールのブロックではないポインタ */
  POOL_ERR_CORRUPT /* 空きリストが壊れている（pool_check のみ） */
};

/* buf の buf_size バイトを、block_size
 * バイトのブロックに分けて使えるようにする。
 * 全ブロックを空きリストに連結する（buf 全体に書く）。O(ブロック数)。
 * align: 返すブロックの先頭の境界。2 のべき乗で、void * の境界以上。
 * block_size は、void * の大きさ以上、align の倍数に切り上げる。
 * 失敗したとき、*p は変更しない。 */
enum pool_status pool_init(struct pool *p, void *buf, size_t buf_size,
                           size_t block_size, size_t align);

/* ブロックを1つ取り出す。空きが無ければ NULL。O(1)。
 * 返すブロックの内容は不定（前の利用者の値が残る）。 */
void *pool_alloc(struct pool *p);

/* ブロックを返す。O(1)。範囲・境界を検査し、このプールのブロックでなければ
 * POOL_ERR_PTR（何も変更しない）。二重解放は検出しない（呼び出し側の責務）。 */
enum pool_status pool_free(struct pool *p, void *block);

/* 空きリストの整合（範囲、境界、閉路なし）を検査する。O(ブロック数)。
 * テスト・デバッグ用。free_count が NULL でなければ、空きブロック数を返す。 */
enum pool_status pool_check(const struct pool *p, size_t *free_count);

#endif
