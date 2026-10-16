# 作業ログ（log）

`works`（Vault のトップ。PC ローカルのリポジトリ）の現在状態と次にやること。**開始時に読むのはこのファイルだけ**（上書きで更新する。4KB 目安）。経緯と、過去の Next Actions の全文は `docs/log-history.md`（開始時に読まない。必要なとき検索する）。判断の根拠は `docs/decisions.md`（何かを決める前に検索する）。

## 期日（開始時に確認する。今日以前、または3日以内の項目は、最初の返答で知らせて判断を求める）

| 期日 | 判断すること | 担当 |
|---|---|---|
| 2026-11-08 | **停止期間の終わりの一括判定**（先に `-Snapshot` で読み込み量を測る）: ① 試験運用の各項目（`decisions.md` の「案Eの判定基準」。既定は畳む）② 自動採用の停止を解くか ③ 規模の凍結を解くか続けるか ④ 手順書本体の縮小の続き（`stock-hook.md` 手順 2 の例外、`docs-rules.md`）⑤ 合言葉の統合（フェーズ3）⑥ `contexts/`（クラウドから push できるので畳めるか）⑦ 手順書の場所の 1 か所化（ステップ 4）⑧ 安全の検査スクリプト（sh）と pre-push | エージェントが期日に知らせる。判断はユーザー |

## Next Actions（2026-10-08 時点）

1. **案E（L3・L5 のレビューの推奨。ユーザー承認済み）の実施**: 済み: 転記の仕組みを「`→ 知識名` のリンクの有無」に簡素化（6状態・台帳・本文ハッシュ・`check-docs.ps1` を畳んだ）、`wrap` を 3 段階＋報告に、`review` を `again` と遠回りの事例を見る内容に、自動採用を 11-08 まで停止。残りは 11-08 の判定に回す（期日の表）。
2. **週1回・15分の `review`**: 初回は 10-15 までに。入力は `again` の件数と内容、終了時の1問、開始時の読み込み字数（`extract-threads.ps1 -Report`）。**次回 `review` の対象に足す（2026-10-14）: `start` のモード（確定型・探索型）の試用結果**。`again`・`gap`・`goal_change` の件数、探索型で全体4回に収まったか、型の判定の1問が合っていたか（根拠は exmem の `lessons/session-goal-modes.md`。未解決は `mobile-session/improvement-methods/`）。
3. **構造の見直し（L1 の案F）**: ステップ 0〜3、5〜9 は済み。常時読み込みは 79,804 → 6,198 字。残りはステップ 4・10 と、手順書本体の縮小の続き（期日の表）。
3b. **フックの章立て（2026-10-08 に統一。`resources` の `e2caad2`、未 push）**: 共通4章を全8フックに揃えた。あわせて `stock` 手順 2 を、kit 自身の作業は一般化できる型だけに絞った（`f78904d`）。残りは、規模の凍結に対して畳んだものが無い点（11-08 の判定で扱う）。（`works` の remote の公開範囲は、2026-10-11 の `gh repo view` で PRIVATE と確認した。10-08 の PUBLIC との食い違いの原因は未確認。push は 10-11 に実施済み。）
4. **PARA の試行**: 3回目の Project（候補は `areas/learning/README.md`）。kit への昇格は安定してから。
4b. **AI 作業部屋（2026-10-14）**: ダミー Project `projects/dummy-mask`（`2dace8c`、push 済み）で、マスク・復元（Excel）、共有知の送付、`stock` を実機で確認した。結果は `resources` の `mobile-session/ai-workspace-boundary/` の各 handover の「PC での確認の結果」。残りと保留は同 `ai-room-next-steps` の TODO（`room start` の通し、部屋の AI が下書きを書く通し、マウントの可視性、項目 5 は別セッションのディレクトリ構造と合流してから）。`resources` は push 済み（ユーザー）。`exmem/inbox/` に未追跡のメモが 2 件ある（「ナレッジ化して」の出力。統合は `integrate`）。
4c. **3 リポジトリの規則の統一（2026-10-16）**: フェーズ1〜3 は済み（kit の `review` の入力 8 に、今後の点検を入れた）。フェーズ4は deny 設定だけ済み（2026-10-16。dotfiles `home/.claude/settings.json` に 38 件。ユーザーの決定。凍結の対として 3 つの `AGENTS.md` の禁止コマンドの列挙を kit への参照に畳んだ）。`pre-push` は 11-08 の判定（⑧）へ。git 周りは後日まとめて見直す（ユーザー）。review の入力 8 の初回は実施済み（残るギャップ: works の `docs/log.md` が 4KB 目安超過、works の README がほぼ空）。push は 3 リポジトリとも済み（works `d992612`、resources `4bff9ce`、dotfiles `63e3ef2` が `origin/main` に含まれる。2026-10-16 確認）。deny のパターンは、コミットメッセージ中の禁止語にも一致する（絞り直しは git の見直しで）。
4d. **この PC の works を worksample の clone に切り替えた（2026-10-16。済み）**: 詳細は `log-history.md`。バックアップのブランチ `init-local` は不要になったら削除する。
4e. **下流から works への依存の整理（2026-10-16。済み）**: 方針は `decisions.md` の項。任意の残り: dotfiles の `profile.ps1`（`dof` `room`）の `$WORKS_DIR` 化。
4f. **3 リポジトリの cwd を揃えた（2026-10-16。済み）**: 起動はトップの 3 つだけ、下位は「〜の続き」。works の `.claude/settings.json`（deny）を置いた。deny の実機確認は済み（2026-10-16。`areas/` の `Read` は拒否、PowerShell の `Get-Content` は通る。kit の `init-workspace.md` を更新した）。`guides/` は後回し（cwd を増やさない）。`handson/` は削除予定。公開リポジトリへの push を許可した（`decisions.md`）。
5. **保留**: 旧 `C:\vault` と GitHub の旧 `notes` の削除、`claude --resume` の確認、WSL の `WORKS_DIR` の実機確認（詳細は `log-history.md` の Next Actions）。

## Open Questions

- Claudian（2026-10-11）: Bedrock を使う別 PC で、dotfiles の `settings-bedrock.txt` を Bedrock のスニペットへ貼り、複数行が保存されて接続できるか確認する。このスニペットの値は手書きのサンプルで、`settings-bedrock.json` が正（`docs/decisions.md` の先頭の項目）。
- Claudian の設定（2026-10-12）: `claudian-settings.json` は dotfiles の symlink（Windows は `30_link.bat`）。別 PC では dotfiles を pull して `30_link.bat` を実行する（実ファイルがあると `[ERR]`。退避してから）。ネイティブ Linux は未対応。
- 公開範囲（2026-10-16 に `gh repo view` で確認）: `worksample` は PRIVATE、`workbase` と `dotfiles` は PUBLIC。公開のまま、エージェントが push してよい（ユーザーの決定）。10-08 の PUBLIC と 10-11 の PRIVATE の食い違いの原因は未確認。
- `workbase` は公開済み。公開前提で書く。クラウドから作業側へ push してよい（ユーザー、2026-10-08）。
- **公開リポジトリの git 履歴に、ユーザー名を含むパスが残っている**（`workbase` は公開済み）。ユーザー名を含むパスは、xmem の現行ファイルからは除いた（10-15）。git 履歴には残っているので、履歴の書き換え（git filter-repo など。force push が要り、現在は禁止）で消すか、残すかを決める（未決）。
