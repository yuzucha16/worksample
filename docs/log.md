# 作業ログ（log）

`works`（Vault のトップ。PC ローカルのリポジトリ）の現在状態と次にやること。**開始時に読むのはこのファイルだけ**（上書きで更新する。4KB 目安）。経緯と、過去の Next Actions の全文は `docs/log-history.md`（開始時に読まない。必要なとき検索する）。判断の根拠は `docs/decisions.md`（何かを決める前に検索する）。

## 期日（開始時に確認する。今日以前、または3日以内の項目は、最初の返答で知らせて判断を求める）

| 期日 | 判断すること | 担当 |
|---|---|---|
| 2026-10-15 | ① 読み落とし点検（会話履歴から: コミット前の `git diff --cached`、`docs-rules.md` の読み込み、`decisions.md` への提案の混入、決める前の `decisions.md` の検索）② ログ分割と `docs-rules.md` の開始時読み込み廃止の昇格（手戻りが無ければ kit に反映）③ CRLF の混入元（`events.csv`、`review-hook.md`）④ 最初の `review` の実施（`again` と遠回りの事例。読み込み量は `extract-threads.ps1 -Snapshot` で `load.csv` に追記して、前後の表と比べる）⑤ 既存の知識のユーザー名入りパス 5 行（`exmem` の 3 ファイル）の修正 | エージェントが調べて報告。ユーザーは `again` の場面と体感を伝える。**進捗（10-14）: ① 済み**（違反 1 件 = 10-12 の `git add -A <パス>`。実害なし。`git add -A <パス>` を許可する案をユーザーが承認し、`AGENTS.md` と kit に反映。経緯は `guides/explain/agent-safety-rules.md`）。② のうち `docs-rules` は、廃止を続け、読む場面を強める（安全規則に「コミット・push の前に未読なら読む」を明記。ユーザー決定）。ログ分割は kit の `docs-rules.md` と `open-hook.md` に昇格済み（ユーザー決定。個人的にも分けたい）。③ 済み（CRLF の混入元: 行の追記で「既存の改行に合わせる」書き方が CRLF を増やし続けていた。行末 CR 6 行を LF にし、追記は常に LF と README に明記。`review-hook.md` は 10-08 に直済みで現在 LF）。④⑤ は未 |
| 2026-11-08 | **停止期間の終わりの一括判定**（先に `-Snapshot` で読み込み量を測る）: ① 試験運用の各項目（`decisions.md` の「案Eの判定基準」。既定は畳む）② 自動採用の停止を解くか ③ 規模の凍結を解くか続けるか ④ 手順書本体の縮小の続き（`stock-hook.md` 手順 2 の例外、`docs-rules.md`）⑤ 合言葉の統合（フェーズ3）⑥ `contexts/`（クラウドから push できるので畳めるか）⑦ 手順書の場所の 1 か所化（ステップ 4）⑧ 安全の検査スクリプト（sh）と pre-push | エージェントが期日に知らせる。判断はユーザー |

## Next Actions（2026-10-08 時点）

1. **案E（L3・L5 のレビューの推奨。ユーザー承認済み）の実施**: 済み: 転記の仕組みを「`→ 知識名` のリンクの有無」に簡素化（6状態・台帳・本文ハッシュ・`check-docs.ps1` を畳んだ）、`wrap` を 3 段階＋報告に、`review` を `again` と遠回りの事例を見る内容に、自動採用を 11-08 まで停止。残りは 11-08 の判定に回す（期日の表）。
2. **週1回・15分の `review`**: 初回は 10-15 までに。入力は `again` の件数と内容、終了時の1問、開始時の読み込み字数（`extract-threads.ps1 -Report`）。**次回 `review` の対象に足す（2026-10-14）: `start` のモード（確定型・探索型）の試用結果**。`again`・`gap`・`goal_change` の件数、探索型で全体4回に収まったか、型の判定の1問が合っていたか（根拠は exmem の `lessons/session-goal-modes.md`。未解決は `mobile-session/improvement-methods/`）。
3. **構造の見直し（L1 の案F）**: ステップ 0〜3、5〜9 は済み。常時読み込みは 79,804 → 6,198 字。残りはステップ 4・10 と、手順書本体の縮小の続き（期日の表）。
3b. **フックの章立て（2026-10-08 に統一。`resources` の `e2caad2`、未 push）**: 共通4章を全8フックに揃えた。あわせて `stock` 手順 2 を、kit 自身の作業は一般化できる型だけに絞った（`f78904d`）。残りは、規模の凍結に対して畳んだものが無い点（11-08 の判定で扱う）。（`works` の remote の公開範囲は、2026-10-11 の `gh repo view` で PRIVATE と確認した。10-08 の PUBLIC との食い違いの原因は未確認。push は 10-11 に実施済み。）
4. **PARA の試行**: 3回目の Project（候補は `areas/learning/README.md`）。kit への昇格は安定してから。
5. **保留**: 旧 `C:\vault` と GitHub の旧 `notes` の削除、`claude --resume` の確認、WSL の `WORKS_DIR` の実機確認（詳細は `log-history.md` の Next Actions）。

## Open Questions

- Claudian（2026-10-11）: Bedrock を使う別 PC で、dotfiles の `settings-bedrock.txt` を Bedrock のスニペットへ貼り、複数行が保存されて接続できるか確認する。このスニペットの値は手書きのサンプルで、`settings-bedrock.json` が正（`docs/decisions.md` の先頭の項目）。
- Claudian の設定（2026-10-12）: `claudian-settings.json` は dotfiles の symlink（Windows は `30_link.bat`）。別 PC では dotfiles を pull して `30_link.bat` を実行する（実ファイルがあると `[ERR]`。退避してから）。ネイティブ Linux は未対応。
- `workbase` の公開: 予定はあるが未決定。公開されうる前提で書く（ユーザー、2026-10-08）。非公開の remote は GitHub。クラウドから作業側へ push してよい（ユーザー、2026-10-08）。
- 公開前に直すもの: 既存の知識に、ユーザー名を含むパスが 5 行ある（期日の 10-15 ⑤）。
