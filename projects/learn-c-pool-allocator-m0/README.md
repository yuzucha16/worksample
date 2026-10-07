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

`make check` が、Cortex-M0 / M0+ と Cortex-M3 / M4 の両方で全項目通り（ホストのテストは ASan・UBSan つきで警告 0）、各コアのフットプリント（`.text` `.data` `.bss`）の実測値を記録する。（種類はユーザー承認: 2026-10-07。文面は承認待ち）

## 方針（ユーザーの指示。2026-10-07）

- M0 対応は、静的な（ビルド時の）切り替えにする。実行時の分岐にしない。
- M0 では、フットプリントが小さくなることを優先する（M3 / M4 と違い、小ささを取る）。
- 動くことを確認してから、チューニング要素（速度の最適化）を行う。最初の設計の根拠にしない。
- 引き継ぐ前提: 組込み領域、安全性 > 起動速度、`archives/learn-c-pool-allocator/docs/coding-rules.md` の制約と機械検査。

## 成果物

未定（設計の判断が承認されたら書く。前の Project の `src/` `tests/` `Makefile` `tools/` を土台にする）。

## 範囲外

スレッド安全性、検査の限界の解消（それぞれ別の Project の候補）。

## Open Questions

- 切り替えの方式（`__ARM_FEATURE_IDIV` での自動切り替え、ビルドオプションでの明示、など）。
- M0 向けの除算の置き換え方（2進の筆算、除算を使わない設計への変更、など。フットプリント優先で比べる）。
- 前の Project の `src/` を、コピーして始めるか、参照するか。
