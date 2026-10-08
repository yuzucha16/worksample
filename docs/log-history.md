# 作業ログの経緯（log-history）

2026-10-08 に、`docs/log.md` から分けた。**開始時に読まない**（必要なとき検索する）。`docs/log.md` は現在状態だけを持つ。新しい経緯は、この下の `## Log` の先頭に、日付の降順で追記する。下の `## Next Actions` と `## Open Questions` は、分割前の全文（2026-10-08 時点。現行は `docs/log.md`）。


`works`（旧 `notes`。Obsidian Vault のトップ。PC ローカルのリポジトリ。PARA 構成）の現在状態と次にやること。2026-10-05 に、共有部分を別リポジトリ `workbase`（`resources/` に clone）に分け、`.obsidian/` を dotfiles へ戻した。対象は、Vault 全体の管理: `resources/exmem`（ナレッジ）、`resources/workflow-kit`（共通機能）、その他の `resources/`、`.obsidian/`（Obsidian の設定。実体は dotfiles）。判断の根拠・却下案・Gotchas は `docs/decisions.md`。作業の終わりに、Next Actions と Log を更新する。

`.obsidian/` の 2026-10-04 以前の Log は、git 履歴（`notes` の `git log -- .obsidian`、dotfiles の `bbb294b`）から復元したもの。コミットメッセージと差分から読み取れる範囲で、書かれていない理由は「不明」としている。dotfiles 側の 2026-10-02 より前の履歴は、履歴の作り直し（単一コミット化）で残っていない。

## Next Actions

- **目的の置き直しと規模の凍結（2026-10-08 開始。判定日 2026-11-08）**: 判断は `docs/decisions.md` の先頭の項目。残りは次の点。
  1. 週 1・15 分の `review`。見るのは `again` と `gap` の事例だけ（`extract-threads.ps1 -Report` で `again`・`detour`・常時読み込みの字数が出る）。
  2. L1（リポジトリ構成）の第三者レビュー依頼文は作成済み（`docs/drafts/review-l1-structure-third-party-prompt.md`。案 A〜E）。結果が来たら `docs/drafts/review-l1-structure-result.md` に置いてもらい、L2 以降の依頼に反映する。
  3. 常時読み込みの縮小（`log.md` の退避が先頭）と、kit の `adopted` の記述の整理（1 つ足すなら 1 つ畳む）。

- **権限移譲の試験運用（2026-10-08 開始）**: 残りは次の点。
  1. 1週間後を目途に、最初の `review` を行う（自動採用の規則、台帳による転記の一括確定。`reviews.csv` に1行）。
  2. 試験期間は2週間（2026-10-22 まで。期間末に継続・修正・撤回を判断する）。`workbase` と dotfiles は push の対象外のまま。`wrap` の棚卸し（`check-docs.ps1`）を `review` へ移すかは、`review` を数回試してから判断する（それまで `wrap` に残す）。
  3. 第三者の意見（転記の時系列整合）は反映した（kit 版 `2026-10-08.4`。Log）。試験期間中は、`review` を3〜4日おきに実行する（最初の `review` から、ハッシュの不一致の頻度を測る）。
  4. `summarize.ps1` が、自動採用の行（`basis` に `auto`）を分けて集計するようにする（今は、手で除いて読む）。
  5. 台帳に記録が無い、2026-10-08 より前の統合済みメモ（`exmem/inbox/` に未統合の 4 件など）は、従来の方式で確定する。

- **Vault を `$HOME\works` へ移した後の残り（2026-10-06 に移行を実行。新しい場所で Obsidian と Claude Code の動作を確認済み。2026-10-06 時点）**: 残りは次の点。
  1. 旧 `C:\vault` の削除は保留（ユーザーの指示）。旧 `notes` の完全な履歴 58 コミットが残るバックアップ（`C:\vault\backup\notes-before-restructure-20261005`）と旧 clone を、`claude --resume` で旧セッションが復活するかの試験に使う（過去に成功した例が無い）。試験の後に、削除の可否（下の「段階5の残り」）を決める。
  2. exmem の `obsidian-vault.md`（現行の記述: 環境変数 `WORKS_DIR`、トップのパス、構成図、`.obsidian` の表）などのナレッジの旧パスは未着手。移行のナレッジは inbox のメモ 2 件（下の Log）にして、「inboxを整理して」で統合するときに、`obsidian-vault.md` の現行の記述も直す（`knowledge/` の編集は exmem 側の運用）。
  3. 実機の WSL で、新しいターミナルを開いて `echo $WORKS_DIR $GHQ_ROOT` を確認する（`WORKS_DIR` が `/mnt/c/Users/<名前>/works`、`GHQ_ROOT` が `~/works/repos` になること。`WSLENV` の受け渡しは実機で未確認）。既存の WSL の `~/vault`（旧 `GHQ_ROOT`。中の clone があれば）は動かしていない。`mv ~/vault ~/works` で移すか決める。
- **PARA の使い方の検討（2026-10-06 開始。A・B・C は承認済み。D の1回目（最初の Project）を閉じた。2026-10-06 時点）**: 残りは次の4点。
  1. 承認待ちの改善案は無い（2026-10-06 に全件承認）。次の改善案は、2回目の実測から出す。
  2. open の手順書の下書き（`docs/drafts/project-open.md`）を、2回目で実測して直す。
  3. 2回目の Project（`learn-c-pool-allocator-m0`）を、2026-10-07 に閉じた（Log。`bare` の回）。3回目以降の候補は `areas/learning/README.md`。「ほかに前提はありますか」の効果は、2回目の実測を Log に書いた（補足は 1 件、漏れは別の軸で 1 件）。作業の種類（文書作成・開発）の定型化は、2〜3回の実測がたまってから設計する。承認待ちの改善案: 開発のインタビューに「最適化・チューニングの軸と、測る対象の操作」を足す（`events.csv` の `2026-10-07-s2-i01`）。
  4. 試行で、上限（Project 3・Area 5）と契機を見直す。kit への昇格と PC1 への投入は、安定してから判断する。
- **フック名の整理の後始末（2026-10-08）**: `resources/AGENTS.md` と他の作業ディレクトリの旧名の参照を、名前が定着した後に一斉に直し、旧名のファイルを削除する（Log 2026-10-07 の「残り」）。
- **スレッド・セッションの指標（2026-10-06 開始。試験運用）**: 残りは次の3点。
  1. 手順（`extract-threads.ps1` → `sessions.csv` に1行 → `-Report`）を、s7 の終了処理で初めて通した（Log）。2回目以降で、並行する別のトライアルのスレッドがある場合に、`-Current`（最も新しく更新された会話）が外れないかを確かめる。当日の s1〜s6 の紐づけは、会話 ID の対応が曖昧なので backfill しない。
  1b. **`bare` → `briefed` の2回の比較は完了した**（2026-10-07。Log の総括）。結論の要旨: 背景を揃えると質問は減るが漏れは減らず、漏れは作業の種類に固有の前提。次は、差分項目を入れた手順書で同種の漏れが出ないかを、office-admin や learning の実務を進めながら測る。kit 化は、今の形でよいと決まり、フック名の体系も決まった（2026-10-08。Log）。実装（kit のファイル名・定義・雛形・`AGENTS.md`）が次。承認待ちの改善案は無い。
  2. 数回回して、`prompt_complete` の取り方（最初の依頼の完備度の数え方）、30分の打ち切り、無駄の合図の閾値（エラー率20%、放置3日）を実測で見直す。
  3. 安定したら、`closing-hook.md` への昇格（kit の改善フックで、ユーザーの承認を得る）を判断する。
- **統合待ち（2026-10-06 時点）**: `exmem/inbox/` に未統合のメモは無く（`README.md` のみ）、`転記待ち` も 0 件（`works` と `archives/learn-c-pool-allocator`。2026-10-06 の「inboxを整理して」と突き合わせで進めた）。次回以降、メモが溜まったら「inboxを整理して」で統合する。
- **docs のデータの行き先の仕組み（kit 版 `2026-10-06.13` に反映済み。2026-10-06 時点）**: 残りは次の2点。
  1. 滞留の候補を探す（今は0件）。一般化を試みて難しい項目が見つかったら、`滞留（理由）` にする。
  2. PC1（会社 PC）への展開の実測。`転記待ち` の【汎用】項目を grep して、一般化した短文を画面に出し、ユーザーが目視で運ぶ手順を、1回通して確認する（手順は kit の `docs-rules.md`）。他の作業ディレクトリ（dotfiles など）の `decisions.md` への印付けは、必要になったときに行う。- **`works` への移行の残り（2026-10-06 時点）**: 移行は完了した（Log 2026-10-06）。残りは次の2点。
  - 旧セッション `bc9d6801-…` の `claude --resume` が `works` で通らない原因を調べる（任意。通らなくても、旧パスの履歴は `C:\Users\ck\.claude\projects\C--vault-notes-*` に残っている）。
  - 各 `resources/*/.claude/settings.local.json`（端末ごとの許可設定。追跡しない）に、旧パスの許可項目が残っている。害はない。気になるときに整理する。
構造変更（`docs/decisions.md` の「Vault のトップを PC ローカルのリポジトリにし…」）。段階1〜4は実施済み（2026-10-05）。残り:
- 段階5の残り: 旧 `notes`（GitHub 側はアーカイブ化済み）の扱い。GitHub 側を削除する案を検討中（ユーザー。2026-10-06。他の PC は未導入なので、他 PC の未 push は無い）。手順の案: ① `git bundle create <名前>.bundle --all` を旧ローカル clone（`C:\vault\repos\github.com\yuzucha16\notes`）で作り、`git bundle verify` で検証して、`C:\vault` の外にも置く（完全な履歴 58 コミットは、GitHub・旧 clone・バックアップ `C:\vault\backup\notes-before-restructure-20261005` にしか無い。`workbase` は 30 コミットの切り出し） ② 旧 clone の未追跡メモ（`exmem/inbox/2026-10-05-obsidian-explorer-color-and-indent-limits.md`。`obsidian-appearance.md` に統合済みに見えるが、突き合わせは未実施）を確認 ③ GitHub 側を削除（復元期間は設定画面で確認） ④ 旧 clone は復元期間が過ぎてから削除（Claude の履歴キー `C--vault-repos-github-com-yuzucha16-notes*` 4つの扱いも決める） ⑤ `docs/decisions.md` の「アーカイブとして残す」を撤回済みにし、`obsidian-vault.md` に旧 URL が無効になったことを1行足す ⑥ バックアップは、bundle の後に最後に消す候補（`projects/link-management` が退避先と一致するか確認してから）。
- `projects/link-management` は、ユーザーが退避した（2026-10-05、ユーザーの回答）。バックアップ（`C:\vault\backup\notes-before-restructure-20261005\projects\link-management`）にも残っている。
- ネイティブ Linux の実機で、dotfiles の `30_link.sh`（`.obsidian` の symlink）、`50_repos.sh`（`workbase` の clone）、`WORKS_DIR` の既定値（`~/vault/works`）を通して確認する（WSL は一時ディレクトリで試験済み）。ワークスペース生成フックの既定の対象 `C:\vault\works` は、ネイティブ Linux では使えないので、対象を言葉で指定する。
- 後で見直す: `cheatsheets/` と `handson/` を `workbase` に置くこと。

導入と共通機能（workflow-kit）:
- 新しいセッションが、作業を始める前に `docs/log.md` を開くか確認する（読む時機の書き分け後。トリガーが来たときに kit のファイルを開くことは確認済み）。
- Claude 用スキル（導入フックと「ナレッジ化して」の入口）を作る（次回以降。TODO）。
- WSL（`/mnt/c/...`）からの kit 参照と、ネイティブ Linux での `notes` の場所を確認する。
- kit の版（`README.md` の「版」）を変えたとき、モバイル用プロンプトと見本の `kit:` を合わせる。次に「ナレッジ化して」を実行したメモに、`kit:` が入っているか確認する（初回の実測）。
- `docs/log.md` の書式が、日報・週報・仕様書の入力として足りるか確かめる（将来）。ナレッジの見直し・マージの契機を仕込む（将来）。

exmem:
- 統合後の `knowledge/` を、`contexts/` の消化と、ナレッジの見直し・マージの観点で見直す（将来）。
- `exmem/README.md` が、今回の変更（kit、`contexts/` の定義）と合っているか確認する。
- `contexts/`（`notes` から見えない場所の引継ぎコンテキスト）を消化する手段を決める。
- 今日の最初の3メモを、新しい下限（Principles と Decisions が合わせて3項目以上）の基準で見直す。

`.obsidian/`:
- `plugins/colored-tags/data.json` は、追跡する（判断基準5項目で確認済み。`docs/decisions.md`）。新しいタグを使い始めたコミットに、追記分を含める。現在も、新しいタグ6件の追記が未コミットで出ている（2026-10-04 の `git diff` で確認）。

コミット（ユーザーが行う）:
- 上の「構造変更」のコミットと push のほか、`.obsidian` の変更は、今後は dotfiles にコミットする（接頭辞 `[obsidian]`）。
- `docs/` は、新しいトップのリポジトリで追跡する（共有の `workbase` には載らない）。

## Open Questions

- 提案（未承認。開始インタビューの手順。2026-10-06 の試行から。`docs/metrics/events.csv` の `2026-10-06-s2-i01` `-i02`）:
  1. 「触ってよい範囲」（この Project、dotfiles、kit、`resources/` など、リポジトリ・ディレクトリ単位の許可）を、「やらないこと」から独立した項目にする。根拠: 今回の「やらないこと」の選択肢が、リポジトリの変更の許可を混ぜていて、ユーザーに直された。
  2. 答えが1つに定まる項目（進行中の Project が1つだけ、環境で確認済み、など）は質問せず、ゴールの要約に宣言して、反対があるときだけ受ける。根拠: 今回の冗長な2問は、既定値を選ぶだけだった（冗長率 50%）。
- 提案（未承認）: `AGENTS.md` の固定パス（`C:\vault\works\...`）を `$WORKS_DIR` に置き換える（Linux での値は未確認）。
- `workbase` の公開範囲（最初は非公開で作る。公開するときは exmem に会社固有の情報が無いか確認する）。
- 決定の記録の書式に、状態（提案／決定）と出典（ユーザーの発言／AI の提案）の欄を持つべきか。部分的な指示の範囲確認の手順を、共通機能に足すか。

## Log

### 2026-10-08（フックの章立ての統一）

- ユーザーの依頼（8つのフック手順書の章立てを、見やすさと整合性のために統一したい）に、現状把握 → 章構成案 → 選択肢 → 適用判定の順で進めた。ユーザーが、全章の厳密な統一から「共通部の一致」へゴールを緩和し、「今回は既存の文言を修正しない。新章の追加は許容」と示した。論点（start の「改善の流れ」は新章から指す、体裁の空行は直す、点検スクリプトは同じコミット）は承認された（判断は `docs/decisions.md` の先頭の項目）。
- 実装: `resources/`（`workbase`）の `e2caad2`。open・close・start に制約・報告の型・改善、review に報告の型を新章で追加。点検 `tools/check-hook-outline.ps1`（8ファイル OK。変更前は4つが FAIL）。追加108行、削除0行。`workbase` は push していない（ユーザーが行う）。
- ナレッジ化: `exmem/inbox/2026-10-08-hook-outline-common-section-check.md`（点検は FAIL 0、WARN 0。コミットしていない）。
- 終了処理（`wrap`）: `works` の push は、`gh repo view` が `PUBLIC` を返したため、条件 1（非公開）を満たさず止めた。`AGENTS.md` の「非公開」の記述と食い違う。
- 追加の決定: kit 自身の作業の `stock` は、一般化できる進め方と判断の型だけを残す（`stock-hook.md` 手順 2。`resources` の `f78904d`。判断は `docs/decisions.md`）。
- 残り: タイトル書式の統一と新フック雛形の提案は、ユーザーが「忘れてください」と言ったので扱わない（メモの Open Questions には残っている）。規模の凍結に対して、畳んだものが無い。

### 2026-10-08（Project の構造の設計。セッション `2026-10-08-s2`）

- ユーザーの依頼（`start`/`open` で作る Project の中身を、浅いフラットな構造で固定したい）に、素案を出した。ユーザーが、①type は3種（`doc` `dev` `research`）②下書きは `docs/` から `drafts/` に分ける ③kit に反映、を承認した（判断は `docs/decisions.md` の先頭の項目）。
- 実装: `resources/`（`workbase`）の `3e9e63e`。`open-hook.md` に「Project の構造」の節と手順 3・4 の追記、`templates/project/README.template.md` を新設、`start-hook.md` の差分の項目を `type` と対応づけた。`workbase` は push していない（ユーザーが行う）。
- 残り: `research` と混合の Project は実測が無い。`write-pc-loan-procedure` は、下書きが `docs/` のまま（閉じるときに扱う）。次の `open` で、type の聞き方とひな形を実測する。

### 2026-10-08（第三者レビューを受けて、台帳方式を直した。セッション `2026-10-08-s1`）

- 終了処理（`wrap`。試験運用の初回）: ① 棚卸し: `works` は FAIL 0、WARN 0（`未仕分け` 0、`転記待ち` 2、`転記済` 43）。② ナレッジ化: `exmem/inbox/2026-10-08-hook-authority-delegation-ledger.md`（Principles 7、Decisions 4、Facts 6、Gotchas 3。点検は FAIL 0、WARN 0。コミットしていない）。権限移譲の項目は `転記待ち（…、本文ハッシュ f0556ecb）` にした（ハッシュ付きの最初の項目）。③ 改善: 自動採用の規則 `R-20261008-1` を1件足した（kit 版 `2026-10-08.5`、`4d9e474`。並行セッションの未コミットの編集が、コミットに混ざるのを防ぐ。このセッションの混入の実例から）。承認を求める案は無い。④ 指標: `threads.csv` を更新（65件）、`sessions.csv` に `2026-10-08-s1` を足した。⑤ push: `works` は許可リストなので、条件を確認して push する。`workbase`（kit `4d9e474`、`98fa69c`）は対象外なので、ユーザーが push する。

- ユーザーの相談（`wrap` の改善案の承認、push、転記の往復を、エージェントに移したい）に、影響分析を出した。結論は一律でなく線引き。ユーザーが、①安全規則は承認制のまま ②push は `works` のみ ③転記は台帳方式、を決め、見直しのフックを `review` とし、チェック機能をここに集約する方針を示した（判断は `docs/decisions.md` の先頭の項目）。
- 実装: kit 版 `2026-10-08.3`（`resources/` の `6307c31`）。新設 `review-hook.md`、`wrap-hook.md` に「自動採用の範囲」「自動採用の規則」の節と push の手順、`docs-rules.md` の「push」（許可リストと5条件）、`integrate-hook.md` の台帳、`exmem/integrated.md`。`works`: `AGENTS.md`（許可リスト、`review`）、`docs/metrics/reviews.csv` `rule-hits.csv`、`events.csv`（`2026-10-08-s1-q01` `q02`）。
- 試験の状態: 自動採用の規則は 0 件、台帳は空、`review` は未実行。`works` の push は、このコミットが最初の実測。

### 2026-10-07（`briefed` の回の総括。セッション `2026-10-07-s3` と `s2` の比較。総括のセッションで記述）

- `briefed` の回（`2026-10-07-s3`。Project `write-pc-loan-procedure`、Area `office-admin`。文書作成）の記録が揃った。最初の依頼にゴール・完了条件・制約・やらないことがすべて入り（`prompt_complete` 4）、開始インタビューは 5 問で済んだ（`bare` の s2 は 8 問）。v2 をゲート承認して html まで作った（Project は未クローズ。未記入の欄は運用で埋める）。能動時間は約 8 分（最初のプロンプトから最後まで約 32 分）。ユーザーの評価は「約15分でこの水準は精度が高い」。
- 漏れ(`gap`)は 3 件、すべて起因 `ai`: ゲート承認の判断基準（`s3-g01`）、骨子のすり合わせ（`s3-g02`）、図の要否と水準（`s3-g03`）。改善案 `s3-i01` `s3-i02` は承認済みで、手順書の下書きの「文書作成」の差分に反映した（`1acc423` `70349a4`）。
- 総括（n=1 ずつ。作業の種類が違うので、傾向を見る程度）: ① 背景を揃えると質問は減る（8 → 5）が、漏れは減らない。漏れたのは、作業の種類に固有の前提（開発: 評価の軸、文書: 判断基準・構成・図）で、最初の依頼の完備度では補えない。手順書の「作業の種類の差分」が効く部分。② 質問の適合率は `briefed` の方が低い（20% 対 75%）。質問が絞られ、残る質問が選択肢の外から補われやすい可能性があるが、未検証。③ 「ほかに前提はありますか」は補足を拾えるが、判断基準・構成・図のような AI 側が項目として持つべき前提は拾えない。④ 効果の検証は、差分項目を入れた後に、同種の漏れが出ないかで行う。
- ユーザーの所感（2026-10-07）: このテストは二重の意味で良かった。a) メトリクスを取る意味を見いだせた。b) 実務をやりながら、仕組みを育成できる可能性を感じた。方針: office-admin や learning の実務を進めながら、「作業を始めて」の改善プロセスを回す。
- ユーザーの見解（2026-10-07 時点。2026-10-08 に決定へ進んだ。下記）: 今の形で kit 化してよい。ただし、フック名は整合させたい（現状は「作業を始めて」。ほかのフックは「〜して」の形で、`knowledge-hook.md` 等の名前と並べる）。kit 化の範囲・名前・時機は、次に相談する。
- フック名の体系を決めた（2026-10-08。ユーザーの決定。`docs/decisions.md` の先頭の項目）: `init` / `open`・`close` / `start`・`wrap` / `stock` / `integrate`。`open` は `start` を呼び、`start` は単独でも呼べる。`end` は紛らわしいので `wrap`。日本語のトリガーは別名に下げる。スレッドの open / close ではなく、Project の寿命だと既存の定義で直した。kit 化の範囲（手順本体と共通の項目を入れ、差分は試験運用と明記）と、改善ループ（実務の漏れは works に記録し、承認したら kit を直す）も、ユーザーが賛成した。実装（kit のファイル名・定義・雛形・`AGENTS.md` のトリガー）は、次の作業。
- 実装した（2026-10-08。セッション `2026-10-07-s4`）: ① kit（版 `2026-10-08.1`、`ac7d574`）: `closing-hook.md` → `wrap-hook.md`、`knowledge-hook.md` → `stock-hook.md`、`setup-hook.md` → `init-hook.md`（旧名は案内だけ）、`start-hook.md` `open-hook.md` `close-hook.md` を works の下書きから一般化して追加（試験運用）、README に「フックの体系」、雛形 2 つの呼び出し行、`improvements.md`。② works（`df7b10a`）: `AGENTS.md` の呼び出し行、`docs/decisions.md`、この log、`docs/drafts/` の 3 つに「正本は kit」の注記、`events.csv`（`2026-10-07-s4-q01`〜`q04`）。モバイル用プロンプトと見本は、メモの形式が変わらないので `kit:` を据え置き、参照先だけ `stock-hook.md` に直した。
- 残り: ① `resources/AGENTS.md`（`workbase` の規約）の呼び出し行が旧名のまま（案内ファイル経由で動く）。② dotfiles など他の作業ディレクトリの `AGENTS.md` も旧名のまま。名前が定着した後に、旧名のファイルとあわせて一斉に直す。③ 実務（office-admin、learning）で `start` を使い、漏れを `events.csv` に記録して、承認後に kit を直す。④ `wrap-hook.md` の手順 4 と 5 の重複は、ユーザーが承認して直した（kit 版 `2026-10-08.2`。`events.csv` の `2026-10-07-s4-i01`）。

### 2026-10-07（2回目の Project `learn-c-pool-allocator-m0` を閉じた。セッション `2026-10-07-s2`。`bare` の回）

- 「作業を始めて」（背景なし）から始め、open（Cortex-M0 対応。`projects/learn-c-pool-allocator-m0/`）、実装（`feature/m0-no-div`）、速度のチューニング（`feature/m0-speed`）を行い、どちらも main にマージし（`3891cae` `2d83649`）、close の手順で `archives/learn-c-pool-allocator-m0/` へ移した。完了条件（`make check` と実測値の記録）はユーザーが達成を確認した。結果: M0 / M0+ の `.text` は 612（libgcc 込みの現状）→ 352、M3 / M4 は 288 → 280。速度は、乗算 32 サイクルの M0 で `pool_free` 563 → 103、`pool_alloc` 41 → 17、`pool_check`（64 ブロック）33,910 → 5,745（命令シミュレータの値。実機は未確認）。詳細は `archives/learn-c-pool-allocator-m0/docs/log.md` と `decisions.md`。
- 指標（`live`）: 聞き取り 8 件（回答率 100%、修正 0、補足 2、適合率 75%、冗長率 0%。補足の起因は 2 件とも `user`）、承認の確認 3 件（補足 1）、漏れ（`gap`）1 件（`s2-g01`: 「チューニング」を、確認せずにサイズの削減と解釈した。起因 `ai`。ユーザーに指摘され、速度で測り直した）。`reversed` は、採用済みの 11 行を 0 に確定した。改善案 `s2-i01`（開発のインタビューに、最適化の軸と測る対象の操作を足す）は、承認待ち。
- 「ほかに前提はありますか」の効果（1回目 `s6-i01` の導入後の実測。n=1）: 宣言した前提への直しを 1 件拾った（M0 は静的な切り替え、フットプリント優先、動いてからチューニング）。ただし、「チューニング」が速度であることは、この自由記述でも拾えなかった（語の定義でなく、前提の宣言に直しを求める形のため）。
- 手順書への所見: close の手順 6 で、ディレクトリごとの `git mv` が、再び `Permission denied` で失敗した（2回目。Claude の作業ディレクトリが対象の中だった可能性は、今回は無い: 作業ディレクトリは `works` に戻していた）。ファイル単位で移し、空のディレクトリだけが残ったので削除した。手順 7 の集計で、`events.csv` の 1 行（`s2-g01`）の列数が 1 つ足りなかった（AI の記録ミス）ので直した。
- 改善案 `s2-i01` を、ユーザーが承認した（開始インタビューの手順書の下書きに反映。`68ef5f6`）。終了処理のフック全体は、パイロット版のため実行せず、指標の手順だけを実行した: `threads.csv` を更新（59 件）、`sessions.csv` に `2026-10-07-s2` を 1 行（スレッド `1eced69d`、`bare`、`outcome` 達成、`prompt_complete` 0、`review` 1、`mechanism` 1。`-Current -Cwd` の警告（並行の可能性）は出なかった）。ツールエラー率は 11 / 185 で、20% 未満。`bare` → `briefed` の順の、1回目（`bare`）の記録は、これで揃った。
- 終了処理（「終了処理して」）の、棚卸し・ナレッジ化・kit の改善は、実行していない。ナレッジ化の候補は、`decisions.md` の項目がすべて `local` なので無い。再利用できる知見の候補（乗法の逆元による可除性の判定、曖昧な「チューニング」の軸の確認）は、ユーザーが言ったときに、終了処理かナレッジ化で扱う。

### 2026-10-06（Vault のトップの rename `notes` → `works` が exmem と workflow-kit に与える影響を点検した。セッション `2026-10-06-s9`。終了処理は 2026-10-07）

- ユーザーの依頼で、rename（当時は `C:\vault\works`）が exmem と workflow-kit に悪影響・デグレを起こさないかを点検した（旧名の grep、スクリプト、git の状態、追跡外ファイルの確認）。結論: 機能面のデグレは無い。`workflow-kit/tools/check-inbox.ps1` と `find-knowledge.ps1` は `$PSScriptRoot` からの相対参照で、実行して動作を確認した。workflow-kit の旧パスは `README.md` と `improvements.md` の履歴の行だけ。`resources/` の remote は `workbase` のまま、作業ツリーは clean。`.claude/settings.local.json` は追跡外で、旧パスの許可項目が残るが害は無い（確認: 2026-10-06、根拠: `Grep`、スクリプトの実行、`git status`）。
- 現在形のまま残っていた旧パス・旧名を、ユーザーの承認で直した（`workbase` の `4ee2d40`、6 ファイル。`claude-code-storage.md`、`context.md`、`workflow-kit.md`、`ai-development-workflow.md`、`app-config-placement.md`、`obsidian-vault.md`）。方針は既存の決定（現在形は新名、日付つきの履歴は書き換えない。`docs/decisions.md` と exmem の `obsidian-vault.md`）。承認の前に、ユーザーから「時制で揃えると過去に決めた」と補足された（質問する前に、既存の決定を確認すべきだった。`docs/metrics/events.csv` の `2026-10-06-s9-q01`）。
- 同日の夕方に、Vault を `$HOME\works` へ移す別のセッションがあり、この修正で書いた `C:\vault\works` の現在形の記述は、`0e75bed` で `$HOME\works` に直された（確認: 2026-10-07、根拠: `git grep` で、残る `C:\vault\works` が日付つきの履歴だけであること）。
- 「ナレッジ化して」は実行しなかった。再利用できる知識（旧名の時制の方針、rename の影響の点検の観点）は、既存のナレッジ `obsidian-vault.md` と既存のメモに入っている。
- 終了処理の改善 1 点を、ユーザーの承認で kit に反映した（版 `2026-10-07.4`）。`closing-hook.md` の手順 2 に、変更したリポジトリに `docs/` が無く、親のワークスペースに `docs/` があるときは、親の `docs/` を対象にする、と足した（`docs/metrics/events.csv` の `2026-10-06-s9-i01`。判断は kit の `improvements.md`）。

### 2026-10-06（Vault を `C:\vault\works` から `$HOME\works` へ移した。固定パスを直した。kit 版 `2026-10-06.23`）

- `migrate-works.ps1 -Execute` で移行を実行した。新しい `C:\Users\ck\works` で、Obsidian が動くこと（ユーザーの確認）、Claude Code が動くこと（`CLAUDE.md`・`AGENTS.md`・メモリを読めた、git の root と remote が `worksample`、`resources/` と `.obsidian` のジャンクションが生きている。確認: 起動したセッションで）を確認した。判断の根拠は、Next Actions の旧項目（Vault を `$HOME\works` に、ghq の root を `$HOME\works\repos` にし、`C:\vault` の親を畳む。ユーザーの決定）。
- `resources/` の固定パスを直した（ユーザーの指示）。kit は、`setup-hook.md`、`knowledge-hook.md`、`integrate-hook.md`、README、`templates/`、`examples/` を `$HOME\works`（WSL は `/mnt/c/Users/<Windows のユーザー名>/works`）に、版を `2026-10-06.23` にした（コミット `7973a52`）。履歴の記述（過去の版の項目、`improvements.md`）は、当時のまま残した。`exmem/knowledge/modern-cli-tools.md` の現在地の1か所も直した。`AGENTS.md`、`exmem/AGENTS.md`、`exmem/README.md`、`cheatsheets/` の現行の記述はコミット `c418105`。`cheatsheets/CLAUDE.md` の文字化け3か所は、HEAD に戻してパスだけ直した（原因は未特定のまま）。
- 続けて、kit の `templates/workspace/gitignore.template` に `/repos/` を足し、版を `2026-10-06.24` にした（`resources/` のコミット `c77e698`）。dotfiles の移行の変更は、`[env]`（`92fd142`。`10_env.bat`、`home/.profile`、`scripts/linux/`、`tests/`、`startup.bat`、`terminal/settings.json`）と `[docs]`（`5d59374`。`AGENTS.md`、`README.md`、`docs/decisions.md`）の2つでコミットした。Obsidian が書き換えた `windows/obsidian/.obsidian/plugins/colored-tags/data.json` は、このコミットに含めず、未コミットのまま残した（接頭辞 `[obsidian]` で別にコミットする）。
- Linux 側も `~/works`、ghq の root を `~/works/repos` にそろえた（ユーザーの指示。dotfiles のコミット `b6c26c9`。WSL の `GHQ_ROOT` の既定、`10_dirs.sh`、README、試験）。dotfiles の試験は 51/51 合格（最初は 49/51。`50_repos.sh` の `ghq get` が `a88d23b` でコメントアウトされたのに、試験が `ghq` の呼び出しを期待したままだったため、試験を直した）。Obsidian が書き換えた `colored-tags/data.json` は、`841672b` `[obsidian]` でコミットした。判断は `docs/decisions.md` の「Vault のトップを `C:\vault\works` から `$HOME\works` に移し…」。
- 確認の質問への回答: 「workflowを導入して」の固定パス `C:\vault\works` は、変更済み（`7973a52`。`setup-hook.md` の既定の対象は `$HOME\works`）。`setup-hook.md` のコミットメッセージ例 `[vault] initial commit: ...` は、旧名のまま（パスではない。改善案として終了処理で提案した）。
- 終了処理（2回目の移行作業）: ナレッジ化で、`exmem/inbox/` にメモ 2 件を作った（`2026-10-06-windows-wsl-shared-workdir-layout.md`、`2026-10-06-powershell-script-file-rewrite-guard.md`。コミットしていない。`check-inbox.ps1` は PASS 50、FAIL 0、WARN 0）。上の決定と事故の Gotcha の行き先は `転記待ち`。
- 終了処理の改善案 2 点を、ユーザーが承認した（`events.csv` の `s8-i01` `s8-i02`）。kit 版 `2026-10-06.25`（`resources/` のコミット `f072c64`）: `docs-rules.md` に「長い Markdown の書き換えは Edit ツールで行う」を足し、コミットメッセージ例の接頭辞 `[vault]` を `[works]` に直した。
- exmem の旧パスを一度きれいにした（ユーザーの依頼。`resources/` のコミット `0e75bed`）。`obsidian-vault.md` は、現在形の記述（構造の図、環境変数、現在の状態）を `$HOME\works` に直し、第2の変更の説明を足した。日付つきの履歴の `C:\vault\...` は、当時のまま残した。ほかに、`workflow-kit.md`、`pc-setup-manuals.md`、`wsl-file-placement.md`、`claude-code-storage.md`（試験の手順の1行）、`contexts/ai-development-workflow/context.md`、`cheatsheets/env/debian-family.md`（WSL の `~/works/repos`）を直した。移動の原則・決定は、inbox のメモ 2 件が持つので、`obsidian-vault.md` には複製していない（次の「inboxを整理して」で統合する。`powershell-script-file-rewrite-guard` の「提案: Edit で書き換える」は、承認済み（kit に反映）なので、統合のときに Principles として扱える）。
- 直さなかったもの: `resources/*/.claude/settings.local.json`（端末ごと・追跡しない。旧パスの許可項目で、害は無い）、exmem の `obsidian-vault.md` など日付つきの確認記録を含むナレッジ（ナレッジ化の対象）。
- 作業中の事故: 手元で `docs/log.md` を書き換えるとき、置換の手順の誤りでファイルが空になった。`git checkout` で HEAD に戻し、ユーザーの未コミットだった Next Actions の項目（移行の準備の記述）は、実行後の残りの記述に書き直した（準備の詳細は、dotfiles の未コミットの差分と `migrate-works.ps1` にある）。再発防止: 長い Markdown の書き換えは、スクリプトではなく Edit で行う。

### 2026-10-06（終了処理の改善 3 点を kit に反映した。kit 版 `2026-10-06.20`）

- ユーザーが、終了処理の改善案 3 点を承認し、kit を版 `2026-10-06.20` に上げた（`workbase` の `9fabb9b`）: ① `closing-hook.md` の手順 2 に、リポジトリの中の Project・Area の `docs/` を、別の対象に数えると明記、② `check-inbox.ps1` の「Decisions に AI の提案が混ざっていない」の WARN を、「AI の提案」と「未承認」が同じ行、または `- 提案:` で始まる行に絞った（試験: 誤検知の例が 1 → 0、検出すべき 2 例は WARN のまま、実メモ 3 件は FAIL 0・WARN 0）、③ 手順 7 に、`転記待ち` を `docs/` ごとと合計の両方で報告し、勧める閾値は `docs/` ごとに見ると明記。判断は kit の `improvements.md`。`events.csv` の `s6-i02`〜`i04` を承認済みにした。承認待ちの改善案は無い。

### 2026-10-06（「inboxを整理して」の後の突き合わせ。`転記待ち` の処理。セッション `2026-10-06-s7`）

- ユーザーが「inboxを整理して」を実行し（`exmem` の `290ad22`）、`転記待ち` 12 件の `転記済` への突き合わせを指示した。`archives/learn-c-pool-allocator` の 7 件（原則 2、事実 3、Gotchas 2）は、`exmem/knowledge/embedded-c-constraint-checks.md` の本文と突き合わせ、ユーザーの承認で `転記済` にした（本文を外した）。
- `works` の 5 件は、転記先に欠落と誤りがあった: 元に無い却下案（AI が補ったもの）が 2 件、開始インタビューの項目・フックの先後・セッションの定義・記録の確度（`live` `backfill` `import`）・用語・指標の構成・開始の形の比較の欠落。ユーザーの指示で、`exmem/knowledge/para-operations.md` と `ai-work-metrics.md` を直した（`workbase` の `062a7e7`）。`works` の 5 件も、ユーザーの承認で `転記済` にした（本文を外した。項目 4 は kit 固有の1行、項目 5 は works の試験運用の1行を残した）。`check-docs` は FAIL 0、WARN 0（`転記待ち` 0、`転記済` 40）。
- 改善案 `s7-i04`（統合先に写す根拠・却下案は元に書かれたものだけにし、無いときは「未検討」と書く。逆方向の確認）を、ユーザーが承認し、kit に反映した（版 `2026-10-06.22`、`workbase` の `4feab08`）。

### 2026-10-06（終了処理の2回目。次のトライアルの開始の形を決めた。セッション `2026-10-06-s7`）

- ユーザーが、次のトライアルの開始の形を承認した: 背景なし（「作業を始めて」だけ。`bare`）→ 背景あり（最初の依頼にゴール・完了条件・制約・やらないことを添える。`briefed`）の順。`sessions.csv` に `start_mode` を足し（s7 は `briefed`）、`docs/metrics/README.md` に定義を足した（`76185a1`）。判断は `docs/decisions.md` の「AI 活用と workflow の効果を、…」の項目（開始の形の比較）。背景ありの回のプロンプトの雛形を、ユーザーに渡した。
- 終了処理の2回目で、手順を通した。並行する別のスレッド（`971132e2`。`works`、更新が約5分前）があったが、`-Current` は正しいスレッド（`f3260c4d`）を選んだ。確認は、作業ディレクトリのキーと更新時刻の手動照合。`AGENTS.md` の手順に、並行するときの照合と `start_mode` を足した。
- 棚卸し: `works` は FAIL 0、WARN 0（`転記待ち` 5）。`archives/learn-c-pool-allocator` は FAIL 0、WARN 0（`転記待ち` 7）。ナレッジ: 新規のメモは作らない（開始の形の比較は、今日の既存メモ `2026-10-06-ai-work-metrics-transcripts.md` に追記する話題。追記はユーザーが明示したときだけ）。
- 改善案を1点出し、ユーザーが承認して、反映した（`events.csv` の `s7-i03` は承認済み）: `extract-threads.ps1 -Current` に `-Cwd`（Claude を開いた作業ディレクトリ。そのキーの履歴の中で最新を選ぶ）と、前後30分以内に別の会話が更新されていたら「並行の可能性」の警告を足した。試験: `-Cwd` なしだと、並行する別トライアルのスレッド（`971132e2`）を誤って選ぶことを再現した（修正前と同じ動作）。`-Cwd` ありは、`works` と `resources\workflow-kit` のどちらでも正しいスレッドを選び、存在しないキーでは警告して全体の最新に戻る。`AGENTS.md` の手順に `-Cwd` を足した。

### 2026-10-06（終了処理。指標の手順を初めて通した。ナレッジ化 1 件。セッション `2026-10-06-s7`）

- ユーザーが、「終了処理して」をトリガにしてよいこと、別のトライアルと並行して数回回すことを指示した。`AGENTS.md` の手順を通した: `threads.csv` を更新（50 スレッド）、`sessions.csv` に s7 を1行（`outcome` 達成、`prompt_complete` 2、`review` 1、`mechanism` 1。根拠と所見は行に記載）、`-Report` で合図を確認（今日のスレッド18件のうち紐づくのは1件。残りは「セッションに紐づかない」。s1〜s6 は backfill しない）。
- `events.csv` の s7 の行を確定した（`reversed` 0、補正の起因 `cause`: q02 は `ai`、q04 は `review`）。漏れ `g01`（無駄の観点が提案に無かった。`cause=ai`）を足した。
- ナレッジ化: `exmem/inbox/2026-10-06-ai-work-metrics-transcripts.md`（Principles 7、Decisions 4、Facts 6、Gotchas 1。点検スクリプトは FAIL 0、WARN 0。コミットしていない）。この `docs/decisions.md` の項目を `転記待ち` にした。
- 改善案を2点出し、ユーザーが承認して、kit に反映した（版 `2026-10-06.21`、`workbase` の `be89d15`。`events.csv` の `s7-i01` `s7-i02` は承認済み）: `closing-hook.md` の手順 5 に、メモを作ったら `check-docs.ps1` を再実行し、以後の報告の件数を再実行後の値にする、と足した。`check-docs.ps1` の `Path` を位置引数でも受けるようにした（位置引数、`-Path`、引数なし、存在しないパス、`-MaxPending` で試験）。モバイル用プロンプトと見本の `kit:` を合わせた。
- 実装中の実測: jsonl の1応答は複数行に分かれ、同じ `message.id` と `usage` が繰り返される（601行が170応答）。`message.id` で一意化している。

### 2026-10-06（AI 活用・workflow の効果を測る指標を作った。セッション `2026-10-06-s7`）

- ユーザーの相談（自己改善のためのデータ取り。背景共有、対象、取り方・フックへの組込み）に対して、素案を精査し、構成をユーザーが承認した（判断は `docs/decisions.md` の「AI 活用と workflow の効果を、スレッド・セッションの指標で測る」）。素案の問題: Project 数は時点の値で効果を測れない、壁時計の時間は自走時間でない、Min は無意味、自走時間だけを目標にすると品質が落ちても良く見える。
- 実測: 履歴（`~/.claude/projects/*/*.jsonl`、52本、約65MB）に、時刻、実プロンプトとツール結果の区別、ツール数、トークンがある。1会話の壁時計は最大約5日（`--resume` の離席）で使えない。ターン長（実プロンプト → 次の実プロンプトの直前）の中央値は20〜140秒。compact の記録は見当たらない（未観測）。会話 ID は、rename 時の履歴コピーで `notes-*` と `works-*` に重複する。
- 作ったもの: `docs/metrics/extract-threads.ps1`（`threads.csv` を書く。全52本が7.6秒。`-Current` と `-Report`）、`threads.csv`（50スレッド）、`sessions.csv`（見出しだけ）、`events.csv` に補正の起因 `cause` 列（既存行は空）、`summarize.ps1` に起因の件数、`docs/metrics/README.md` の定義、`AGENTS.md` に終了処理の手順（試験運用。kit には反映していない）。`-Report` で、セッション紐づけ、放置、ツールエラー率、打ち切りターンを無駄の合図として出す（判定ではない）。
- 指標の記録: `events.csv` に `s7-q01`〜`q04`（用語、用途、起因の列、構成の承認）を `live` で足した。

### 2026-10-06（終了処理。ナレッジ化 3 件。セッション `2026-10-06-s6`）

- ユーザーが push を終え、「終了処理して」を指示した。対象は、`works`、`resources/`（kit）、dotfiles（すべて push 済み。dotfiles にユーザー自身の未コミットの変更（`notepadpp`）があり、触っていない）。
- 棚卸し: `works` の `docs/decisions.md` は FAIL 0、WARN 0（`転記待ち` 4、`転記済` 35、`local` 7）。`archives/learn-c-pool-allocator/docs/decisions.md` は FAIL 0、WARN 0（`転記待ち` 7、`local` 7）。dotfiles は FAIL 0、WARN 0（`未仕分け` 0、`転記待ち` 0）。
- ナレッジ化（`knowledge-hook.md`）: `exmem/inbox/` に 3 件を作った（コミットしていない）: `2026-10-06-embedded-c-constraint-checks.md`（組込み C の制約の機械検査。Principles 5、Decisions 4、Facts 10、Gotchas 2）、`2026-10-06-para-lifecycle-question-metrics.md`（PARA の運用と、質問・提案の指標。Principles 7、Decisions 5、Facts 6、Gotchas 1）、`2026-10-06-make-powershell-git-pitfalls.md`（Make・PowerShell・git の落とし穴。Principles 4、Facts 3、Gotchas 3）。点検スクリプトは FAIL 0、WARN 1（Decisions の「AI の提案」の語。種類の説明で、誤検知と判断）。この `docs/decisions.md` の未仕分け 4 件と、`archives/` の Project の未仕分け 7 件を、`転記待ち`（→ 上のメモ）にした。
- 改善案を 3 点記録した（承認待ち。`events.csv` の `s6-i02`〜`i04`）: closing-hook の対象に Project・Area の `docs/` を含める、点検スクリプトの「AI の提案」の WARN の誤検知、`転記待ち` の閾値を複数の `docs/` 間でどう数えるか。

### 2026-10-06（新しいセッションの呼び出しを決めた。セッション `2026-10-06-s6`）

- ユーザーが、案 A（呼び出しの言葉「作業を始めて」を決め、`AGENTS.md` から開始インタビューの手順書を参照する）と、改善案 `s6-i01`（質問のあとに「ほかに前提はありますか」の自由記述）を承認した。`AGENTS.md` の「このワークスペース固有のルール」に1項目を足した（「作業を始めて」→ `docs/drafts/session-start-interview.md`、Project が無ければ `project-open.md`、閉じるときは `project-close.md`）。open の手順書の下書きを、最初の Project の実績から起こした（`docs/drafts/project-open.md`）。承認待ちの改善案は、いま無い。

### 2026-10-06（承認待ちの改善案5件を承認。セッション `2026-10-06-s6`）

- ユーザーが、承認待ちの改善案5件を承認した（開発のインタビューに「コーディングルールとチェックの有無」と「設計の優先順位」、利用者の前提を記憶に残す、完了条件の達成時点で close を提案する、close の移動を先に `make clean` し、ディレクトリごとの `git mv` が失敗したらファイル単位）。`events.csv` の該当5行を承認済みにし、手順書の下書きに反映した（`docs/drafts/session-start-interview.md` は、項目の構成を、共通・利用者の前提・開発の差分に整理した。`project-close.md` は、手順 6 に反映した）。
- ユーザーから、「見落とす率が高い」という指摘があった。データの裏づけ: 漏れ（`gap`）が累計4件、承認の確認で補足が14件中8件。改善案を1点記録した（承認待ち）: 各質問のあとに「ほかに前提はありますか」の自由記述を置く（`s6-i01`）。

### 2026-10-06（最初の Project `learn-c-pool-allocator` を閉じた。セッション `2026-10-06-s5`）

- 完了条件を達成し、ユーザーの指示で、見直し日（2026-10-20）を待たずに閉じた（close の手順の初回の実測。手順書の下書きは `docs/drafts/project-close.md`）。判断 F は、ユーザーが F4（Cortex-M0 を対象外）を選び、`src/pool.c` が `#error` で止める。`make check` が全項目通った（ARM は M3 / M4）。フットプリント（Cortex-M3 / M4、`-Os`）は、`.text` 288、`.data` 0、`.bss` 0。
- `projects/learn-c-pool-allocator/` を `archives/learn-c-pool-allocator/` へ移した（ファイル単位の `git mv` 25件。ディレクトリごとの `git mv` は `Permission denied` で失敗した）。`areas/learning/README.md` の一覧を、「完了した Project」に更新し、次の Project の候補（スレッド・割り込みの安全性、Cortex-M0 対応、検査の限界の解消）と、開発系の Project の事前確認（専門領域、設計の優先順位、コーディングルールとチェック）を足した。新しい場所で `make check` が通ることを確認した。
- 指標: Project の単位（`live`）の集計は、聞き取り 4 件（適合率 75%、冗長率 50%）、承認の確認 14 件（修正 5、補足 8、適合率 29%）、漏れ（`gap`）3 件。採用済みの行 25 件の `reversed` を 0 に確定した（撤回は無し）。傾向: 承認の確認で、補足が多い（ユーザーが選択肢の外から前提を足す）。漏れは、すべて開発系の前提（専門領域、コーディングルール、設計の優先順位、ポインタの規則）。
- ナレッジ化は、ユーザーの指示で、あとでまとめて言う（上の Next Actions）。

### 2026-10-06（ARM の実測と、暫定制約の再検討。Project の close へ。セッション `2026-10-06-s5`）

- ユーザーが `arm-none-eabi-gcc` を導入して実測した。Cortex-M0 で除算の補助関数（libgcc）への依存が出た（libc 非依存の検査の成果。仮説が当たった）。判断 F（F1 2進の筆算を推奨）は、ユーザーの決定待ち。詳細は `projects/learn-c-pool-allocator/docs/log.md` と `docs/design.md`。
- ユーザーが、実装の初期値を承認し、MISRA は目標にしないこと、ポインタの規則（コンパイラに任せる、キャストは許容、整数演算の値をポインタにしない）を指示した。再帰の禁止を機械検査にした（`gcc -fcallgraph-info`）。
- ユーザーが、見直し日を待たずに Project を閉じることを指示した（私は「見直し日まで残す」と提案して、直された。`events.csv` の `s5-q02`、修正1）。close の手順書の下書きを作った（`docs/drafts/project-close.md`）。判断 F の決定後に、手順どおりに閉じる。
- 指標: `gap` が累計4件（専門領域、コーディングルール、設計の優先順位、ポインタの規則）。いずれも、開発系のインタビューの項目の候補。改善案を1点記録した（承認待ち）: 完了条件を達成した時点で close を提案する（`s5-i01`）。

### 2026-10-06（アロケータを実装した。セッション `2026-10-06-s4`）

- ユーザーが、判断 E1（`-fno-strict-aliasing`）と `gcc-arm-none-eabi` の追加を承認し、`coding-rules.md` の `.data` の制約から「起動を楽にする」の削除を指示した。私は、先に設計書だけを直し、ここは残していた（削除の範囲の解釈の誤り。`events.csv` の `2026-10-06-s4-q01`、修正1）。
- `projects/learn-c-pool-allocator/` に、`src/pool.{h,c}` と `tests/test_pool.c` を実装した。`make check`（整形、静的解析、制約、テスト、`-O2` のテスト、検査の検査）が通った。ホストのフットプリントは `.text` 633、`.data` 0、`.bss` 0。ARM の確認は、`arm-none-eabi-gcc` の導入待ち（dotfiles の `08df993`。ユーザーが導入する）。詳細は `projects/learn-c-pool-allocator/docs/log.md`。

### 2026-10-06（設計の判断 A〜D を承認。セッション `2026-10-06-s3`）

- ユーザーが、メモリプールの設計の判断 A〜D に回答した（詳細は `projects/learn-c-pool-allocator/docs/decisions.md`）。AI の推奨（A1 遅延切り出し）が、ユーザーの優先（安全性が起動速度より上）と逆だった。`events.csv` に、`approval` 4行（A は修正つき、B・D は補足つき）と、`gap` 1行（設計の優先順位が聞かれなかった）を記録した。
- 改善案を1点記録した（承認待ち）: 開発のインタビューに「設計の優先順位（安全性・速度・フットプリントの順）」を足す（`2026-10-06-s3-i02`）。ここまでの開発の差分項目の候補は3つ（コーディングルールとチェック、利用者の前提、設計の優先順位）。いずれも、`gap` で見つかった漏れ。

### 2026-10-06（組込み前提の設計と、指標に「漏れ（gap）」を追加。セッション `2026-10-06-s3`）

- ユーザーが組込み領域のエンジニアと伝えた（インタビューで聞いていなかった前提）。制約の適用範囲を `src/` のみにし、「`.data` を抑える」を初期値つき `.data` の削減に直した（`projects/learn-c-pool-allocator/docs/decisions.md`）。この前提を、記憶（ユーザーの属性）に残した。`events.csv` の `approval` 2行は、ともに修正と補足つき（AI の解釈が強すぎた）。
- 指標に `kind=gap`（質問が漏れていた: 聞かれなかった前提が後から出た）を足した。今日の2件: 専門領域（組込み）、コーディングルールと制約。適合率は聞いた質問のズレを測り、gap は聞かなかった質問の欠落を測る。件数だけを見る指標（`docs/metrics/README.md`）。集計スクリプトで、ループ変数と検証つき引数の名前が衝突するバグ（PowerShell は大文字小文字を区別しない）を直した。
- 改善案を1点記録した（承認待ち）: 利用者の前提（専門領域・経験）を記憶に残し、不足していれば最初に1度だけ聞く（`events.csv` の `2026-10-06-s3-i01`）。同じ前提を毎回聞かないための案。

### 2026-10-06（改善案2点を承認。コーディングルールの明示。セッション `2026-10-06-s2`）

- ユーザーが、開始インタビューの改善案2点（「触ってよい範囲」の独立、答えが定まる項目の省略）を承認した。手順書の下書きを `docs/drafts/session-start-interview.md` に起こした（6項目、省略の条件、未決）。`events.csv` の該当2行を承認済みにした。
- ユーザーの要望で、`learn-c-pool-allocator` の実装で私が暗黙に使うルールを明示し、承認を受けた（判断と詳細は `projects/learn-c-pool-allocator/docs/decisions.md` と `docs/coding-rules.md`）。linter とフォーマッタは未導入だったので、追加の警告フラグ、`-fanalyzer`、制約の検査スクリプト（`check-rules.sh`）を足し、`clang-format` を dotfiles の `manifests/apt.txt` に追記した（dotfiles の `14711b5`）。実機への導入はユーザーが行う（`sudo` のパスワードが要るため）。
- dotfiles に足したものは、`projects/learn-c-pool-allocator/docs/dotfiles-additions.md` に1行ずつ記録し、作業の最後にまとめて報告する（ユーザーの指示）。いまは `clang-format` の1件。
- 改善案を1点、記録した（承認待ち）: 開発のインタビューに「コーディングルールとチェックの有無」を足す（`events.csv` の `2026-10-06-s2-i03`）。

### 2026-10-06（開始インタビューの手動の試行。セッション `2026-10-06-s2`）

- 開始インタビューを、`learn-c-pool-allocator` で初めて手動で試した（ユーザーの指示）。事前に `docs/log.md` と環境（Windows と WSL のコンパイラ）を確認し、答えが分かる項目は既定値（Recommended）にして、4問を聞いた（ゴール、前提・制約、対象と資料、やらないこと）。結果（`live` の4行）: 回答率 100%、採用率 100%、適合率 75%、冗長率 50%。ズレは「やらないこと」の1問だけで、選択肢「dotfiles や kit の変更」が誤りだった（dotfiles は変更してよい、kit は不要。ユーザーが自由記述で直した）。冗長な2問（前提、対象と資料）は、答えが1つに定まっていた。ゴールの「環境を整え、テストが走る最小の骨組み」は、Project 側で達成した（`projects/learn-c-pool-allocator/docs/log.md`）。
- インタビュー手順への改善案を2点、`improvement` の行として記録した（承認待ち。下の Open Questions）。

### 2026-10-06（指標を改善フックにも適用した。kit 版 `2026-10-06.19`）

- ユーザーが指標の形式を承認し、同じ指標を既存の改善フックにも適用するよう指示した。実施: `docs/metrics/interview-events.csv` を `events.csv` に改名し、`kind=improvement`（改善案）を足した。`improvements.md` の66件を `import` で取り込み（採用率約98%。判別力が低いので、`fix` と `reversed` を重視する方針）、集計スクリプトを、未判定の行（`fix` や `answerable` が空）を母数から外すよう直した。kit の `knowledge-hook.md` に節「改善案の指標の記録」を足し、版を `2026-10-06.19` にした（`workbase` にコミット）。モバイル用プロンプトの `kit:` と見本の `kit:` を合わせた。判断は `docs/decisions.md`。

### 2026-10-06（開始インタビューの指標を集め始めた）

- ユーザーの指示で、質問数・回答率・採用率・適合率などを、全体・Area・Project・セッションの単位で集めることにした。`docs/metrics/` に、定義（`README.md`）、イベントログ（`interview-events.csv`。このセッションの会話から15行を `backfill` で起こした）、集計スクリプト（`summarize.ps1`）を作り、集計が動くことを確認した。記録をエージェントの役目にするため、`AGENTS.md` に1項目足した。形式と推奨指標は AI の提案で、承認待ち（判断は `docs/decisions.md`）。`backfill` の行は推定で、`live` の行が溜まるまで、率は参考値。

### 2026-10-06（PARA の `areas/` `projects/` の使い方の検討を始めた）

- 検討の進め方を、A 役割と責務、B フックとディレクトリ構造、C 判断基準と候補、D 試行の4段階にした（ユーザーの指示）。A と C を同時に進め、ユーザーが承認した（判断は `docs/decisions.md` の「PARA の `areas/` `projects/` `archives/` の役割と判断基準を定める」）。前提（PC1・PC2 は別インスタンス、優先順位、最初の試行は PC2 の学習、`areas/dev-env` は廃止済み）も記録した。続いて B を承認（B1 フラット。開始・終了フックを先に）。D を始め、`areas/learning/README.md` と `projects/learn-c-pool-allocator/`（`README.md`、`docs/log.md`、`docs/decisions.md`）を作った。成果物（固定長ブロックのメモリプールアロケータ）はユーザーが承認した。フックの連鎖（open → [開始インタビュー → 作業 → 終了処理]×N → close）と、開始インタビューを育成・改善方式（プラン方式かプロンプトから始め、作業の種類のカテゴライズと抽象化・継承で定型化）で作る方針も、ユーザーが承認した（判断は `docs/decisions.md`）。

### 2026-10-06（`転記待ち` を `転記済` に進めた。kit 版 `2026-10-06.18`）

- 「inboxを整理して」の最初の実行で出た改善2点を、ユーザーが承認し、kit を版 `2026-10-06.18` に上げた（`workbase` の `9567c15`）: `integrate-hook.md` の手順 5 に、案の一覧の表の形と、本文を外す範囲の目安を足した。

- exmem の統合（`b70f0d4`）のあと、この `docs/decisions.md` の `転記待ち` 1件（CA 証明書の置き場）を、`obsidian-vault.md` の本文と照らして `転記済` に進めた（ユーザーの承認。突き合わせ済み）。dotfiles の 20 件も同時に進めた（dotfiles の `docs/log.md`）。新しい「inboxを整理して」フックの最初の実行になった。

### 2026-10-06（作業の終わりの処理を、2つの独立したフックに分けた。kit 版 `2026-10-06.17`）

- ユーザーの承認で、「終了処理して」（`closing-hook.md`）と「inboxを整理して」（`integrate-hook.md`）を kit に足した（`workbase` の `93d2a41`）。終了処理は、`docs/` 更新 → 棚卸し → ナレッジ化 → コミット → 統合待ちの報告の順で固定し、メモ5件以上、または `転記待ち` 15件以上で統合を勧める。統合は exmem 側の独立したフックで、`転記済` への案（「突き合わせ済み」と「存在の確認のみ」を区別。承認制）まで出す。「ナレッジ化して」の単独実行（誤入力を含む）は知識の抽出だけを行い、終了処理の案内を1行添える。この `AGENTS.md` の共通ルールに、`closing-hook.md` と `integrate-hook.md` を足した。判断はユーザーの承認（kit の `improvements.md`）。

### 2026-10-06（会社 CA 証明書の置き場を `$HOME/.certs` に変更。ナレッジ化）

- 「ナレッジ化して」を実行し、`exmem/inbox/2026-10-06-certs-location-wslenv-path.md` を作った（コミット対象外）。`docs/decisions.md` の対応する項目の行き先を、このメモにした（転記待ち）。同じ実行で、dotfiles の未仕分け項目も別の2メモにした（dotfiles の `docs/log.md`）。

- ユーザーの指示で、`certs` の置き場を `areas/dev-env/certs/` から `$HOME/.certs` に変えた。このリポジトリの `.gitignore` から `/areas/dev-env/certs/` を除いた。kit は版 `2026-10-06.15`（雛形の `.gitignore` から同じ行を除く。「workflowを導入して」の手順は、もともと `certs` を作らないので変更なし）。dotfiles は `10_env.bat`、`common.sh`、`README.md` を直した（WSL へは `WSLENV` の `CERTS_DIR/p`）。判断は `docs/decisions.md`。旧 `areas/dev-env/certs` は空で、dotfiles の確認が済んだら削除する（dotfiles の Next Actions）。

### 2026-10-06

- exmem の統合を確認して、棚卸しを行った（kit `docs-rules.md` の「棚卸し」。`workbase` の `9e335b7`）。メモ `2026-10-06-docs-destination-markers.md` は inbox から無くなり、`exmem/knowledge/workflow-kit.md` の新節（Principles 6、Decisions 6、Facts 5、Gotchas 3）に入っている。Decisions 6件の根拠と却下案が欠けなく写っていることを、本文で確認した。`decisions.md` の「docs の項目に「行き先」を持たせ…」を `転記済` にし、本文を外した（点検は FAIL 0。転記済34、転記待ち0、local 6、破棄 2、滞留 0）。統合された Open Questions に、「`転記済` に進める契機を決める」の提案が未承認のまま残っている（kit `2026-10-06.14` で決まった。exmem 側の修正は、exmem の運用）。
- 「ナレッジ化して」の改善1点を kit に反映した（ユーザーの承認。kit の版 `2026-10-06.14`、`workbase` の `f2a815c`）。`転記待ち（→ exmem/inbox/<メモ>）` を `転記済` に進める契機を、棚卸しのとき、メモが inbox に無くなっていたら、統合先を確認して進める、と `docs-rules.md` に足した。もう1点（Gotchas の3行セットの検査）は、規則で足りるので変更なし（`improvements.md` に記録）。
- 「ナレッジ化して」を実行した（ユーザーの指示。kit 版 `2026-10-06.13`）。先に dotfiles の `docs/log.md` に、転記した決定の記録を足した（dotfiles の `13ba921`）。`exmem/inbox/2026-10-06-docs-destination-markers.md` を作った（Principles 6、Decisions 6、Facts 6、Gotchas 3。点検スクリプトは FAIL 0、WARN 0）。メモはコミットしない規則のため未追跡。`decisions.md` の対応する項目の行き先を、このメモにした（転記待ち）。
- `転記済` 33件の内容確認をして、元の本文を外した（ユーザーの指示。規則は kit の `docs-rules.md`）。確認: 各項目の根拠・却下案の要点を、転記先（kit の各ファイル、exmem の `workflow-kit.md` `app-config-placement.md` `obsidian-vault.md` ほか）の本文と突き合わせた（キーワードの一致 + 本文の目視）。D9（コミット権限）の却下案「PARA の中身も含める」は、exmem の別の項目（初回コミット）に入っていた。D15（`contexts/`）の根拠・却下案は exmem の `workflow-kit.md` に揃っていた。欠落は無し。`decisions.md` は 258 行 → 約140 行。見出し・日付・行き先だけにした（`local` `破棄` `転記待ち` の項目は変更なし）。作業中に、変数名の大文字小文字の衝突（`$l` と `$L`）で `decisions.md` を壊して書き出したが、`git restore` で戻して、やり直した（コミットした内容は無事）。
- docs の行き先の仕組みを kit に反映した（ユーザーの承認。kit の版 `2026-10-06.13`、`workbase` の `c67ae80`）。`docs-rules.md` に節「decisions.md の項目の行き先」（ラベル、6状態、一般化して運ぶ、転記済は本文を外す、棚卸し、直結ソースと隔離ソース（PC1）の運び方）と、P2「小さく一過性のディレクトリには専用の `docs/` を置かない」・P5「決定はユーザーが明示または承認したものだけ」を足した。`templates/decisions.md` に行き先の行、`knowledge-hook.md` の手順 2 に未処理の【汎用】項目の入口、`tools/check-docs.ps1`（works の試験版を移し、雛形の空の `-` を項目に数えないよう直した。works・雛形・上限超過・ファイル無しで試験）を足した。works の `docs/tools/` は削除した。判断は `docs/decisions.md`。ユーザーの呼び名として、会社 PC を PC1、個人 PC を PC2 とした（今後の記述から。過去の記述は書き換えない）。
- docs のデータの行き先の仕組みを設計し、works で試験運用を始めた（ユーザーの指示と承認。判断は `docs/decisions.md` の「docs の項目に「行き先」を持たせ、滞留するデータを検出する」）。現状把握（kit・exmem との突き合わせ）→ 論点と判断軸の作成 → 選択肢（現状維持、行き先の印、書く時点のラベル、docs からの転記、docs の共有）→ 採用（ラベルと行き先の印、滞留を独立した状態、上限20件、試験先行）の順。`docs/decisions.md` の42項目に、ラベルと行き先を付けた（転記済 31、転記待ち 3、local 6、破棄 2、滞留 0）。点検スクリプト `check-docs.ps1`（のち kit の `tools/` に移した）を作り、FAIL 0 を確認した（見本で、欠落・不正な状態・上限超過の検出も試験した）。kit は、承認前なので変更していない。
- 転記待ちのうち3件を処理した（ユーザーの承認）。① dotfiles の `docs/decisions.md` に、Linux 側の試験スクリプトの置き場の決定を足した（works の記録が先で、dotfiles 側に無かった）。② exmem の `README.md` と `AGENTS.md` の `contexts/` の定義を、決定（`works` から見えない場所の引継ぎコンテキスト）に合わせた。③ exmem の `obsidian-vault.md` の設定節は、すでに現状と一致していたので変更なし。
- 「ナレッジ化して」を2回実行した（ユーザーの指示）。既存メモ `2026-10-06-vault-top-rename-impact.md` に、このメモに無い情報（旧パス 1180 件の内訳など）を追記し、別メモ `2026-10-06-archived-repo-old-path-policy.md`（旧名の時制の方針、アーカイブ済み GitHub リポジトリの削除の前提と手順）を作った。メモはコミットしない規則のため未追跡。点検スクリプトは FAIL 0。この実行の改善1点（既存メモへの追記と別メモの作成が同時に求められたときの手順）を、ユーザーが承認し、kit に反映した（版 `2026-10-06.10`。判断は kit の `improvements.md`）。`AGENTS.md` の「新規ファイルだけ」に例外の参照を足した（雛形と同じ文面）。
- 現在形の旧パスを直した（ユーザーの指示。方針: 現在形の記述は現在の名前に直し、日付つきの履歴は書き換えない）。直したもの: `exmem/knowledge/` の `workflow-kit.md`（既定の対象。WSL から読めることを確認して更新）、`modern-cli-tools.md`（`.ignore` の場所）、`wsl-file-placement.md`（記述時点のパスと明記）、`obsidian-vault.md`（構造の図）。このリポジトリの Next Actions（終わった項目2つを削除、パスと `$WORKS_DIR` を更新）と、dotfiles の `docs/log.md` の Next Actions。残る旧パスは、すべて日付つきの履歴の記述（確認: 2026-10-06、根拠: `rg`）。旧 `notes` の GitHub 側の削除は、手順の案を Next Actions に記録した（未決）。
- `works` への移行が完了した（ユーザーが `C:\vault\backup\finish-works-rename.ps1` を実行。その後の確認は次の項目）。`claude --resume bc9d6801-…` は、`cwd` を書き換えた履歴でも**通らなかった**（ユーザーの報告。エラーの内容は未取得）。
- 移行の完了を確認した（確認: 2026-10-06）。① 旧パス `vault[\\/]notes` は、履歴（log・decisions・contexts・日付つきの記述、kit の `README.md` と `improvements.md` の変更履歴）と、`exmem/knowledge/` の日付つきの経緯を除いて、`works` と dotfiles のコードに無い（根拠: Grep と `rg`。dotfiles の `docs/log.md` の Next Actions に旧名が残る点は Next Actions に記録）。② 環境変数 `WORKS_DIR=C:\vault\works`、`CERTS_DIR=C:\vault\works\areas\dev-env\certs`（`NOTES_DIR` は未設定。ユーザー環境変数で取得）。`obsidian.json` の Vault は `C:\vault\works`。`C:\vault\works\.obsidian` は dotfiles の `windows\obsidian\.obsidian` へのジャンクション（`app.json` が読める）。`C:\vault\notes` は無く、`areas\dev-env\certs` がある。③ WSL から `/mnt/c/vault/works/resources/.git` が読め、`WORKS_DIR=/mnt/c/vault/works`。dotfiles の Linux テストは 36/36 合格（実 WSL の「default WORKS_DIR sees the Windows-side clone」も合格。以前の skip は解消）。
- resume が通らなかった事実: 新キー `C--vault-works-resources-workflow-kit` の jsonl では、`"cwd"` 287件はすべて `works` に書き換わっていたが、本文・スナップショットの `workingDirectory`・読み込んだ `CLAUDE.md` のパスなどに、旧パス `C:\\vault\\notes\\…` が1180件残っていた（確認: 2026-10-06、根拠: jsonl の検索）。「`cwd` の不一致が原因」という仮説は、`cwd` だけでは足りなかった。原因は未特定。
- Vault のトップを `notes` から `works` に rename する作業を進めた（ユーザーの指示。判断は `docs/decisions.md`）。文字列の更新まで済み: dotfiles（`NOTES_DIR` → `WORKS_DIR`、パス、`CERTS_DIR`）、`workbase`（kit の版 `2026-10-06.8`、`AGENTS.md`、既定の対象、雛形、見本）、このリポジトリの `AGENTS.md` と `.gitignore`（`/areas/dev-env/certs/` を除外）。dotfiles の Linux のテストは 35/35 合格（実 WSL の項目だけ、rename 後でないと走らず skip）。**ディレクトリの rename 本体は、ユーザーが `C:\vault` で行う**（このセッションが cwd を掴むため）。
- ユーザーが `C:\vault\backup\rename-notes-to-works.ps1` を実行した（rename、certs の移動、環境変数、`obsidian.json`、Claude の履歴キーのコピー）。そのあと、Claude の `--resume` が新しいパスで通らなかったため、ユーザーが `works` を `notes` に戻した。結果、環境変数（`WORKS_DIR` `CERTS_DIR`）と `obsidian.json` は `works` を指し、ディレクトリは `notes` という食い違いの状態になった（確認: 2026-10-06、根拠: 環境変数と `obsidian.json` の取得、`C:\vault` の一覧）。コピーした履歴の `"cwd"` に旧パスが残っているのが原因という仮説で、`C:\vault\backup\finish-works-rename.ps1`（rename と、履歴の再コピー＋`cwd` の書き換え）を用意した（のち実行された。上の項目）。
### 2026-10-05

- 「ナレッジ化して」の改善2点を実施した（ユーザーの承認。kit の版 `2026-10-05.8`、`workbase` の `3daeff6`）。① 同じスレッドで `knowledge/` を直接編集済みのときは、Open Questions に「統合時の重複」を書く（手順 5-6）。② 自己点検の機械で確認できる項目を、点検スクリプト `workflow-kit/tools/check-inbox.ps1`（PowerShell 7）にした。一時ディレクトリで、正常なメモ1件と、わざと壊したメモ11種を試験し、すべて期待どおり。試験で、スクリプトの引数の受け取り方（複数パス）の誤りと、`kit` の版の比較を FAIL にする過剰さ（WARN にした）を直した。スクリプトを、今日の inbox の7メモに実行して、別セッションのメモ（ファイル名が7語、Facts の根拠が無い項目、`kit` が古い版）と、私のメモ1件（ファイル名が6語）の規定違反を検出した。私のメモは改名した。別セッションのメモは、既存のメモとして編集していない（ユーザーが統合のときに判断する）。判断は `docs/decisions.md`。
- 「ナレッジ化して」を、スレッド全体に対して実行した（ユーザーの指示。版 `2026-10-05.7`）。範囲を限定した前回の実行（WSL の試験のメモ）の範囲は除いた。`exmem/inbox/` に、統合先が異なる5話題のメモを作った（コミットしない規則のため、未追跡）: `2026-10-05-repo-boundary-shared-local-vault.md`（共有とローカルのリポジトリ境界の設計。ファイル名が英単語6語で規定違反だったので、後で5語に改名した）、`…-search-visibility-gitignore-junction.md`（検索ツールが `.gitignore` とジャンクションで黙って外れる）、`…-git-subdirectory-split-filter-repo.md`（`git filter-repo` による切り出し）、`…-agent-commit-delegation-workspace-hook.md`（コミット権限の委譲とフックの設計）、`…-ai-proposal-checks-and-migration.md`（AI との構造変更の進め方）。自己点検は機械的に通した。
- 3点を実施した（ユーザーの指示。判断は `docs/decisions.md`）。① Linux 側の試験スクリプトを dotfiles の `tests/linux/test_scripts.sh` に保存した（36項目、WSL で合格。dotfiles の `afa9211` `7fe015f`）。② 「ナレッジ化して」で作った inbox のメモは、コミットしないことにした（全体）。③ 「ナレッジ化して」の改善2点（範囲を限定された実行、【汎用】【この件】のラベル）を採用した。②③は kit の版 `2026-10-05.7`（`.6` は欠番）で、`workbase` の `ba96753`。モバイル用プロンプトと見本の `kit:` を合わせた。直前にコミットしていた WSL の試験のメモ（`9df9903`、未 push）は、そのまま残っている。
- 「ナレッジ化して」を、範囲を限定して実行した（ユーザーの指示: dotfiles の Linux 対応の WSL での試験の部分だけ。スレッド全体は、この後に実行する予定）。版 `2026-10-05.5`。`exmem/inbox/2026-10-05-wsl-shell-script-testing-patterns.md` を作った（【汎用】と【この件】に分けた。Decisions は「なし」。コミット `workbase` の `[exmem] inbox: WSL shell-script testing patterns…`）。スレッド全体の実行のときは、このメモを同日の既存メモとして扱い、話題を重複させない。
- ユーザーが、`workbase` と トップの push、旧 `notes` の GitHub 側アーカイブ化を完了した。ghq の位置にあった `workbase` の clone（`C:\vault\repos\github.com\yuzucha16\workbase`。ユーザーが作成）は、ユーザーが削除した（`resources/` の clone だけが残る）。雛形 `templates/AGENTS.md` と見本の「`notes` が無いPCなど」を「`workbase` を clone していないPCなど」に直した（ユーザーの承認。`workbase` の `f4ed4be`。版は上げない）。
- Linux を dotfiles で対応した（ユーザーの指示。dotfiles の `dab1507`、`ef5989b`。詳細は dotfiles の `docs/log.md`）。WSL の実機で、一時ディレクトリと偽の HOME を使って35項目を試験し、すべて合格した。ネイティブ Linux の実機は未確認。kit の `setup-hook.md` の既定値の表に、「`C:\vault\notes` は Windows と WSL の標準の場所。ネイティブ Linux では対象を言葉で指定する」を足した（`workbase` の `ec79112`）。
- ディレクトリ構造の変更を検討し、方針を決めた（ユーザーの選択。判断は `docs/decisions.md` の「Vault のトップを PC ローカルのリポジトリにし…」）。きっかけは、会社 PC で `_local` の作業もコミットしたいこと。検討した案: 現状維持、`company/` の入れ子、トップ非リポジトリ、重ね git、exmem・kit の単独化。決定: トップを PC ローカルのリポジトリにし、共有部分を `workbase` として `resources/` に直接 clone する。`.obsidian` は dotfiles へ戻す。fonts・wallpapers・`_archive/obsolete`（履歴ごと）は破棄、`office/` は dotfiles へ。ジャンクション越しは Grep / Glob が辿らないことを実測した。`git filter-repo` 2.47.0 を導入した。リポジトリ、ファイルの移動、dotfiles はまだ変更していない（文書の記録のみ）。
- 段階1を実施した（ユーザーの指示）。`notes` を一時ディレクトリへ clone し、`git filter-repo` で `fonts` `wallpapers` `_archive` `office` `_local/.gitkeep` と、トップのファイル（`.obsidian` `AGENTS.md` ほか）を履歴ごと除き、`resources/` をルートにした。結果: 58 → 30 コミット、139 → 68 ファイル（`exmem` 42、`workflow-kit` 11、`cheatsheets` 10、`handson` 5）。ルートに `AGENTS.md`、`CLAUDE.md`、`.gitattributes`（LFS なし）、`.gitignore` を足して1コミットにした。確認: 除外したパスの履歴の漏れ0、LFS 0、remote なし、改行は全ファイル LF、単独 clone した状態での wikilink 340件のうち未解決は8件（すべて規約の説明文にある書式の例で、実際の切れではない）。旧構成の記述（`_local`、`notes` がルート）が `workbase` 内の文書に残っている（修正は段階5）。実施中に、2026-10-04 の `.obsidian` の置き場の決定との食い違いを見つけて報告した。
- `.obsidian` を dotfiles へ戻す（A）を、10-04 の決定と根拠を示した上で、ユーザーが改めて選んだ。経緯と撤回の理由は `docs/decisions.md`（「`.obsidian` を dotfiles へ戻す」）。`workbase` 側の `obsidian-vault.md` と `app-config-placement.md` に、撤回済みを記録した（2コミット）。
- dotfiles を更新した（ユーザーの指示。Windows のみ。未コミット）。`windows/obsidian/.obsidian`（15ファイル。元と一致を確認）と `windows/office/`（17ファイル、`.gitattributes` つき）を追加し、`links.map` を `windows\obsidian\.obsidian|%NOTES_DIR%\.obsidian` に差し替え（`..\notes` の行は削除）、`50_repos.bat` に `workbase` の `git clone`（`%NOTES_DIR%\resources`、既にあれば skip）を追加した。`10_env.bat` のコメント、`.gitignore`（`workspace*.json`）、`README.md`、`AGENTS.md` を合わせた。`.bat` の改行は CRLF のまま。実行は未確認（リンクと clone は、トップの切り替えまで有効にしない）。
- `gh` が未ログインで、GitHub のリポジトリ作成と push は実行していない（この後、ユーザーが `workbase` を作成して push した。`origin/main` = `f588cc2` を確認）。
- 段階2を実施した（ユーザーの承認）。kit に導入項目 5「ワークスペース（Vault のトップ）の生成」を足し（`setup-hook.md`、`templates/workspace/`、見本、`improvements.md`）、版を `2026-10-05.1` にした。モバイル用プロンプトと見本の `kit:` を合わせた。
- 段階4を実施した（ユーザーの承認。個人用 PC、remote は非公開リポジトリ `worksample`、履歴ファイルは削除、の指示）。手順: ① 旧リポジトリ全体をバックアップ（`C:\vault\backup\notes-before-restructure-20261005`、1070ファイル。`ConsoleHost_history.txt`（177,425バイト）は、ユーザーの指示で削除したので含まない）。② ジャンクション `C:\vault\notes` を外し（リンクのみ。旧リポジトリは無傷）、実ディレクトリとして作り直した。③ `areas` `projects`（6ファイル）`archives` `docs` を移した。④ `workbase` を `C:\vault\notes\resources` に clone し、origin を GitHub に付け替えた（74ファイル。2コミット先）。端末ごとの `settings.local.json` 2件を旧位置から移した。⑤ `.obsidian` を dotfiles の `windows\obsidian\.obsidian` へのジャンクションにした（`30_link.bat link -n` のドライランで、リンクの解決を確認した上で、同じ `mklink /J` を1本だけ張った。15ファイル読める）。⑥ kit の項目 5 の手順で、トップを生成した（`.gitignore`、`.ignore`、`AGENTS.md`、`CLAUDE.md`、`areas/` `archives/` の `.gitkeep`、`git init`、`origin` = `worksample`。初回コミットも push もしていない）。自己点検: `resources/` と `.obsidian` が無視される、プレースホルダなし、共通ルールの節が雛形と一致、`resources/` は別リポジトリ。
- 切り替えの実測で、**トップの `.gitignore` が `resources/` を除外すると、Claude Code の Grep（ripgrep）が `resources/` の中を黙って飛ばす**ことを見つけた（`setup-hook` の検索が3件のみ。ジャンクション越しと同じ症状）。`.ignore` に `!/resources/` を置くと解消した（8件以上。確認: 2026-10-05）。kit に反映した（雛形 `ignore.template`、手順 6、自己点検、版 `2026-10-05.2`）。判断は `docs/decisions.md` の Facts。
- 段階5を実施した（ユーザーの指示）。`workbase` 内の旧構成の記述（`_local`、「`notes` がルート」、ホワイトリスト、LFS）を直した: `exmem/AGENTS.md` `exmem/README.md` `cheatsheets/CLAUDE.md` `cheatsheets/env/win11.md`（`dotfiles` だけを clone する手順に）、知識ノート7件（`obsidian-vault.md` は「現在の構造」の節を足し、旧い節に「撤回・変更済み」の注記を付けた。履歴は残した）。`updated` を 2026-10-05 にした。`exmem/contexts/` と、日付つきの履歴の記述は、書き換えていない。点検で、旧 `notes` のルートにあった `.gitattributes`（LF 統一）が新しいトップに引き継がれていないことを見つけ、トップに置き、kit の雛形に足した（版 `2026-10-05.3`）。`workbase` に2コミットを足した（kit、文書修正）。
- コミットと push が完了した（ユーザー）。`workbase`: `origin/main` と同期（kit `2026-10-05.1`〜`.3`、段階5の文書修正）。dotfiles: `cded219` まで同期。新しいトップ: `28aa7cf [vault] initial commit`（`worksample` の `first commit` の上。11ファイル。`resources/` と `.obsidian` は追跡されていない。`.gitignore` は kit の雛形と一致）。確認: 2026-10-05、`git log` `git status` `git ls-files`。この確認で、`projects/link-management` がトップから無くなっていることに気づいた（Next Actions。その後、ユーザーが退避したと回答した）。
- コミットの権限をエージェントに移した（ユーザーの指示。全体に適用。判断は `docs/decisions.md`）。共通ルール `docs-rules.md` に「コミットと push」を足し、`setup-hook.md`（項目 5 は初回コミットまで。入力 7）、`knowledge-hook.md`、kit の `AGENTS.md` を合わせた。kit の版を `2026-10-05.4` にした。使い捨ての一時ディレクトリで3回試験して（空のトップ、既存の中身あり、中止条件3種）、曖昧さ3点を直した。この規則で、`workbase` に初めて自分でコミットした（`71d1d7c`。パス指定、事前の確認つき）。push はしていない。
- 「workflowを導入して」だけでワークスペースを作れるようにした（ユーザーの指示。判断は `docs/decisions.md`）。`workbase` の中で、対象の指定なしに言うと項目 5 になり、既定値（`C:\vault\notes`、業務用、remote なし、初回コミットする）で作る。報告に「条件」（既定値か指定か）を必ず書く。`pre-push` を雛形にした。kit の版を `2026-10-05.5` にして、一時ディレクトリで試験した（`workbase` に1コミット）。push は未実施（ユーザー）。
- 項目 5 の既定の対象を、固定パスから、Claude を開いたディレクトリ（cwd）に変えた（ユーザーの指示。判断は `docs/decisions.md`）。cwd の直下に `workbase` の clone があるときだけ項目 5。`workbase` の中では作らず止まる。雛形の共通ルールの置き場を相対にした。kit の版を `2026-10-05.6` にして、5つの場面の判定を試験した（`workbase` に1コミット `a1abf33`）。この変更で、新しい PC のトップに入口（`AGENTS.md`）が無い問題が見えたので、Open Questions に残した。
- 上の「cwd を対象にする」変更を取り消した（ユーザーの指示）。理由: 呼び出し元は `workbase` の中という前提を見落としていた。参照先の中から呼ぶのが自然で、ワークスペースの中から呼ぶ必要はない。`git revert` で kit を版 `2026-10-05.5` に戻した（`workbase` の `f7b054a`。取り消しの記録は、kit の `README.md` の変更履歴と `improvements.md`）。既定の対象は `C:\vault\notes` に戻り、入口がない問題（Open Questions）も、この前提では起きないので消した。判断は `docs/decisions.md`（撤回済みの注記）。
- エクスプローラーのアイコンと配色を確定し、コミットした（`file-explorer-compact.css`。ユーザーの指示）。内容: ファイルの種類ごとのアイコン色（ノート=blue、`.base`=green、コード・設定=orange、画像=purple、`.pdf`=red）、開いているフォルダ=yellow・閉じているフォルダ=`#A7B85A`（見出しと同じ緑）、アクティブなタブの文字とウィンドウ右上のボタンを本文色（`--text-normal`）に。プラグインは入れず CSS のみ。判断は `docs/decisions.md`。見た目と起動・処理の軽さは、ユーザーが実機で確認しながら調整した（数値の計測はしていない）。
- 次の調整は見送った。階層ごとのインデントを狭める（エクスプローラーとアウトライン）: Obsidian が各行に `padding-inline-start` と `margin-inline-start` を `!important` のインラインで付け（1階層17px）、CSS では変えられない。余白の変数や `.nav-folder-children` への直接指定は、効かないか、位置がずれた（確認: 開発者ツールのDOM）。`.md` の表示（Obsidian は `.md` だけ隠す）、ファイル名とタグペインのタグ名を緑にすることも、取りやめた。

### 2026-10-04

- 「ナレッジ化して」の改善2点が承認され、kit の版を `2026-10-04.2` に上げて反映し、コミットした。Decisions にはユーザーが明示または承認した決定だけを書く（AI の提案は Open Questions に「提案」）。同じ会話で複数回実行したときは、前回の実行以降の内容だけを対象にする。モバイル用プロンプトと見本の `kit:` を合わせた。inbox の2メモ（`kit: 2026-10-04.1`）は、未コミットのまま、ユーザーの統合を待つ。
- 「ナレッジ化して」を実行した（版 `2026-10-04.1`。`kit:` の記録の初回の実測）。`exmem/inbox/` に2ファイルを作った: `2026-10-04-tracking-criteria-for-app-written-files.md`（自動で書き換わるファイルを追跡するかの判断基準）、`2026-10-04-parallel-sessions-and-integration-consistency.md`（並行セッションと、統合時の整合の取り方）。push は、ユーザーが完了した（`notes` の8コミット）。
- 残件 A〜D の変更を、2コミットに分けてコミットした（`3c8eaec`: kit の版と導入する単位、`df29cb7`: `knowledge/` の修正）。ユーザーが、inbox の整理（統合コミット `a1f9cb4`）と、`colored-tags` の `data.json` のコミット（`646f44b`）を終えた。`inbox/` は `README.md` だけになった。統合後の `knowledge/` に、`kit:` は写っていない（確認: `git grep "^kit:"` が0件）。
- 残件の修正と整理（ユーザーの指示）を行った。
  - 統合で未解決のまま取り込まれていた項目を直した。`workflow-kit.md` の Open Questions から「`notes/docs/` を共有するか」を外し、Decisions に「ローカル専用のままにする」を記録した。kit の版に関する問いも、Decisions に移した。`app-config-placement.md` には、未解決の取り込みは無かった（検索で確認）。
  - `obsidian-vault.md` の `Backlinks / Graph` の行（`graph` は無効）と、Proposals の節の前書きを直した。Proposals の項目自体は、別セッションの統合で、すでに現状に合っていた。
  - 導入フックに「導入する単位」の注意を足した（承認済み）。メモに使った kit の版を残す運用を始めた（版 `2026-10-04.1`。承認済み）。
  - `colored-tags` の `data.json` の追跡の判断基準（5項目）を作り、既存の決定（追跡する）を確認した。改行コードは、Obsidian が LF で書くことを確認した。2025-09 のプラグインの取り消し理由は、不明のまま、問いを削除した（ユーザーの指示）。
- 別セッションの作業を反映して、残件を整理し直した。`notes` の4コミット（kit の初回コミット `1b0ba77`、`.obsidian` の置き場の判断基準のメモ `755b13c`、`knowledge-hook.md` の改善 `5714d41`、`obsidian-vault.md` の更新 `2893e74`）と、dotfiles の push 状況（`2b417f6`、`c8159f3` は push 済み）を、確認した。`knowledge-hook.md` の改善は、他のメモとの決定の食い違いを Open Questions に書くこと、実行の順序の判定を `docs/log.md` の今日の項目で行うこと（確認: `improvements.md`）。
- 新しいセッションに、kit に書かれた内容（「ナレッジ化して」の手順 5、「workflowを導入して」の入力）を質問した。回答は、`knowledge-hook.md` と `setup-hook.md` の内容と一致した（確認: ユーザーの回答と kit の照合。手順 5-4 と 5-5 は、最近足された部分で、記憶では答えられない）。トリガーが来たときに kit のファイルを開くことを、確認した。承認を受けて、共通ルールの「作業の開始時に、次を読む」を、ファイルごとの読む時機に書き分けた（`docs-rules.md` は作業を始める前と更新時、2つのフックはトリガー時）。`templates/AGENTS.md`、`examples/setup-example.md`、`notes/AGENTS.md`、dotfiles の `AGENTS.md` を直した（dotfiles は1コミット）。
- 新しいセッションを `notes/` で開き、「共通ルールは何を読みますか」と聞いた。回答は、`notes/AGENTS.md` の「共通ルール」（パス、3項目、読めない場合の一文）と「読む順番」を、正しく答えた（確認: ユーザーの回答の貼り付け）。`CLAUDE.md` → `AGENTS.md` の読み込みは機能している。回答は `AGENTS.md` の文面の言い換えで、kit のファイルを開いたかは、この回答からは分からない（未検証）。
- 導入フックの実測結果に対するユーザーの承認を反映した。`notes/AGENTS.md` に「共通ルール」（3項目。`setup-hook.md` を含む）と「読む順番」を追加した。`notes/docs/` は、ローカル専用のままにする（`.gitignore` は変更しない）。実測で見つかった改善3点（導入の入口を兼ねるときの3項目目、ローカル専用のときの共有の確認、既存 `AGENTS.md` の読む順番）を `setup-hook.md` に反映した。判断は `docs/decisions.md`、記録は `workflow-kit/improvements.md`。
- 作業ディレクトリを `notes/` とし、`docs/` を `notes/docs/` に置く方針に変えた（ユーザーの指示）。直前の「`.obsidian/docs/` に暫定で置く」は取り消した。`.obsidian/` に作っていた `AGENTS.md`、`CLAUDE.md`、`docs/`（当日作成の未コミットのファイル）の内容を、この `docs/` に移して削除した。判断は `docs/decisions.md`。
- 導入フック `workflow-kit/setup-hook.md`（トリガー「workflowを導入して」）と見本 `examples/setup-example.md` を作り、`notes/` に対して初めて実行した。`AGENTS.md` と `CLAUDE.md` は既存のため上書きせず、`AGENTS.md` は差分案を示して承認待ち。`docs/` を新規に作った。結果と改善案はユーザーへの報告と `improvements.md` に残す。
- 共通機能の「ナレッジ化して」を、初めて実行した（`.obsidian/` を作業場として）。`exmem/inbox/` に3ファイルを作った。実測で見つかった改善3点が承認され、反映した（既存メモとの重複確認、根拠の表記に「ユーザーの発言」、話題を分けるときの下限）。記録は `workflow-kit/improvements.md`。
- `.obsidian/` の作業ログと判断記録を、git 履歴から復元した。「なぜ」が履歴に無い項目は「不明」とした。
- 本文の幅を、フォントサイズに比例させた。`readable-width.css` で `--file-line-width: 58em` を指定し、`readableLineLength` を有効にした（コミット `0fdd679`）。拡大しても1行の文字数が保たれる（スニペットのコメントより。既定は固定 700px）。

### 2026-10-03

- 日付プロパティの型を設定した。`types.json` で `created` と `updated` を `date` 型にした（`e81182c`）。`notes` のルートの `AGENTS.md` と `CLAUDE.md` の追加と同じコミット。
- ファイルエクスプローラーを整えた（`df2d261`）。フォントサイズ、CSS ファイルのアイコン（`file-explorer-compact.css`）。同じコミットで、改行コードを `.gitattributes` の `* text=auto eol=lf` で LF に統一した。
- 設定を CRLF に戻し、`colored-tags` の `data.json` を再び追跡し、エクスプローラーをコンパクトにした（`76d3fec`）。`file-explorer-compact.css` を新規作成した。
- 使っていないプラグインと古い設定を削除した（`82953b7`）。
  - コミュニティプラグインを `colored-tags` だけにした（`calendar` と `obsidian-icon-folder` を削除）。
  - コアプラグインの `graph` `canvas` `daily-notes` `templates` `note-composer` をオフに、`properties` をオンにした。
  - `daily-notes.json`、`graph.json`、`query.json` を削除し、`types.json` から旧プラグイン由来の `TQ_*` を削除した。
  - 検索から除外するフィルターを追加した（`.tmp.`、`_archive/`、`.claude/`）。
- テーマを Material Gruvbox に変更した（`78e3975`）。`Everforest` と `Obsidian gruvbox` を削除し、`Material Gruvbox` と `Typora-Vue` を追加した。行番号を表示、新規ノートの保存先を現在のフォルダ、添付の保存先を `./`、削除の確認をオンにした。スニペット `material-gruvbox-bold.css` を追加した。
- フォントを PlemolJP Console NF に変更した（`1d75fce`）。以前は Noto Sans JP、BIZ UDPゴシック、HackGen Console NF だった。基本のフォントサイズを 14 にした。
- `colored-tags` の `data.json` の追跡をやめた（`22b9fc0`。コミットメッセージによると、端末ごとのタグ色のキャッシュ）。
- `.obsidian/` を dotfiles から `notes` リポジトリへ移した（`cee0c82`、dotfiles 側は `bbb294b`）。`workspace.json`（端末ごとの状態）は除外した。移管前は、dotfiles の `windows/obsidian/.obsidian` へのジャンクションだった。

### 2025-09-23

- 前日に追加したプラグインの追加を、取り消した（`dcbe209`）。理由は不明。

### 2025-09-22

- 9つのコミュニティプラグインを追加した（`44054b5`）。`calendar`、`dataview`、`obsidian-kanban`、`obsidian-minimal-settings`、`obsidian-memos`、`obsidian-icon-folder`、`omnisearch`、`obsidian-mind-map`、`obsidian-outliner`。
