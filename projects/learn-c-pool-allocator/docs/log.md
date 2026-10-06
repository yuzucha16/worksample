# 作業ログ（log）

C のメモリプールアロケータの実装による学習（Project `learn-c-pool-allocator`）の現在状態と次にやること。完了条件と範囲は `README.md`。判断の根拠は `docs/decisions.md`。

## Next Actions

- ユーザーが、WSL に `clang-format` を導入する（`docs/dotfiles-additions.md` のコマンド）。導入後に `make check` で `OK: format-check` になることを確認し、整形の差分があれば `make format` で直す。
- 制約の適用範囲（`tests/probe/` は対象外）と、「`.data` を抑える」の読み方を、ユーザーに確認する（`docs/coding-rules.md` の「AI の解釈」）。
- アロケータの API とメモリレイアウトを設計する（ブロックサイズ、フリーリスト、アライメント。動的確保とグローバル変数の禁止から、領域は呼び出し側が渡すバッファ）。判断は `docs/decisions.md` に残す。
- 設計に沿って、`src/pool.c` と `tests/test_pool.c` を実装する（完了条件: 単体テストと、ASan・UBSan の警告 0）。
- WSL の開発ツールが足りなければ、dotfiles に足す（ユーザーの方針。2026-10-06。`gdb` `valgrind` `clang` `cmake` は、いまは無い。必要になってから）。

## Open Questions

## Log

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
