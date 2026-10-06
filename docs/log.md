# 作業ログ（log）

`works`（旧 `notes`。Obsidian Vault のトップ。PC ローカルのリポジトリ。PARA 構成）の現在状態と次にやること。2026-10-05 に、共有部分を別リポジトリ `workbase`（`resources/` に clone）に分け、`.obsidian/` を dotfiles へ戻した。対象は、Vault 全体の管理: `resources/exmem`（ナレッジ）、`resources/workflow-kit`（共通機能）、その他の `resources/`、`.obsidian/`（Obsidian の設定。実体は dotfiles）。判断の根拠・却下案・Gotchas は `docs/decisions.md`。作業の終わりに、Next Actions と Log を更新する。

`.obsidian/` の 2026-10-04 以前の Log は、git 履歴（`notes` の `git log -- .obsidian`、dotfiles の `bbb294b`）から復元したもの。コミットメッセージと差分から読み取れる範囲で、書かれていない理由は「不明」としている。dotfiles 側の 2026-10-02 より前の履歴は、履歴の作り直し（単一コミット化）で残っていない。

## Next Actions

- **PARA の使い方の検討（2026-10-06 開始）**: A・C は承認済み。残り: B（フックとディレクトリ構造の候補を比較して1案を採用）→ D（PC2 の学習で試行。`areas/learning/` と最初の Project `learn-c-pool-allocator`）。次のセッションの冒頭で、開始インタビュー（5項目）を手動で試し、実測を手順書の下書きにする。「プロジェクトを始めて」「閉じて」の手順書も、実測から起こす。試行で、上限（Project 3・Area 5）と契機を見直す。
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

- 提案（未承認）: `AGENTS.md` の固定パス（`C:\vault\works\...`）を `$WORKS_DIR` に置き換える（Linux での値は未確認）。
- `workbase` の公開範囲（最初は非公開で作る。公開するときは exmem に会社固有の情報が無いか確認する）。
- 決定の記録の書式に、状態（提案／決定）と出典（ユーザーの発言／AI の提案）の欄を持つべきか。部分的な指示の範囲確認の手順を、共通機能に足すか。

## Log

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
