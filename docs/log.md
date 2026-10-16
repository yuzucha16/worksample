# 作業ログ（log）

`works`（Vault のトップ。PC ローカルのリポジトリ）の現在状態と次にやること。**開始時に読むのはこのファイルだけ**（上書きで更新する。4KB 目安）。経緯と過去の Next Actions の全文は `docs/log-history.md`、判断の根拠は `docs/decisions.md`（どちらも開始時に読まない。必要なとき検索する）。

## 期日（今日以前、または3日以内の項目は、最初の返答で知らせて判断を求める）

| 期日 | 判断すること | 担当 |
|---|---|---|
| 2026-11-08 | **停止期間の終わりの一括判定**（先に `-Snapshot` で読み込み量を測る）: ① 試験運用の各項目（`decisions.md` の「案Eの判定基準」。既定は畳む）② 自動採用の停止 ③ 規模の凍結 ④ 手順書本体の縮小の続き ⑤ 合言葉の統合（フェーズ3）⑥ `contexts/` ⑦ 手順書の場所の 1 か所化（ステップ 4）⑧ 安全の検査スクリプトと pre-push | エージェントが期日に知らせる。判断はユーザー |

## Next Actions（2026-10-16 時点）

1. **案E**: 残りは 11-08 の判定に回す（期日の表）。
2. **週1回・15分の `review`**（初回は 10-15 まで。期限超過）: 入力は `again` の件数、終了時の1問、読み込み字数（`extract-threads.ps1 -Report`）。あわせて確かめる: ① `start` のモード（確定型・探索型）の試用結果（`goal_change` の件数、探索型で4回に収まったか。根拠は exmem の `lessons/session-goal-modes.md`）② 入力 8 の比較が、`alignment-baseline.md` の差分を意図どおり拾うか。
3. **構造の見直し（L1 の案F）**: 残りはステップ 4・10 と、手順書本体の縮小の続き（11-08）。
4. **PARA の試行**: 3回目の Project（候補は `areas/learning/README.md`）。
4b. **AI 作業部屋**: 残りは `resources` の `ai-room-next-steps` の TODO（`room start` の通し、部屋の AI の下書きの通し、マウントの可視性、項目 5）。
4c. **3 リポジトリの規則の統一**: `pre-push` と git 周りの見直しは 11-08（⑧）。deny のパターンがコミットメッセージ中の禁止語にも一致する（絞り直しは git の見直しで）。残るギャップ: works の README の行を `alignment-baseline.md` で更新する。
5. **保留**: `claude --resume` の確認、WSL の `WORKS_DIR` の実機確認。

## Open Questions

- Claudian（2026-10-11）: Bedrock の別 PC で、dotfiles の `settings-bedrock.txt` を貼り、複数行が保存されて接続できるか確認する（正は `settings-bedrock.json`。`decisions.md` の先頭）。
- Claudian の設定（2026-10-12）: `claudian-settings.json` は dotfiles の symlink。別 PC では pull して `30_link.bat` を実行する（実ファイルは退避）。ネイティブ Linux は未対応。
- 公開範囲（2026-10-16）: `worksample` は PRIVATE、`workbase` と `dotfiles` は PUBLIC（公開のまま、エージェントが push してよい。ユーザーの決定）。10-08 の PUBLIC と 10-11 の PRIVATE の食い違いの原因は未確認。
- **公開リポジトリの git 履歴に、ユーザー名を含むパスが残っている**（現行ファイルからは除いた。10-15）。履歴の書き換え（force push が要り、現在は禁止）で消すか残すかは未決。
