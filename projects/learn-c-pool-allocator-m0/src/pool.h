/* 固定長ブロックのメモリプール（設計: docs/design.md）。
 * 領域は呼び出し側が渡す。動的確保、グローバル変数、libc を使わない。
 * 再入しない。割り込みなどと共有するときは、呼び出し側が排他で囲む。 */
#ifndef POOL_H
#define POOL_H

#include <stddef.h>

/* 除算命令が無いコア（Cortex-M0 / M0+
 * など）では、除算と剰余を使わない経路にする （libgcc
 * の補助関数に依存しない。docs/decisions.md の M0 対応の方針）。
 * 切り替えはビルド時。ARM で __ARM_FEATURE_IDIV が無ければ自動で選ぶ。
 * POOL_NO_HW_DIV を定義すると、どのコアでも（ホストのテストでも）選べる。
 * struct pool の配置が変わるので、pool.h を使うすべての翻訳単位で、同じ条件
 * （同じコア、同じ POOL_NO_HW_DIV）でコンパイルすること。 */
#if defined(POOL_NO_HW_DIV) ||                                                 \
    (defined(__ARM_ARCH) && !defined(__ARM_FEATURE_IDIV))
#define POOL_SOFT_DIV 1
#endif

/* 呼び出し側が置く（スタック、または呼び出し側の static）。
 * メンバは、pool_* 以外から書き換えない。
 *
 * 初期化の保証（設計。docs/design.md の 7 節）: struct pool は、次のどちらか。
 *   (a) 全バイトが 0（static 変数、または memset）: 未初期化。pool_alloc は
 * NULL、 pool_free と pool_check は POOL_ERR_ARG を返す。 (b) pool_init が
 * POOL_OK を返した後で、呼び出し側が書き換えていない:
 *       下の不変条件が成り立つ。pool_alloc と pool_free は、この不変条件を
 *       前提にして、再検査しない（pool_check は検査する）。
 * pool_init が失敗したとき、*p
 * は変更されない。初期化していない自動変数に失敗した pool_init
 * を呼んだ後は、(a) でも (b) でもないので、使ってはならない（戻り値を
 * 確認すること）。
 *
 * 不変条件（(b) のとき）:
 *   I1 base != NULL で、align の境界にある。
 *   I2 block_size >= sizeof(void *) で、align の倍数。
 *   I3 capacity >= 1 で、capacity * block_size は、buf
 * に収まる（オーバーフローしない）。 I4 free_head
 * は、空きブロックの単方向リストの先頭（空なら NULL）。 I5 （POOL_SOFT_DIV
 * のとき）block_size = d * 2^shift（d は奇数）で、inv * d = 1
 *      （2^ビット数を法とする）。 */
struct pool {
  unsigned char *base; /* ブロック領域の先頭（アライメント調整後） */
  size_t block_size; /* 丸めた後のブロックサイズ */
  size_t capacity;   /* ブロック数 */
  void *free_head;   /* 空きブロックの単方向リスト */
#ifdef POOL_SOFT_DIV
  size_t
      inv; /* block_size の奇数部の乗法の逆元（境界検査用。pool_init が設定） */
  size_t shift; /* block_size の 2 のべき乗部の指数 */
#endif
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

/* 構造体の不変条件（I1、I2 の下限、I3 の capacity >= 1）と、空きリストの整合
 * （範囲、境界、閉路なし）を検査する。O(ブロック数)。テスト・デバッグ用
 * （pool_alloc と pool_free が省いた検査を、ここでまとめて行う）。I5
 * は検査しない （フットプリントのため。pool_init
 * 直後の値と判定の結果は、テストで検証する）。
 * 未初期化（(a)）か、不変条件が壊れているときは POOL_ERR_ARG、リストが壊れて
 * いるときは POOL_ERR_CORRUPT。free_count が NULL
 * でなければ、空きブロック数を返す。 */
enum pool_status pool_check(const struct pool *p, size_t *free_count);

#endif
