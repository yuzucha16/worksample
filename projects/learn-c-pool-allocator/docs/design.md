# 設計（design）— 固定長ブロックのメモリプール

状態: **提案（未承認）**。2026-10-06。承認した項目だけ、`docs/decisions.md` に決定として移し、実装に入る。前提は、組込み領域（ユーザーは組込みエンジニア）、`docs/coding-rules.md` の制約（`src/` のみ: 動的確保なし、グローバル変数なし、初期値つき `.data` を減らす、再帰なし）。

## 1. 要求（制約から導いたもの）

| 要求 | 出どころ |
|---|---|
| `malloc` を使わない。領域は呼び出し側が渡す | 動的確保の禁止 |
| ライブラリ内に状態を持たない（すべて構造体） | グローバル変数の禁止 |
| `.data` を増やさない。初期値は実行時に設定する | 初期値つき `.data` の削減 |
| `alloc` と `free` が一定時間（O(1)）。断片化しない | 組込みの時間の決定性（固定長ブロックの利点） |
| 起動が軽い（初期化でバッファを走査・書き込みしない） | 起動を楽にする目的 |
| 余計な ROM・RAM を使わない（ブロックごとのヘッダなし） | フットプリント |
| libc に依存しない（`src/` は freestanding） | 提案。組込みで libc が使えない・使いたくない場合がある（下の判断 C） |

## 2. API（`src/pool.h`）

```c
struct pool {              /* 呼び出し側が置く（スタック、または呼び出し側の static） */
  unsigned char *base;     /* ブロック領域の先頭（アライメント調整後） */
  size_t block_size;       /* 丸めた後のブロックサイズ */
  size_t capacity;         /* ブロック数 */
  size_t carved;           /* これまでに領域から切り出したブロック数（高水位） */
  void *free_head;         /* 解放されたブロックの単方向リスト */
};

enum pool_status { POOL_OK = 0, POOL_ERR_ARG, POOL_ERR_SIZE, POOL_ERR_PTR };

enum pool_status pool_init(struct pool *p, void *buf, size_t buf_size,
                           size_t block_size, size_t align);
void *pool_alloc(struct pool *p);                    /* 空きが無ければ NULL */
enum pool_status pool_free(struct pool *p, void *block);
enum pool_status pool_check(const struct pool *p);   /* 不変条件の検査（デバッグ・テスト用。O(n)） */
size_t pool_capacity(const struct pool *p);
```

- すべて、`p` を引数で受ける。グローバルも `static` の状態も持たない。
- 失敗は、戻り値（`pool_status`）か `NULL`。`assert` と `abort` は使わない（libc 依存を避け、呼び出し側が処理を決める）。
- スレッド・割り込み: 再入しない。割り込みと共有するときは、呼び出し側が排他（割り込み禁止など）で囲む。この Project の範囲外（README）。ヘッダに明記する。

## 3. メモリレイアウト

```
buf（呼び出し側）
 │ ← 先頭を align に切り上げる（切り捨てた分は使わない）
 ▼
 base ┌──────────┬──────────┬──────────┬─ ─ ─ ─┐
      │ block 0  │ block 1  │ block 2  │  ...  │  capacity 個、block_size ずつ隙間なし
      └──────────┴──────────┴──────────┴─ ─ ─ ─┘
      ◀─ carved ─▶ ◀── 未使用（一度も書いていない） ──▶
```

- **ブロックサイズ**: `block_size` を `max(要求, sizeof(void *))` にし、`align` の倍数に切り上げる。解放されたブロックは、先頭の `sizeof(void *)` バイトに、次の空きブロックへのポインタを置く（侵入型リスト）。使用中のブロックは、全体が利用者のもの。**ブロックごとのヘッダはなく、オーバーヘッドは 0**。
- **容量**: `capacity = (buf_size - 先頭の調整分) / block_size`。0 なら `POOL_ERR_SIZE`。
- **`pool_init` はバッファに書かない**（判断 A）。`carved = 0`、`free_head = NULL` を構造体に設定するだけで、O(1)。バッファが未初期化（`.noinit` など）でも、起動時にゼロクリアや連結の時間がかからない。
- **`pool_alloc`**: `free_head` があればそれを取る。無ければ `carved < capacity` のときに、`base + carved * block_size` を切り出して `carved` を進める。どちらも無ければ `NULL`。O(1)。
- **`pool_free`**: ブロックを `free_head` に積む（LIFO。O(1)）。範囲外・非整列のポインタは `POOL_ERR_PTR`（O(1) の検査: `base` 以上、`base + carved * block_size` 未満、オフセットが `block_size` の倍数）。二重解放は、O(1) では検出できない（判断 B）。

## 4. 判断が要る点

### 判断 A: 初期化の方式

| 案 | 内容 | 利点 | 欠点 |
|---|---|---|---|
| **A1 遅延切り出し（推奨）** | 上の設計。`pool_init` は構造体だけ設定 | 起動が O(1)。バッファに書かない。未使用領域のページ・RAM に触れない | `alloc` の分岐が1つ増える。構造体が `carved` の分だけ大きい |
| A2 全ブロックを連結 | `pool_init` で全ブロックを走査してリストにする | `alloc` が単純（リストの先頭を取るだけ） | 起動が O(capacity) で、バッファ全体に書く。起動を楽にする目的に反する |

### 判断 B: 不正な `free` の検出

| 案 | 内容 | 利点 | 欠点 |
|---|---|---|---|
| **B1 O(1) の範囲検査 + `pool_check`（推奨）** | `free` は範囲・整列だけ検査。二重解放は `pool_check`（リストの走査）で、テスト・デバッグ時に検出 | 実行時間が一定。製品の ROM・RAM が増えない | 製品の実行時には、二重解放を検出しない（呼び出し側の責任） |
| B2 常時、二重解放も検出 | `free` で空きリストを走査 | 安全 | O(n)。組込みの時間の決定性を失う |
| B3 ビットマップ | 使用中のビットを、呼び出し側が渡す領域に持つ | O(1) で二重解放も検出 | RAM が増える。API が複雑になる |

### 判断 C: libc への依存

提案: `src/` は libc に依存しない（`nm -u` の結果が空）。`<stddef.h>` `<stdint.h>` `<stdalign.h>` だけを使い、`memcpy` `memset` `assert` `printf` は使わない。検査は `check-rules.sh` に足す（未定義シンボルが1つでもあれば失敗）。理由: 組込みでは、libc がリンクされない・使えない構成がある。この Project のテストは libc を使ってよい（`tests/` は制約の対象外）。

### 判断 D: ターゲットの前提

ホスト（WSL の x86-64、64bit）でテストするが、組込みのターゲットは 32bit のことが多い。ポインタと `size_t` の幅に依存しない書き方にする（`uintptr_t` で計算、固定幅に固定しない）。32bit のビルド確認（`-m32`）は、WSL に 32bit ライブラリが無い（未確認）ので、いまは行わない。ターゲットを教えてもらえれば、前提（ワード幅、アライメント）を明記する。

## 5. 実装の初期値（上の判断を承認した後に使う）

- 型: サイズと個数は `size_t`、アドレスの計算は `uintptr_t`。ポインタ ↔ 整数の変換は、アライメント調整を行う1つの `static` 関数に閉じ込める（MISRA C のポインタ変換の規則では、逸脱の記録が要る箇所。この Project は MISRA 準拠を目標にはしない。必要なら言ってほしい）。
- `align` は2のべき乗で、`sizeof(void *)` 以上（リンクを置くため）。違えば `POOL_ERR_ARG`。
- 整数のオーバーフロー: `capacity * block_size` などの乗算は、オーバーフローを検査してから行う（UBSan の対象にもなる）。
- 名前は `pool_` 接頭辞、`struct pool`（typedef なし）。公開は `pool.h` だけ。内部は `static`。
- 反復だけを使う（再帰なし）。

## 6. テストの方針（テストは実現のしやすさを優先。`tests/test_pool.c`）

- バッファは、テストの関数内のスタック配列（`_Alignas(max_align_t) unsigned char buf[N]`）。ASan が、スタック配列の範囲外への書き込みを検出する（プールが `buf` の外に書かないことの検証になる）。
- 観点: 引数の検証（`NULL`、小さすぎるバッファ、不正な `align`）、すべてのブロックが整列していること、`capacity` 個を取ったあとの枯渇（`NULL`）、ブロックが重ならないこと（個別のパターンを書いて検証）、`free` の再利用（LIFO）、範囲外・非整列の `free`（`POOL_ERR_PTR`）、`pool_check` による二重解放の検出、**`pool_init` がバッファに書かないこと**（`0xA5` で埋めて、`init` 後に変化が無いことを確認）。
- フットプリント: `make size` で、`src/*.o`（`-Os`、サニタイザなし）の `.text` `.data` `.bss` を表示する。`.data` が 0 のことを、目標にして記録する。
