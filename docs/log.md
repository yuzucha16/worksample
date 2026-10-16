# 作業ログ（log）

`works`（Vault のトップ。PC ローカルのリポジトリ）の現在状態と次にやること。**開始時に読むのはこのファイルだけ**（上書きで更新する。4KB 目安）。経緯と過去の Next Actions の全文は `docs/log-history.md`、判断の根拠は `docs/decisions.md`（どちらも開始時に読まない。必要なとき検索する）。

## 期日（今日以前、または3日以内の項目は、最初の返答で知らせて判断を求める。定例は実行したら次回の期日に書き換える。書式は kit の `docs-rules.md`）

| 期日 | 種別 | 内容 | 担当 |
|---|---|---|---|
| 2026-10-22 | 定例（週1・15分） | **`review`**（前回 10-15）: 入力は `again` の件数、終了時の1問、読み込み字数（`extract-threads.ps1 -Report`）。あわせて確かめる: ① `start` のモード（確定型・探索型）の試用結果（根拠は exmem の `lessons/session-goal-modes.md`）② 入力 8 の比較が、`alignment-baseline.md` の差分を意図どおり拾うか。③ 各フックの cwd の期待（kit の `hook-matrix.md` の cwd の 3 行、初回）④ 入力 3・4・6 が `alignment-baseline.md` の「点検の対象」の 3 リポジトリを見るか。実行したら次回の期日に書き換える | ユーザーとエージェント |
| 2026-11-08 | 単発 | **停止期間の終わりの一括判定**（先に `-Snapshot` で読み込み量を測る）: ① 試験運用の各項目（`decisions.md` の「案Eの判定基準」。既定は畳む）② 自動採用の停止 ③ 規模の凍結 ④ 手順書本体の縮小の続き ⑤ 合言葉の統合（フェーズ3）⑥ `contexts/` ⑦ 手順書の場所の 1 か所化（ステップ 4）⑧ 安全の検査スクリプトと pre-push | エージェントが期日に知らせる。判断はユーザー |

## Next Actions（2026-10-16 時点）

1. **ユーザーの作業**: PARA の 3回目の Project（候補は `areas/learning/README.md`）、AI 作業部屋の通し（`resources` の `ai-room-next-steps` の TODO）、`claude --resume` の確認、WSL への `WORKS_DIR` の受け渡し(2026-10-16 の確認: Ubuntu-24.04 で `WSLENV` は設定されているが、`WORKS_DIR` と `CERTS_DIR` は渡っていない。原因は未特定)。
2. **11-08 の一括判定**(期日の表): 案E の残り、構造の見直しのステップ 4・10、`pre-push` と git 周りの見直し(deny のパターンがコミットメッセージ中の禁止語にも一致する点を含む)。

## Open Questions

なし。公開リポジトリの履歴の書き換え（個人・組織を特定する文言の除去と、author のメールの noreply 化）は、2026-10-16 に済み。author の紐付けとバックアップの削除も、ユーザーが確認・実施した。他の PC での復旧手順は `log-history.md`。
