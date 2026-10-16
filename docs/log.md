# 作業ログ（log）

`works`（Vault のトップ。PC ローカルのリポジトリ）の現在状態と次にやること。**開始時に読むのはこのファイルだけ**（上書きで更新する。4KB 目安）。経緯と過去の Next Actions の全文は `docs/log-history.md`、判断の根拠は `docs/decisions.md`（どちらも開始時に読まない。必要なとき検索する）。

## 期日（今日以前、または3日以内の項目は、最初の返答で知らせて判断を求める）

| 期日 | 判断すること | 担当 |
|---|---|---|
| 2026-11-08 | **停止期間の終わりの一括判定**（先に `-Snapshot` で読み込み量を測る）: ① 試験運用の各項目（`decisions.md` の「案Eの判定基準」。既定は畳む）② 自動採用の停止 ③ 規模の凍結 ④ 手順書本体の縮小の続き ⑤ 合言葉の統合（フェーズ3）⑥ `contexts/` ⑦ 手順書の場所の 1 か所化（ステップ 4）⑧ 安全の検査スクリプトと pre-push | エージェントが期日に知らせる。判断はユーザー |

## Next Actions（2026-10-16 時点）

1. **週1回・15分の `review`**（初回は 10-15 に実施済み。2 回目を 10-22 ごろまでに）: 入力は `again` の件数、終了時の1問、読み込み字数（`extract-threads.ps1 -Report`）。あわせて確かめる: ① `start` のモード（確定型・探索型）の試用結果（根拠は exmem の `lessons/session-goal-modes.md`）② 入力 8 の比較が、`alignment-baseline.md` の差分を意図どおり拾うか。
2. **ユーザーの作業**: PARA の 3回目の Project（候補は `areas/learning/README.md`）、AI 作業部屋の通し（`resources` の `ai-room-next-steps` の TODO）、`claude --resume` の確認、WSL への `WORKS_DIR` の受け渡し(2026-10-16 の確認: Ubuntu-24.04 で `WSLENV` は設定されているが、`WORKS_DIR` と `CERTS_DIR` は渡っていない。原因は未特定)。
3. **11-08 の一括判定**(期日の表): 案E の残り、構造の見直しのステップ 4・10、`pre-push` と git 周りの見直し(deny のパターンがコミットメッセージ中の禁止語にも一致する点を含む)。

## Open Questions

なし。公開リポジトリの履歴の書き換え（個人・組織を特定する文言の除去と、author のメールの noreply 化）は、2026-10-16 に済み。author の紐付けとバックアップの削除も、ユーザーが確認・実施した。他の PC での復旧手順は `log-history.md`。
