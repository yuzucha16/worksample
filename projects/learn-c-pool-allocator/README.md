---
status: active
area: learning
review: 2026-10-20
created: 2026-10-06
updated: 2026-10-06
---

# learn-c-pool-allocator

C の低レイヤー（メモリ配置、ポインタ、アライメント、未定義動作）を、小さな実装で理解し直す。所属 Area: [[areas/learning/README|learning]]。

## 完了条件

固定長ブロックのメモリプールアロケータを C で実装し、`alloc` / `free` の単体テストと、AddressSanitizer・UndefinedBehaviorSanitizer の警告 0 の実行が通る。（ユーザー承認: 2026-10-06）

## 成果物

- `src/`: 実装（アロケータ）
- `tests/`: 単体テスト（`test_*.c`）と、サニタイザが効いていることの確認（`probe/`）
- `Makefile`: `make test`（ASan・UBSan つきで実行）、`make probe`（意図したバグを検出することの確認）。WSL（Ubuntu 24.04）の gcc と make で動かす
- `docs/`: 経緯（`log.md`）と判断（`decisions.md`）。複数セッションにまたがるため置く

## 範囲外

C++ の機能、スレッド安全性（必要なら次の Project にする）。

## Open Questions

なし。
