# 作業ログ（log）

`notes`（Obsidian Vault のトップ。PC ローカルのリポジトリ。PARA 構成）の現在状態と次にやること。2026-10-05 に、共有部分を別リポジトリ `workbase`（`resources/` に clone）に分け、`.obsidian/` を dotfiles へ戻した。対象は、Vault 全体の管理: `resources/exmem`（ナレッジ）、`resources/workflow-kit`（共通機能）、その他の `resources/`、`.obsidian/`（Obsidian の設定。実体は dotfiles）。判断の根拠・却下案・Gotchas は `docs/decisions.md`。作業の終わりに、Next Actions と Log を更新する。

`.obsidian/` の 2026-10-04 以前の Log は、git 履歴（`notes` の `git log -- .obsidian`、dotfiles の `bbb294b`）から復元したもの。コミットメッセージと差分から読み取れる範囲で、書かれていない理由は「不明」としている。dotfiles 側の 2026-10-02 より前の履歴は、履歴の作り直し（単一コミット化）で残っていない。

## Next Actions

構造変更（`docs/decisions.md` の「Vault のトップを PC ローカルのリポジトリにし…」）。段階1〜4は実施済み（2026-10-05）。残り:
- **Obsidian の実機確認（ユーザー）**: `C:\vault\notes` を Vault として開き直し、検索、バックリンク、`.base`、テーマと CSS スニペット、`colored-tags` の色が、新しいトップ（実ディレクトリ + `resources/` の入れ子 + `.obsidian` のジャンクション）で動くか。`workspace.json` は新規になる（開いていたタブは消える）。
- **コミットと push（ユーザー）**: `workbase`（`C:\vault\notes\resources`。`origin/main` より2コミット先: kit の `2026-10-05.1` と `.2`）。dotfiles（未コミットの差分: `windows/obsidian/` `windows/office/` の追加、`links.map` `10_env.bat` `50_repos.bat` `.gitignore` `README.md` `AGENTS.md` `docs/log.md`）。新しいトップ（`C:\vault\notes`。初回コミットは未実施。remote は `worksample`（非公開）を設定済みで、push はしていない）。
- 段階5の残り: 旧 `notes` のリポジトリ（`C:\vault\repos\github.com\yuzucha16\notes`。clean、`origin/main` と同期）の GitHub 側アーカイブ化（外向きの操作。`gh` が未ログインなので、ユーザーが GitHub の Settings から行う）と、ローカルの扱い（バックアップ: `C:\vault\backup\notes-before-restructure-20261005`。しばらく残す）。ほかに、`workflow-kit/templates/AGENTS.md` の「`notes` が無いPCなど」の文言は、`notes` が共有リポジトリでなくなったので、`workbase` に直すか検討する（雛形の項目は変えない規則があるので、`improvements.md` に理由を残す）。
- コミット・push（ユーザー）: `workbase`（`C:\vault\notes\resources`）は `origin/main` より4コミット先（kit `2026-10-05.1`〜`.3`、段階5の文書修正）で、未 push。新しいトップ（`C:\vault\notes`）は、まだ1コミットも無い。
- Linux（WSL / ネイティブ）: `50_repos.sh` の `workbase` の clone、`.obsidian` の扱い、`NOTES_DIR` の値は TODO（dotfiles）。
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

- 提案（未承認）: `AGENTS.md` の固定パス（`C:\vault\notes\...`）を `$NOTES_DIR` に置き換える（Linux での値は未確認）。
- `workbase` の公開範囲（最初は非公開で作る。公開するときは exmem に会社固有の情報が無いか確認する）。
- 決定の記録の書式に、状態（提案／決定）と出典（ユーザーの発言／AI の提案）の欄を持つべきか。部分的な指示の範囲確認の手順を、共通機能に足すか。

## Log

### 2026-10-05

- ディレクトリ構造の変更を検討し、方針を決めた（ユーザーの選択。判断は `docs/decisions.md` の「Vault のトップを PC ローカルのリポジトリにし…」）。きっかけは、会社 PC で `_local` の作業もコミットしたいこと。検討した案: 現状維持、`company/` の入れ子、トップ非リポジトリ、重ね git、exmem・kit の単独化。決定: トップを PC ローカルのリポジトリにし、共有部分を `workbase` として `resources/` に直接 clone する。`.obsidian` は dotfiles へ戻す。fonts・wallpapers・`_archive/obsolete`（履歴ごと）は破棄、`office/` は dotfiles へ。ジャンクション越しは Grep / Glob が辿らないことを実測した。`git filter-repo` 2.47.0 を導入した。リポジトリ、ファイルの移動、dotfiles はまだ変更していない（文書の記録のみ）。
- 段階1を実施した（ユーザーの指示）。`notes` を一時ディレクトリへ clone し、`git filter-repo` で `fonts` `wallpapers` `_archive` `office` `_local/.gitkeep` と、トップのファイル（`.obsidian` `AGENTS.md` ほか）を履歴ごと除き、`resources/` をルートにした。結果: 58 → 30 コミット、139 → 68 ファイル（`exmem` 42、`workflow-kit` 11、`cheatsheets` 10、`handson` 5）。ルートに `AGENTS.md`、`CLAUDE.md`、`.gitattributes`（LFS なし）、`.gitignore` を足して1コミットにした。確認: 除外したパスの履歴の漏れ0、LFS 0、remote なし、改行は全ファイル LF、単独 clone した状態での wikilink 340件のうち未解決は8件（すべて規約の説明文にある書式の例で、実際の切れではない）。旧構成の記述（`_local`、`notes` がルート）が `workbase` 内の文書に残っている（修正は段階5）。実施中に、2026-10-04 の `.obsidian` の置き場の決定との食い違いを見つけて報告した。
- `.obsidian` を dotfiles へ戻す（A）を、10-04 の決定と根拠を示した上で、ユーザーが改めて選んだ。経緯と撤回の理由は `docs/decisions.md`（「`.obsidian` を dotfiles へ戻す」）。`workbase` 側の `obsidian-vault.md` と `app-config-placement.md` に、撤回済みを記録した（2コミット）。
- dotfiles を更新した（ユーザーの指示。Windows のみ。未コミット）。`windows/obsidian/.obsidian`（15ファイル。元と一致を確認）と `windows/office/`（17ファイル、`.gitattributes` つき）を追加し、`links.map` を `windows\obsidian\.obsidian|%NOTES_DIR%\.obsidian` に差し替え（`..\notes` の行は削除）、`50_repos.bat` に `workbase` の `git clone`（`%NOTES_DIR%\resources`、既にあれば skip）を追加した。`10_env.bat` のコメント、`.gitignore`（`workspace*.json`）、`README.md`、`AGENTS.md` を合わせた。`.bat` の改行は CRLF のまま。実行は未確認（リンクと clone は、トップの切り替えまで有効にしない）。
- `gh` が未ログインで、GitHub のリポジトリ作成と push は実行していない（この後、ユーザーが `workbase` を作成して push した。`origin/main` = `f588cc2` を確認）。
- 段階2を実施した（ユーザーの承認）。kit に導入項目 5「ワークスペース（Vault のトップ）の生成」を足し（`setup-hook.md`、`templates/workspace/`、見本、`improvements.md`）、版を `2026-10-05.1` にした。モバイル用プロンプトと見本の `kit:` を合わせた。
- 段階4を実施した（ユーザーの承認。個人用 PC、remote は非公開リポジトリ `worksample`、履歴ファイルは削除、の指示）。手順: ① 旧リポジトリ全体をバックアップ（`C:\vault\backup\notes-before-restructure-20261005`、1070ファイル。`ConsoleHost_history.txt`（177,425バイト）は、ユーザーの指示で削除したので含まない）。② ジャンクション `C:\vault\notes` を外し（リンクのみ。旧リポジトリは無傷）、実ディレクトリとして作り直した。③ `areas` `projects`（6ファイル）`archives` `docs` を移した。④ `workbase` を `C:\vault\notes\resources` に clone し、origin を GitHub に付け替えた（74ファイル。2コミット先）。端末ごとの `settings.local.json` 2件を旧位置から移した。⑤ `.obsidian` を dotfiles の `windows\obsidian\.obsidian` へのジャンクションにした（`30_link.bat link -n` のドライランで、リンクの解決を確認した上で、同じ `mklink /J` を1本だけ張った。15ファイル読める）。⑥ kit の項目 5 の手順で、トップを生成した（`.gitignore`、`.ignore`、`AGENTS.md`、`CLAUDE.md`、`areas/` `archives/` の `.gitkeep`、`git init`、`origin` = `worksample`。初回コミットも push もしていない）。自己点検: `resources/` と `.obsidian` が無視される、プレースホルダなし、共通ルールの節が雛形と一致、`resources/` は別リポジトリ。
- 切り替えの実測で、**トップの `.gitignore` が `resources/` を除外すると、Claude Code の Grep（ripgrep）が `resources/` の中を黙って飛ばす**ことを見つけた（`setup-hook` の検索が3件のみ。ジャンクション越しと同じ症状）。`.ignore` に `!/resources/` を置くと解消した（8件以上。確認: 2026-10-05）。kit に反映した（雛形 `ignore.template`、手順 6、自己点検、版 `2026-10-05.2`）。判断は `docs/decisions.md` の Facts。
- 段階5を実施した（ユーザーの指示）。`workbase` 内の旧構成の記述（`_local`、「`notes` がルート」、ホワイトリスト、LFS）を直した: `exmem/AGENTS.md` `exmem/README.md` `cheatsheets/CLAUDE.md` `cheatsheets/env/win11.md`（`dotfiles` だけを clone する手順に）、知識ノート7件（`obsidian-vault.md` は「現在の構造」の節を足し、旧い節に「撤回・変更済み」の注記を付けた。履歴は残した）。`updated` を 2026-10-05 にした。`exmem/contexts/` と、日付つきの履歴の記述は、書き換えていない。点検で、旧 `notes` のルートにあった `.gitattributes`（LF 統一）が新しいトップに引き継がれていないことを見つけ、トップに置き、kit の雛形に足した（版 `2026-10-05.3`）。`workbase` に2コミットを足した（kit、文書修正）。
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
