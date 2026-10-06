---
status: done
area: learning
review: 2026-10-20
created: 2026-10-06
closed: 2026-10-06
updated: 2026-10-06
---

# learn-c-pool-allocator

C の低レイヤー（メモリ配置、ポインタ、アライメント、未定義動作）を、組込み（Cortex-M 系）の制約のもとで、小さな実装で理解し直す。所属 Area: [[areas/learning/README|learning]]。

## 完了条件

固定長ブロックのメモリプールアロケータを C で実装し、`alloc` / `free` の単体テストと、AddressSanitizer・UndefinedBehaviorSanitizer の警告 0 の実行が通る。（ユーザー承認: 2026-10-06）

## 結果（2026-10-06 に達成。同日に close）

- **完了条件: 達成**（確認: 2026-10-06、`make check` が全項目通った）。`tests/test_pool.c` が、ASan・UBSan つきで `-O1` と `-O2` の両方で通る。観点は、引数の検証、不変条件、整列（8〜64、先頭をずらす）、枯渇と LIFO、ブロックが重ならないこと、不正な `free`、リストの破壊の検出、固定シードのモデル検査（2万回）。
- フットプリント（`-Os`、freestanding、バイト）: Cortex-M3 / M4 は `.text` 288、`.data` 0、`.bss` 0。ホスト x86-64 は 633 / 0 / 0。
- 対象は、ハードウェア除算のある Cortex-M3 / M4 など。Cortex-M0 / M0+ は対象外（`#error`。理由と代替案は `docs/design.md` の判断 F）。
- 制約（`src/` のみ）は、機械検査で満たされている: 初期値つき `.data` なし、グローバル変数なし、動的確保なし、libc 非依存（ホストと ARM）、再帰なし、整数からのポインタなし。

## 成果物

- `src/`: 実装（`pool.h` `pool.c`。設計は `docs/design.md`）
- `tests/`: 単体テスト（`test_*.c`）と、サニタイザ・検査が効いていることの確認（`probe/`）
- `Makefile`: `make check`（全チェック）、`make test`、`make probe`、`make size` `make size-arm`。WSL（Ubuntu 24.04）の gcc と make で動かす。ARM は `arm-none-eabi-gcc`
- `tools/check-rules.sh`、`tools/find-cycles.py`、`.clang-format`: コーディングルールの機械検査と整形の設定（内容と根拠は `docs/coding-rules.md`）
- `docs/`: 経緯（`log.md`）、判断（`decisions.md`）、設計（`design.md`）、ルール（`coding-rules.md`）、dotfiles に足したもの（`dotfiles-additions.md`）

## 範囲外

C++ の機能、スレッド安全性（次の Project の候補）。

## Open Questions

なし。持ち越しは `areas/learning/README.md` の「次の Project の候補」に移した。
