---
status: active
area: learning
review: 2026-10-20
created: 2026-10-07
updated: 2026-10-07
---

# learn-c-pool-allocator-m0

`archives/learn-c-pool-allocator` の固定長メモリプールアロケータを、Cortex-M0 / M0+（ARMv6-M。除算命令が無い）にも対応させる。M0 対応は、ビルド時の静的な切り替えにする。所属 Area: [[areas/learning/README|learning]]。前の Project: [[archives/learn-c-pool-allocator/README|learn-c-pool-allocator]]（判断 F は `archives/learn-c-pool-allocator/docs/design.md`）。

## 完了条件

`make check` が、Cortex-M0 / M0+ と Cortex-M3 / M4 の両方で全項目通り（ホストのテストは ASan・UBSan つきで警告 0）、各コアのフットプリント（`.text` `.data` `.bss`）の実測値を記録する。（ユーザー承認: 2026-10-07）

## 方針（ユーザーの指示。2026-10-07）

- M0 対応は、静的な（ビルド時の）切り替えにする。実行時の分岐にしない。
- M0 では、フットプリントが小さくなることを優先する（M3 / M4 と違い、小ささを取る）。
- 動くことを確認してから、チューニング要素（速度の最適化）を行う。最初の設計の根拠にしない。
- 引き継ぐ前提: 組込み領域、安全性 > 起動速度、`archives/learn-c-pool-allocator/docs/coding-rules.md` の制約と機械検査。

## 結果（2026-10-07。完了条件の確認はユーザー待ち）

- `make check` が通る（終了コード 0。ホスト試験は ASan・UBSan つき、除算なしの経路も含む）。フットプリント（`-Os`、freestanding、バイト）: Cortex-M0 / M0+ は `.text` 360、M3 / M4 は 288（変更前とバイト単位で同一）。`.data` と `.bss` はすべて 0。

## 成果物

- `src/`（`pool.h` `pool.c`。除算を使わない経路は `POOL_SOFT_DIV`）、`tests/`、`Makefile`（`make check`、`make test-soft`、`make size-arm`）、`tools/`、`.clang-format`: 前の Project から持ち込み、M0 対応を足した。
- `docs/`: 経緯（`log.md`）、判断（`decisions.md`）、設計（`design.md`。判断 F は前の Project の記録）、ルール（`coding-rules.md`）。

## 範囲外

スレッド安全性、検査の限界の解消（それぞれ別の Project の候補）。

## Open Questions

なし（切り替えの方式、除算の置き換え方、持ち込み方は決定済み。`docs/decisions.md`）。
