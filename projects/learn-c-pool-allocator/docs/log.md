# 作業ログ（log）

C のメモリプールアロケータの実装による学習（Project `learn-c-pool-allocator`）の現在状態と次にやること。完了条件と範囲は `README.md`。判断の根拠は `docs/decisions.md`。

## Next Actions

- 判断 E（strict aliasing。E1 `-fno-strict-aliasing` を推奨）を、ユーザーが承認する。承認後に、`docs/coding-rules.md` の節 5 を、`docs/design.md` の「実装の初期値」で置き換える。
- `src/pool.h` `src/pool.c` と `tests/test_pool.c` を実装する（設計は `docs/design.md`。テストの観点は同書の 6 節）。`make size`（フットプリントの表示）を足す。
- ARM 向けのフットプリントを測るために、`arm-none-eabi-gcc` を dotfiles に足すか、ユーザーに確認する（提案。いまは未導入。導入すれば Cortex-M 向けの `.text` `.data` `.bss` を実測できる）。
- 設計に沿って、`src/pool.c` と `tests/test_pool.c` を実装する（完了条件: 単体テストと、ASan・UBSan の警告 0）。
- WSL の開発ツールが足りなければ、dotfiles に足す（ユーザーの方針。2026-10-06。`gdb` `valgrind` `clang` `cmake` は、いまは無い。必要になってから）。

## Open Questions

## Log

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
