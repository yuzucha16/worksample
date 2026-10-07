# コーディングルールとチェック（coding-rules）

この Project の実装で、私（AI）が暗黙に使っていたルールを明示し、ユーザーが承認したものを規則にしたもの。決定の経緯は `docs/decisions.md`。**状態の凡例**: 決定 = ユーザーが明示または承認（2026-10-06。暫定。見直し日 2026-10-20）、事実 = 確認済み、提案 = 未承認、AI の解釈 = ユーザーの指示を AI が読み解いた点（確認待ち）。

## 1. 機械チェックの一覧（`make check`）

| チェック | 内容 | 状態 | 根拠・確認 |
|---|---|---|---|
| コンパイラの警告 | `-std=c11 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wvla -Wstrict-prototypes -Wmissing-prototypes -Werror` | 決定 | `Makefile`。警告はエラー |
| 実行時の検査 | AddressSanitizer + UBSan（`-fno-sanitize-recover=undefined`） | 決定 | `make test` |
| 静的解析 | `gcc -fanalyzer`（`make analyze`） | 決定 | gcc 13.3。誤検知があれば、その箇所を記録する |
| 書式 | `clang-format`（`.clang-format`。`make format-check`） | 決定。有効（clang-format 18.1.3） | ユーザーの報告（2026-10-06）。導入後の最初の `make check` で、手で揃えたマクロの `\` を指摘し、`make format` で直した |
| 制約（.data・グローバル変数・動的確保・再帰・整数からのポインタ） | `tools/check-rules.sh`（`nm` と呼び出しグラフでオブジェクトを検査。**`src/` のみ**） | 決定 | 下の「制約」 |
| 改行・文字コード | `tools/check-rules.sh`（CR、BOM、UTF-8 を検査。テストも含む） | 決定 | 下の「書式」 |
| ARM の libc 非依存 | `make check-arm`（Cortex-M0 / M0+ / M3 / M4 向けに、未定義シンボルが無いこと。libgcc の補助関数を含む） | 決定。OK（事実。2026-10-07） | M0 / M0+ は、除算を使わない経路を自動で選ぶ（`docs/decisions.md`）。以前の `__aeabi_uidiv` 依存は解消した |
| 除算なしの経路の検証 | `make test-soft` `test-soft-o2`（ホストで `POOL_NO_HW_DIV`）、`make test-white` `test-white-soft`（`tests/white_*.c`。ブロックの先頭の判定を、参照と大量に突き合わせる） | 決定 | 設計は `docs/design.md` の 7 節 |
| 最適化への依存 | `make test-o2`（`-O2` でも同じテストを実行） | 決定 | 判断 E1（`-fno-strict-aliasing`）の確認用 |
| ビルドフラグ | `-fno-strict-aliasing`（判断 E1） | 決定 | `Makefile`。製品のビルドにも同じフラグが要る |
| フットプリント | `make size`（ホスト）、`make size-arm`（Cortex-M） | 事実（下の表） | 目標は `.data` が 0（達成） |
| 検査の検査 | `make probe`（意図したバグ・違反が検出され、許可される例が通ること） | 事実 | ASan、UBSan、グローバル変数、初期値つき `.data`、許可される例、`malloc`、libc 依存、整数からのポインタ、再帰、CRLF、BOM を確認（2026-10-06） |
| `cppcheck` `clang-tidy` | **導入しない**（今回） | 決定 | ユーザーの選択。必要になれば再検討 |

linter（静的解析ツール）は、gcc の `-fanalyzer` だけ。フォーマッタは `clang-format`。

**フットプリント（バイト。`-Os`、freestanding、`pool.c` のみ。確認: 2026-10-06）**

| 対象 | `.text` | `.data` | `.bss` | 備考 |
|---|---|---|---|---|
| ホスト x86-64 | 633 | 0 | 0 | 参考値 |
| Cortex-M3 / M4 | 280 | 0 | 0 | ハードウェア除算。2026-10-07 の速度のチューニングで 288 から減った（`pool_alloc` / `pool_free` の検査の削減と、初期化ループの整理） |
| Cortex-M0 / M0+ | 352 | 0 | 0 | 除算を使わない経路（2026-10-07、`arm-none-eabi-size`）。速度のチューニング前は 360、前の Project の「現状」は 612（libgcc 込み）、F1 の試作は 378。`struct pool` は、この経路で 8 バイト増える（`inv` `shift`） |

## 2. 書式（決定）

- インデントは2スペース、タブなし。1行は80桁以内。ただし `Makefile` のレシピはタブ（make の仕様）。
- 改行コードは LF、文字コードは UTF-8（BOM なし）、ファイル末尾に改行。（値は、リポジトリの `.gitattributes`（`eol=lf`）に合わせて AI が補った。違えば指示をもらう）
- コメントは日本語。ファイルの先頭に目的を書く。
- 識別子は `snake_case`、マクロは大文字。テスト関数は `static void test_<観点>(void)`。
- `main` は `int main(void)`。使わない引数は `(void)argv;`。複数文のマクロは `do { ... } while (0)`。
- `clang-format` は、**一貫性のためでなく、コードリーディングのコストを下げるため**に使う（ユーザーの意図）。整形の設定は読みやすさを優先し、`.clang-format` に置く。
- テストは `tests/test_*.c`（`Makefile` が自動で見つける）。失敗は `exit(1)`、成功は `ok: <名前>` を出して終了コード 0。サニタイザの試験（`tests/probe/`）は、**終了コードが検出の有無だけで決まる**ようにする。

## 3. 制約（決定。暫定）

**前提と範囲（ユーザーの回答。2026-10-06）**: ユーザーは組込み領域のエンジニアで、制約は組込み用途のため。**適用範囲は `src/` のみ**。テストコードは、実現のしやすさを優先する（グローバル変数、`malloc`、`static` の初期値つき変数を使ってよい）。**MISRA C への準拠は、この Project の目標にしない**（ユーザーの指示）。

| 制約 | 検査 | 設計への影響 |
|---|---|---|
| 初期値つきの `.data` を減らす（目的: フットプリントの削減） | `check-rules.sh`（`D` `d` を検出。`static const` は `.rodata` なので許可） | 初期値のある変数を作らない。定数は `const`。初期値が要る状態は、実行時に `pool_init` で設定する |
| グローバル変数の禁止 | 同上（外部リンケージの変数 `B` `C` `G` `S` を検出） | プールの状態は、すべて構造体に持たせて、呼び出し側が渡す |
| グローバルでないゼロ初期化の `.bss` は許可（ユーザーの回答: 「グローバルでなければとりあえず OK」） | 検査しない（小文字の `b` は許可） | 限界: ファイルスコープの `static` 変数も `b` なので許可になる。`nm` では、関数内の `static` と区別できない。使わない方針とし、レビューで見る |
| 再帰の禁止 | `check-rules.sh`（`-fcallgraph-info` の呼び出しグラフに閉路が無いこと。`tools/find-cycles.py`。直接・相互・ファイルをまたぐ再帰を検出） | 走査は反復で書く（フリーリストの走査など）。限界: 関数ポインタなどの間接呼び出しは検査できない（WARN） |
| libc に依存しない（承認: 判断 C） | `check-rules.sh`（`-ffreestanding`、`-O0` と `-Os`、未定義シンボルが無いこと）、`make check-arm` | `memcpy` `memset` `assert` `printf` を使わない。使えるのは `<stddef.h>` `<stdint.h>` `<stdalign.h>` など、ライブラリを要しないヘッダ。限界: `check-rules.sh` の未定義シンボルの検査は、`src/` が1ファイルの前提（ファイル間の参照が、外部シンボルとして誤検出される） |
| 動的確保の禁止（`malloc` `calloc` `realloc` `free` ほか） | `check-rules.sh`（未定義シンボルを検出） | プールの領域は、呼び出し側が渡すバッファ（`pool_init(pool, buf, ...)` の形）。ここが設計の前提になる |
| ポインタ操作は、コンパイラに任せる（ユーザーの指示） | レビュー | ポインタの進め方は、ポインタ型の演算（`base + i * size`、配列添字）で書く。整数にして手計算しない |
| 明示的なポインタへのキャストは許容する（ユーザーの指示） | なし | `void *` ↔ `T *`、`unsigned char *` ↔ `void **` などのポインタ同士のキャストは使ってよい（`node_set_next` `node_get_next`） |
| 整数演算の値を、ポインタとして扱わない（ユーザーの指示） | `check-rules.sh`（`(T *)(uintptr_t …)` の形を検出） | ポインタ → 整数（`uintptr_t`）は、比較と境界の検査だけに使う。整数 → ポインタは作らない。限界: 整数型の変数（例: `addr`）を直接キャストする形は、型が分からないので検出できない（レビューで見る）。コンパイラの `-Wint-to-pointer-cast` は、大きさが違うときだけ |

`tests/probe/` は、意図したバグ・違反を含む（ASan の試験は `malloc` を使う）ので、そもそも対象外。

## 4. 未検査（機械では見られない）

- **コメントの質**（「なぜ」を書く）、**命名**: レビューで見る。
- **間接呼び出し経由の再帰**、**整数型の変数からのポインタ**、**ファイルスコープの `static` 変数**: 上の「限界」のとおり。`src/` が小さいうちは、レビューで見られる。

## 5. 実装の初期値（承認: 2026-10-06。正本は `docs/design.md` の 5 節）

- 型: サイズと個数は `size_t`、アドレスの比較は `uintptr_t`（ポインタ → 整数だけ）。
- オーバーフロー: ブロックサイズの切り上げと、アドレスの調整は、検査してから行う。範囲の検査は、乗算を避ける。
- 失敗の返し方: 確保の失敗は `NULL`。他は `pool_status`。`assert` と `abort` は使わない（libc 依存を避ける）。失敗した `pool_init` は `*p` を変更しない。
- 公開と内部: 公開は `src/pool.h` の宣言だけ。内部の関数は `static`。include ガードは `POOL_H`。
- 名前: 公開 API は `pool_` 接頭辞。型名は `struct pool`（typedef なし。`_t` 終わりは POSIX が予約）。
- コメント: 「なぜ」だけを書く。公開関数には、前提（所有権、アライメント、失敗時の戻り値）を1〜3行で書く。
- テスト: 1つのテスト関数は1つの観点。
