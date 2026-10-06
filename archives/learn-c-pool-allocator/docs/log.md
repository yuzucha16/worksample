# 作業ログ（log）

C のメモリプールアロケータの実装による学習（Project `learn-c-pool-allocator`）の現在状態と次にやること。完了条件と範囲は `README.md`。判断の根拠は `docs/decisions.md`。

## Next Actions

なし。Project を閉じた（2026-10-06）。持ち越しは `areas/learning/README.md` の「次の Project の候補」。`docs/decisions.md` の `未仕分け`（【汎用】の Principles 2、Facts 3、Gotchas 2）は、ユーザーが「ナレッジ化して」または「終了処理して」を言ったときに処理する（ユーザーの指示: あとでまとめて言う）。

## Open Questions

## Log

### 2026-10-06（Project を閉じた。完了条件を達成。セッション `2026-10-06-s5`）

- ユーザーが判断 F に F4（Cortex-M0 を対象外）を選んだ。`src/pool.c` に、ARMv6-M で `#error` で止める記述を足した。`make check-arm` は、M3 / M4 の未定義シンボルが無いことと、M0 が `#error` で止まることを確認する。`make check` が全項目通った（確認: 2026-10-06）。フットプリント: M3 / M4 は `.text` 288、`.data` 0、`.bss` 0。
- 完了条件（`alloc`/`free` の単体テストと、ASan・UBSan の警告 0 の実行）を、`make check` で確認して達成。ユーザーの指示で、見直し日（2026-10-20）を待たずに閉じた。暫定の制約は、実測で再検討し、現状維持（再帰とポインタの検査を足した）。結果は `README.md`。
- `archives/` へ移した（`git mv`）。親の Area の一覧（`areas/learning/README.md`）を更新した。
- ユーザーの指示で、ナレッジ化は、あとでまとめて言う（`docs/decisions.md` の【汎用】の未仕分け 7 件を残した）。

### 2026-10-06（セッション `2026-10-06-s5`。ARM の実測と、暫定制約の再検討）

- ユーザーが `gcc-arm-none-eabi` を導入し、`make check-arm` と `make size-arm` を実行した。**仮説が当たった**: Cortex-M0 で `__aeabi_uidiv` `__aeabi_uidivmod`（除算命令が無いため）。M3 / M4 は OK。`check-arm` が最初の失敗で止まり M3 / M4 が見えなかったので、全 CPU を集計する形に直した。
- 容量（`-Os`、`.text` バイト、`.data` と `.bss` は 0）: M3 / M4 は 288、M0 は 332 で、libgcc をリンクすると 612（`__udivsi3` が 266 バイト）。2進の筆算に置き換えた試作（一時ディレクトリ。`src/` には未反映）は、M0 で 378、M3 で 358、未定義シンボルなし。ホストで `test_pool.c` が ASan・UBSan つき、`-O1` と `-O2` で通った。選択肢 F1〜F4 は `docs/design.md`（判断 F）。
- ユーザーが「実装の初期値」を承認した。MISRA C は目標にしない。ポインタの規則: コンパイラに任せる、明示的なキャストは許容、整数演算の値をポインタとして扱わない（`docs/decisions.md`）。
- 暫定制約の再検討（ユーザーの指示: 見直し日を待たず、実測と再検討をして close に持っていく）:
  - 再帰の禁止は、未検査だったので、機械検査にした（`gcc -fcallgraph-info` と `tools/find-cycles.py`。直接・相互・ファイルをまたぐ再帰を検出。間接呼び出しは警告）。
  - ポインタの規則③（整数 → ポインタのキャスト禁止）を、簡易検査にした（`(T *)(uintptr_t …)` の形）。
  - 結果: 制約（`.data`、グローバル変数、動的確保、libc、再帰）は、`src/pool.c` で満たされている（`make check` の `check-rules` と `check-arm`（M3 / M4）が OK）。**未解決は、Cortex-M0 の除算 1 点**。限界: ファイルスコープの `static`（ゼロ初期化）は許可になる、間接呼び出し経由の再帰は検査できない、`check-rules.sh` の未定義シンボルの検査は `src/` が1ファイルの前提。
- いまの `make check` は、`check-arm` の M0 で失敗する（意図した状態。判断 F の決定後に直す）。

### 2026-10-06（セッション `2026-10-06-s4`。実装）

- ユーザーが、判断 E1（`-fno-strict-aliasing`）と `arm-none-eabi-gcc` の導入を承認した。`docs/coding-rules.md` の `.data` の制約から、「起動を楽にする」の記述を削除した（ユーザーの指示）。
- アロケータを実装した: `src/pool.h` `src/pool.c`（固定長ブロック、全ブロックを連結、侵入型の単方向リスト、`pool_init` `pool_alloc` `pool_free` `pool_check`。設計は `docs/design.md`）。テスト `tests/test_pool.c`（引数の検証、不変条件、整列（align 8〜64、先頭を 0〜7 バイトずらす）、枯渇と LIFO の再利用、重ならないこと、不正な `free`、未初期化のプール、リストの破壊の検出、固定シードのモデル検査 2万回）と、`tests/check.h`。`Makefile` に、`test-o2`（`-O2`）、`check-arm`、`size`、`size-arm`、`-fno-strict-aliasing` を足した。
- 確認（2026-10-06、gcc 13.3、WSL）: `make check` が通った（`format-check`、`analyze`、`check-rules`（変数・`.data`・`malloc`・libc 依存・改行・文字コード）、`test`（ASan・UBSan）、`test-o2`、`probe`）。`check-arm` は `arm-none-eabi-gcc` 未導入で SKIP。フットプリント（ホスト x86-64、`-Os`）: `.text` 633、`.data` 0、`.bss` 0（バイト）。
- E1 の対照実験: `-fno-strict-aliasing` を外しても、`-O1` `-O2` `-O3` のどれでもテストは通った（strict aliasing の問題は再現していない。E1 は予防）。
- 作業中に、テストの未定義動作を1件直した（配列の外へのポインタ演算 `b - n` を、整数で作る形に）。
- リスク（未確認）: `pool_free` の `locate` の除算・剰余は、Cortex-M0 では libgcc の補助関数を呼び、libc 非依存の検査に引っかかる可能性がある。`arm-none-eabi-gcc` の導入後に `make check-arm` で確認する（`docs/design.md` の 5 節。対処案 3 つ）。
- dotfiles に `gcc-arm-none-eabi` を追記した（dotfiles の `08df993`。約 490MB）。実機への導入は、ユーザーが行う（`docs/dotfiles-additions.md`）。

### 2026-10-06（セッション `2026-10-06-s3`。組込み前提の設計）

- ユーザーが `clang-format` を導入した（18.1.3）。`make check` で `format-check` が有効になり、手で揃えたマクロの `\` を指摘したので、`make format` で直した。
- ユーザーが、組込み領域のエンジニアであることを伝え（インタビューで聞いていなかった前提）、制約の確認に回答した: ① 制約の適用範囲は `src/` のみ（テストは実現のしやすさを優先）、② 「`.data` を抑える」の目的は、初期値つき `.data` を減らしてフットプリントの削減と起動を楽にすること（`.bss` はグローバルでなければ許可）。AI の当初の解釈（`tests/test_*.c` も対象、`.bss` も全面禁止）は強すぎたので直した。`tools/check-rules.sh` を、初期値つき `.data`（`D` `d`）とグローバル変数（外部リンケージの `B` `C` `G` `S`）の禁止に変え、許可される例の対照（`rules_ok.c`）と、初期値つき `static` の検出（`rules_static_data.c`）を足した。`make check` が通った。
- 組込み前提の設計を、`docs/design.md` にまとめた。要点: 固定長ブロック、侵入型の単方向フリーリスト、呼び出し側が渡すバッファ、`libc` 非依存、`alloc`/`free` が O(1)。
- ユーザーが判断 A〜D を回答した（`docs/decisions.md`）: A 全ブロックを連結（AI の推奨の遅延切り出しは却下。安全性を起動速度より優先し、起動速度はチューニング要素）、B O(1) の検査 + `pool_check`（二重解放は、検知でなく、起こさないことをテストで見る）、C libc 非依存、D 32bit MCU（Cortex-M 系）。設計書から「起動を楽にする」を根拠にした記述を消し、遅延切り出しをチューニング要素の節に移した（AI の拡大解釈をユーザーが直した）。
- 判断 C の検査（`check-rules.sh` の libc 非依存。`-ffreestanding`、`-O0` と `-Os`）を実装し、違反例（`rules_libc.c`）で検出を確認した。`make check` が通った。`-Os` では `memset` が展開され `strlen` だけが残るので、両方の最適化レベルで見る。
- 新しい論点として、判断 E（strict aliasing: 空きブロックに `void *` を書く侵入型リストは、呼び出し側の `unsigned char` 配列に対して、規格上の有効型の問題がある）を、設計書に提案として足した（未承認）。

### 2026-10-06（セッション `2026-10-06-s2`。コーディングルールとチェック）

- ユーザーの要望で、実装のときに私が暗黙に持っているルールを明示した（`docs/coding-rules.md`）。確認した事実: 導入済みの機械チェックは、コンパイラの警告とサニタイザだけで、linter もフォーマッタも無かった（WSL に `cppcheck` `clang-tidy` `clang-format` は未導入。`gcc -fanalyzer` は使える）。
- ユーザーが承認した内容（`docs/decisions.md`）: 既存の書式を規則にする、改行コードと文字コードを規則に足す、制約（グローバル変数の禁止、`.data` の抑制、再帰の禁止、動的確保の禁止。暫定）、追加の警告フラグと `-fanalyzer`、`clang-format` の導入（目的はコードリーディングのコストの低減）。
- 実施: `Makefile` に追加の警告フラグ、`analyze`（`-fanalyzer`）、`check-rules`、`format` `format-check`、全体の `check` を足した。制約を検査する `tools/check-rules.sh`（`nm` でグローバル・静的変数と `malloc` 系の呼び出しを、CR・BOM・UTF-8 も検出）と、`.clang-format` を作った。`make probe` に、変数・`malloc`・CRLF・BOM の検出の確認を足した。確認: `make check` が通った（`format-check` は `clang-format` 未導入のため SKIP）。
- dotfiles の `manifests/apt.txt` に `clang-format` を追記した（dotfiles の `14711b5`）。WSL への導入は `sudo` のパスワードが要るため、ユーザーが行う（`docs/dotfiles-additions.md`）。
- 再帰の禁止は検査していない。制約の適用範囲（`tests/probe/` は対象外）と、「`.data` を抑える」の強めの読みは、AI の解釈で、ユーザーの確認待ち。
- 制約（動的確保の禁止、グローバル変数の禁止）から、設計の前提が決まる: プールの領域は呼び出し側が渡すバッファ、状態は構造体に持たせる。

### 2026-10-06（セッション `2026-10-06-s2`。環境と骨組み）

- 開始インタビューを手動で試した（PARA の試行。指標は親の `docs/metrics/events.csv`）。ゴール: 環境を整え、テストが走る最小の骨組みを作る。前提: WSL の gcc と make で進める。対象と資料: この `README.md` と `docs/log.md`。やらないこと: C++ の機能や他の言語の比較、スレッド安全性（README の範囲外のまま）、kit の変更。dotfiles への追記は、必要になったらしてよい（質問の選択肢「dotfiles や kit の変更はやらない」は誤りで、ユーザーが直した）。
- 環境を確認した。Windows 側に C コンパイラは無く、WSL（Ubuntu 24.04）に gcc 13.3.0 と make がある（`clang` `cmake` `gdb` `valgrind` は無い）。判断は `docs/decisions.md`。
- 最小の骨組みを作った: `Makefile`（`make test` は ASan・UBSan つきで `tests/test_*.c` を実行、`make probe` はサニタイザが意図したバグを検出することの確認）、`tests/test_smoke.c`（仕組みの確認だけ）、`tests/probe/`（ヒープの範囲外書き込みと、符号付き整数のオーバーフロー）、`.gitignore`（`/build/`）。確認: WSL で `make test probe` が通った（`ok: test_smoke`、ASan・UBSan とも検出）。
- 最初の UBSan のプローブは、検出されなくても終了コード 1 で終わる作りで、`make probe` が誤って成功した。対照実験（サニタイザなし・`recover` 許可は 0、`-fno-sanitize-recover=undefined` は非ゼロ）で見つけて直した（`docs/decisions.md` の Gotchas）。
- この骨組みは、完了条件（`alloc`/`free` の単体テストと警告 0）の前提の部分だけで、アロケータの実装は未着手。

### 2026-10-06

- Project を作った。PARA の試行（`docs/decisions.md`、親の `works` の記録）の最初の Project として、開始の手順を手でなぞった（ユーザーが、言語 = C、成果物 = 小さな実装物、見直し日 = 2026-10-20 を選んだ。成果物の具体案は AI の提案で、同日にユーザーが承認した）。
