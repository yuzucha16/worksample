---
status: active
review: 2026-10-20
created: 2026-10-06
updated: 2026-10-06
---

# learning（学習）

技術力を維持・更新する責任領域。終わりは無い。完了条件のある取り組みは、`projects/` に Project として切り出す。

## 基準

- 学習は、成果物（実装物など）で完了条件を書ける Project にする。読書や講座の消化だけを目的にしない。
- 見直し: Project の見直し日ごとに、この一覧を更新する。完了条件を達成したら、見直し日を待たずに閉じる。
- 一般化できる学びは、「ナレッジ化して」で exmem へ渡す。
- 開発系の Project は、実装の前に、専門領域（組込み）、設計の優先順位（安全性 > 起動速度）、コーディングルールとチェックの有無を確認する（初回の Project で、聞き漏れが3回あったため）。

## 進行中の Project

なし。

## 次の Project の候補（持ち越し。未決）

- スレッド・割り込みの安全性（`learn-c-pool-allocator` の範囲外。呼び出し側の排他の設計）。
- 検査の限界の解消（間接呼び出し経由の再帰、ファイルスコープの `static`、複数ファイルの `src/` での未定義シンボルの検査）。
- 速度の確認の実機化（M0 の実機または QEMU で、`pool_free` などのサイクルを測る。いまは命令シミュレータの値）、32 ビットのホスト実行（`gcc -m32` の導入）、シミュレータと変異テストのスクリプトのリポジトリ化（`archives/learn-c-pool-allocator-m0/docs/log.md` の持ち越し）。

## 完了した Project

- [[archives/learn-c-pool-allocator-m0/README|learn-c-pool-allocator-m0]]（C。Cortex-M0 / M0+ 対応と速度のチューニング。2026-10-07 に達成。M0 で `.text` 352 バイト、M3 / M4 で 280 バイト。`pool_free` は乗算 32 サイクルで 563 → 103 サイクル）
- [[archives/learn-c-pool-allocator/README|learn-c-pool-allocator]]（C。組込み向けの固定長メモリプール。2026-10-06 に達成。Cortex-M3 / M4 で `.text` 288 バイト、`.data` 0）
