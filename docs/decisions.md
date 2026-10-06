# 判断の記録（decisions）

なぜそうしたか（Why）、却下案、遭遇した詰まり、実機で確認した事実を残す。現在の状態と次にやることは `docs/log.md`。

`.obsidian/` に関する 2026-10-04 以前の項目は、git 履歴と、`exmem/knowledge/` の記述から復元したもの。根拠と却下案が履歴に残っていないものは、Facts に事実として書く（判断の理由は推測で補わない）。

## Principles

- 【汎用】作業ログは `exmem` に置かず、作業ディレクトリ側の `docs/` に置く。 行き先: 転記済（2026-10-06 → kit/docs-rules.md、exmem/workflow-kit.md）
- 【汎用】小さく一過性のディレクトリには、専用の `docs/` を置かない。親の作業ディレクトリの `docs/` に含める。 行き先: 転記済（2026-10-06 → kit/docs-rules.md。exmem 側にも済み）
- 【汎用】アプリが自動で書き換えるファイルを追跡するかは、次の5項目で決める。 行き先: 転記済（2026-10-06 → exmem/app-config-placement.md）
- 【この件】Obsidian の設定は、使っているものだけに絞る。 行き先: 転記済（2026-10-06 → exmem/obsidian-vault.md）
- 【汎用】記録する決定は、ユーザーが明示したものだけにする。AI の提案は「提案」と書き、承認の確認が取れるまで決定として書かない。 行き先: 転記済（2026-10-06 → kit/docs-rules.md。exmem 側にも済み）

## Decisions

### 【汎用】PARA の `areas/` `projects/` `archives/` の役割と判断基準を定める（2026-10-06。ユーザーが承認。試行で見直す前提）

- 決めたこと（役割）:
  - `projects/<名>/`: 完了条件のある取り組み。完了条件・見直し日・成果物を持つ。達成か中止で `archives/` へ移す。
  - `areas/<名>/`: 終わりのない責任領域。維持する基準と、その領域の Project 一覧を持つ。責任が無くなったときだけ `archives/` へ移す。
  - `archives/`: 終了したものの保管。参照用で更新しない。
- 決めたこと（判断基準）:
  1. 完了条件を1文で書けるなら Project、書けないなら Area。
  2. 見直し日（期限）を置けないものは、Project にしない。
  3. 成果物が1つに特定できなければ、Project を分ける。
  4. 複数セッションにまたがる Project は `docs/` を持つ。1日で終わるものは親の `docs/` に含める（P2 の規則どおり）。
  5. 同時進行の上限は、Project 3件、Area 5件（仮の値。試行で見直す）。
  6. `archives/` へ移す契機: 完了条件の達成、中止の判断、見直し日を2回超えて更新が無いとき。
  7. 閉じるとき、再利用できる知識は「ナレッジ化して」で exmem へ渡す。経緯は `docs/` に残す。
  8. 一般化できる学習内容は exmem へ。業務固有のものは、そのリポジトリの中に置く（PC1 の内容を PC2 側へ運ばない）。
- 根拠: PARA の本来の区別は「終わらせることを目指すか（Project）、維持することが目的か（Area）」。ユーザーは、期間未定の案件に参画しているシニアエンジニア。終わりのない責任は Area、期限・完了条件のある成果物は Project に分ける。
- 却下案: 未検討（ユーザーは、この粒度で良いと承認）。
- 行き先: 転記待ち（→ exmem/inbox/2026-10-06-para-lifecycle-question-metrics.md）

### 【汎用】PARA のディレクトリ構造は B1（フラット）にし、フックは開始と終了を先に作る（2026-10-06。ユーザーが承認）

- 決めたこと: `areas/<領域>/`（`README.md` に基準と Project 一覧）と `projects/<名>/`（`README.md` に完了条件・見直し日・成果物・状態。複数セッションにまたがるなら `docs/`）を並べる。README の frontmatter に `status` `review` `area` を持たせる（項目は試行で見直す）。フックは、開始（Project を始める）と終了（Project を閉じる）を先に手順書で試す。見直しフックと点検スクリプトは、試行で必要性が見えてから。
- 根拠: PARA の本来の形で、移動が `projects/` → `archives/` だけで済む。
- 却下案: 入れ子（`areas/<領域>/projects/`）。閉じるときに所属が切れ、複数の Area に関わる Project で破綻するため。Area ごとの `docs/`。Project が少ない間は空の `docs/` が増えるため。
- 行き先: 転記待ち（→ exmem/inbox/2026-10-06-para-lifecycle-question-metrics.md）

### 【汎用】フックを「Project の寿命」と「セッションの寿命」の2層で連鎖させ、開始インタビューは育成・改善方式で作る（2026-10-06。ユーザーが承認）

- 決めたこと:
  - 連鎖は `open（プロジェクトを始めて）→ [開始インタビュー → 作業 → 終了処理して（既存）]×N → close（プロジェクトを閉じて）`。セッションの層で欠けていた開始側として、開始インタビューを足す。
  - 開始インタビューは、聞くこと5項目（ゴール、前提・制約、対象の Project、読んでほしい資料、やらないこと）を叩き台にする。先に `docs/log.md` の Next Actions と Open Questions を読み、答えがあるものは聞かず確認だけにする。出力は「今日のゴール」の要約で、承認を取る。終了処理で、開始時のゴールと結果を突き合わせて Log に書く。
  - 育成・改善方式: 最初は、プラン方式、またはユーザーがプロンプトで渡す形から始める。実測で、徐々にフォーマット化して確度を上げる。作業の種類（文書作成: 仕様・設計・調査など、開発: 設計・実装・評価など）をカテゴライズし、抽象化・継承の考え方で、共通部分と種類ごとの差分に分けて定型化する方向（実現方法は未決）。
- 根拠: セッションの開始側にだけフックが無く、ゴールや前提を毎回ユーザーが手で書いている。
- 懸念（未解決）: 毎回のインタビューは重い。小さな再開では「Next Actions の先頭でよいか」の1問に縮める設計が要る。名前（「作業を始めて」など）は、「プロジェクトを始めて」と衝突しないよう、試行で決める。
- 行き先: 転記待ち（→ exmem/inbox/2026-10-06-para-lifecycle-question-metrics.md）

### 【汎用】開始インタビューの指標を、1質問1行のイベントログで集める（2026-10-06。ユーザーの指示。形式と推奨指標は、同日にユーザーが承認）

- ユーザーの指示: 質問数（母数）、回答数（回答率）、採用数（採用率）、修正・補足の回数（適合率）、AI が推奨する指標を、全体・Area・Project・セッションの単位で集め続ける。最終的に、AI に提案・回答をループさせる。
- AI の提案（未承認）: 正本は `docs/metrics/interview-events.csv`（1質問・1提案につき1行。集計は `summarize.ps1`）。聞き取りと承認の確認を `kind` で分ける。推奨指標は、冗長率（答えが `docs/` にあった質問）と覆り率（採用後に撤回）。セッションの達成度と作業の種類別の集計は、必要になったら足す。AI が記録し、ユーザーに作業を求めない。
- 却下案: 質問ごとに別ファイル（集計が難しい）、Project ごとに別の CSV（Area・全体の集計に結合が要る）。
- 確認済み: 15行を、このセッションの会話から `backfill` で起こし（推定）、集計スクリプトが動いた（2026-10-06）。
- 追加の指示（2026-10-06。ユーザー）: 同じ考え方の指標（回答率・採用率・適合率・冗長率・覆り率のいずれか）を、既存の改善フックにも適用して収集する。指標自体も改善対象にする。実施: ファイルを `events.csv` に改め、`kind=improvement` を足した。`knowledge-hook.md` の「このフックの改善」に節「改善案の指標の記録」を足した（kit の版 `2026-10-06.19`。`docs/metrics/events.csv` があるときだけ記録する。試験運用）。`improvements.md` の既存66件を `basis=import`（状態列だけから。`fix` などは空）で取り込んだ。「セッション」を、開始インタビューから終了処理までの区間と定義した（会話の単位ではない）。`live` は、回答を受けた同じターンで記録した行。
- 確認済み（2026-10-06）: 取り込んだ改善案の採用率は約98%（回答63件中62件）で、判別力が低い。却下は撤回の1件だけ。このため、改善案では採用率より、`fix`（直されたか）と `reversed`（後で覆ったか）を `live` で取る方が、質を測れると考える（仮説。`live` の行が溜まったら確認する）。
- 行き先: 転記待ち（→ exmem/inbox/2026-10-06-para-lifecycle-question-metrics.md）

### 【汎用】AI 活用と workflow の効果を、スレッド・セッションの指標で測る（2026-10-06。ユーザーが承認。試験運用）

- 決めたこと:
  - 用途はユーザー本人の自己改善だけ。忖度のない評価にするため、観測できる行動と件数だけを取り、AI の印象評価（段階評価）は使わない。各行に根拠（ユーザーの発言の要旨）を残す。
  - 用語: スレッド = Claude Code の1会話（jsonl 1本）、セッション = 既存の定義（開始インタビュー〜終了処理）。紐づけは `sessions.csv` の `thread_id`。
  - 指標の構成: 規模・分割（Area あたり Project 数、Project のリードタイム・完了条件の達成・見直し日の超過、Project あたりスレッド数、スレッドあたりセッション数とその逆）、自走（ターン長の中央値と上位 10% 点、ターンあたりのツール数、最大トークン）、品質（`fix` `gap` `reversed` と、起因 `cause`、セッションの `outcome`）、リテラシー（最初の依頼の完備度 0〜4、`review` 件数、仕組み化の件数）。無駄の合図（紐づかないスレッド、放置、ツールエラー率、打ち切りターン）も取る。
  - 取得: スレッドは jsonl から自動抽出（`extract-threads.ps1` → `threads.csv`）。ターンは30分で打ち切る。判断項目は、終了処理で AI が `sessions.csv` に1行足す。補正の行に `cause`（`ai` `user` `review`）を足す。
  - 組込み: 当面は works の `AGENTS.md` の終了処理の手順として試験運用し、kit（`closing-hook.md`）への昇格は安定してから判断する。
  - 開始の形の比較（ユーザーが承認。2026-10-06）: `sessions.csv` に `start_mode`（`bare` = 「作業を始めて」だけ、`briefed` = 最初の依頼に背景（ゴール・完了条件・制約・やらないこと）を添える）を足す。次のトライアルは、背景なし → 背景ありの順に試す。背景なしの回は、開始インタビューの効果（`gap` `fix` `冗長率`）を測り、背景ありの回は、最初の依頼の完備度（`prompt_complete`）を測る。理由: 背景を最初に渡すと、インタビューの効果が隠れ、完備度は開始の形の結果になるので、混ぜると効果と指示の質を分けて読めない。却下案: 毎回背景を渡す、毎回渡さない（どちらも、片方の指標が測れなくなる）。この項目は、転記先のメモには未記載（追記は、ユーザーが明示したときだけ）。
- 根拠: 壁時計の時間は `--resume` の離席が混ざり（実測で最大約5日）、自走時間にならない。ターン長で測る。自走時間だけを目標にすると、監督を減らして品質が落ちても良く見えるので、品質の指標と対にする。`fix` の起因が混ざっていると、AI の欠陥とユーザーの批判的レビューの成果を区別できない。
- 却下案: Project 数を規模の指標にする（時点の値で、効果に直結しない）。Min の時間（1行の質問が最小になるだけで無意味）。平均（外れ値に弱い。中央値と上位 10% 点にする）。総合スコア（n が小さく、重みの根拠が無いので当面作らない）。概念の理解の測定（会話から推定しにくく、当面は対象外）。
- 確認済み（2026-10-06）: jsonl から全52本を7.6秒で抽出できた（根拠: `extract-threads.ps1` の実行）。1応答が複数行に分かれ、同じ `message.id` と `usage` が繰り返される（601行が170応答）ので、`message.id` で一意化している（根拠: 集計）。
- 行き先: 転記待ち（→ exmem/inbox/2026-10-06-ai-work-metrics-transcripts.md）

### 【この件】PARA 試行の前提（2026-10-06。ユーザーの明示）

- PC1（会社 PC、remote なしのローカルリポジトリ）と PC2（個人 PC、非公開 remote `worksample`）は、別リポジトリ・別インスタンスで、同じ構造を使い回す。
- 管理の優先順位は、案件の業務、学習、個人開発の順。
- 最初の試行は PC2 の学習（C か C++。選択は最初の Project の Open Question）。PoC として改善プロセスを回し、kit を強化してから PC1 に投入する。
- `areas/dev-env` は廃止済み（CA 証明書は `$HOME\.certs` へ移行済み）。
- 行き先: local（この PC のトップの運用方針）

### 【この件】会社 CA 証明書の置き場を `areas/dev-env/certs/` から `$HOME/.certs` に移す（2026-10-06。上の `certs` の移動を置き換える）

- 確認済み（2026-10-06）: 旧 `areas/dev-env/certs` は空。
- 行き先: 転記済（2026-10-06 → exmem/knowledge/obsidian-vault.md）

### 【汎用】docs の項目に「行き先」を持たせ、滞留するデータを検出する（2026-10-06。試験運用）

- 行き先: 転記済（2026-10-06 → exmem/knowledge/workflow-kit.md、kit/docs-rules.md）

### 【この件】Vault のトップを `notes` から `works` に rename し、`certs` を `areas/dev-env/certs/` へ移す（2026-10-06）

- 行き先: 転記済（2026-10-06 → exmem/obsidian-vault.md）

### 【汎用】Vault のトップを PC ローカルのリポジトリにし、共有部分を `workbase` として入れ子で clone する（2026-10-05）

- 行き先: 転記済（2026-10-06 → exmem/obsidian-vault.md）

### 【汎用】「ナレッジ化して」の自己点検を、点検スクリプトで機械化し、編集済みの知識との重複を明記する（2026-10-05）

- 行き先: 転記済（2026-10-06 → kit/knowledge-hook.md、exmem/workflow-kit.md）

### 【汎用】「ナレッジ化して」で作った inbox のメモは、コミットしない（2026-10-05。全体に適用）

- 行き先: 転記済（2026-10-06 → kit/docs-rules.md、exmem/workflow-kit.md）

### 【汎用】「ナレッジ化して」の改善2点を採用する（2026-10-05）

- 行き先: 転記済（2026-10-06 → kit/knowledge-hook.md、exmem/workflow-kit.md）

### 【この件】Linux 側の試験スクリプトを dotfiles の `tests/` に置く（2026-10-05）

- 行き先: 転記済（2026-10-06 → dotfiles/docs/decisions.md）

### 【汎用】（撤回済み 2026-10-05）項目 5 の既定の対象を、Claude を開いたディレクトリ（cwd）にする

- 行き先: 転記済（2026-10-06 → kit/improvements.md、exmem/workflow-kit.md）

### 【汎用】「workflowを導入して」だけでワークスペースを生成する（2026-10-05）

- 行き先: 転記済（2026-10-06 → kit/setup-hook.md、exmem/workflow-kit.md）

### 【汎用】コミットの権限をエージェントに移す（2026-10-05。全体に適用）

- 行き先: 転記済（2026-10-06 → kit/docs-rules.md、exmem/workflow-kit.md）

### 【汎用】トップのワークスペースを kit の導入フックで生成する（2026-10-05）

- 行き先: 転記済（2026-10-06 → kit/setup-hook.md、exmem/workflow-kit.md）

### 【この件】`.obsidian` を dotfiles へ戻す（2026-10-05。2026-10-03 と 2026-10-04 の決定を撤回）

- 行き先: 転記済（2026-10-06 → exmem/app-config-placement.md）

### 【汎用】`notes/` を作業ディレクトリとし、`docs/` を `notes/docs/` に置く（2026-10-04）

- 行き先: 転記済（2026-10-06 → exmem/workflow-kit.md）

### 【汎用】`notes/docs/` はローカル専用のままにする（2026-10-04）

- 行き先: 転記済（2026-10-06 → exmem/workflow-kit.md）

### 【汎用】共通機能の導入手順を、「workflowを導入して」の導入フックにする（2026-10-04）

- 行き先: 転記済（2026-10-06 → kit/setup-hook.md、exmem/workflow-kit.md）

### 【汎用】`contexts/` を「`notes` から見えない場所の引継ぎコンテキスト」にする（2026-10-04）

- 行き先: 転記済（2026-10-06 → exmem/knowledge/workflow-kit.md、exmem/README.md、exmem/AGENTS.md）

### 【この件】`.obsidian/` を dotfiles から `notes` リポジトリへ移した（2026-10-03）

- 行き先: 転記済（2026-10-06 → exmem/obsidian-vault.md）

### 【汎用】改行コードを LF に統一する（2026-10-03）

- 行き先: 転記済（2026-10-06 → exmem/git-line-endings.md）

### 【この件】`colored-tags` の `data.json` は追跡する（2026-10-04）

- 行き先: 転記済（2026-10-06 → exmem/app-config-placement.md）

### 【この件】`types.json` で `created` と `updated` を日付型にする（2026-10-03）

- 決めたこと: `created` と `updated` のプロパティを `date` 型にする（`e81182c`）。
- 根拠: Bases での並べ替えや日付フィルタが正しく動く（`exmem/knowledge/obsidian-vault.md` の Proposals の記述）。
- 却下案: 履歴から不明。
- 行き先: local（Obsidian 固有の設定値）

### 【この件】ファイルアイコンは CSS のみで種類ごとに色分けする（2026-10-04）

- 行き先: 転記済（2026-10-06 → exmem/obsidian-appearance.md）

### 【この件】本文の幅をフォントサイズに比例させる（2026-10-04）

- 行き先: 転記済（2026-10-06 → exmem/obsidian-vault.md）

## Facts

- 【汎用】ripgrep（Claude Code の Grep を含む）は `.gitignore` を尊重する。 行き先: 転記済（2026-10-06 → exmem/modern-cli-tools.md、kit/templates/workspace/ignore.template）
- 【この件】`docs/` は、トップのリポジトリで追跡する（共有の `workbase` には載らない）。2026-10-04 の「`notes/docs/` はローカル専用のままにする」の趣旨（共有リポジトリに載せない）は保たれる。個人用 PC では、非公開 remote（`worksample`）へ push するかは、ユーザーが決める。 行き先: local（この PC のトップの運用）
- 【汎用】ジャンクション越しのディレクトリは、Claude Code の Grep / Glob、`rg`（既定）、PowerShell の `Get-ChildItem -Recurse` が辿らない。 行き先: 転記済（2026-10-06 → exmem/modern-cli-tools.md）
- 【この件】`_archive/obsolete/` は、プロジェクト管理の旧雛形27ファイル（プレースホルダ `your_project` など）で、作成は 2026-10-02 の1コミットだけ。使われた形跡は、コミットからは見つからなかった（確認: 2026-10-05、根拠: `git log -- resources/_archive`）。 行き先: local（廃止した旧雛形の事実）
- 【汎用】`git filter-repo` 2.47.0 を scoop で導入した（2026-10-05。ユーザーの承認）。 行き先: 転記済（2026-10-06 → exmem/git-subdirectory-split.md）
- 【この件】`notes` のルートに作った `docs/` は、`.gitignore` のホワイトリスト（`/*`）により、既定でローカル専用になる（確認: 2026-10-04、根拠: `git check-ignore -v docs/log.md` が `.gitignore:3:/*` を返した）。共有するには、`.gitignore` に `!/docs/` を足す必要がある。 行き先: 破棄（旧 `.gitignore` のホワイトリストは廃止済み）
- 【この件】`notes` の `AGENTS.md` と `CLAUDE.md` は、導入フックの実行前から存在した。`CLAUDE.md` は `@AGENTS.md` の1行（確認: 2026-10-04、根拠: ファイルの読み取り）。 行き先: 破棄（導入時の観測。log に記録済み）
- 【この件】テーマは Material Gruvbox。以前は Obsidian gruvbox と Everforest で、`78e3975`（2026-10-03）で変更した。変更の理由は、履歴から不明。Zed の自作テーマ（Material Gruvbox Dark）と同じ名前だが、そろえる意図があったかは未確認（仮説）。 行き先: local（この Vault のテーマ）
- 【この件】フォントは PlemolJP Console NF（UI・本文・等幅とも）。以前は Noto Sans JP、BIZ UDPゴシック、HackGen Console NF 系で、`1d75fce`（2026-10-03）で変更した。変更の理由は、履歴から不明。 行き先: local（この Vault のフォント）
- 【この件】現在の Obsidian の設定（確認: 2026-10-04、根拠: `.obsidian/*.json` の読み取り）: 行き先: local（現在の Obsidian の設定値）
  - 新規ノートの保存先は現在のフォルダ（`newFileLocation: current`）、添付は `./`、行番号を表示、削除の確認あり、タブ幅 2、検索から除外するフィルターは `.tmp.` `_archive/` `.claude/`。
  - コミュニティプラグインは `colored-tags` だけ。有効なスニペットは `material-gruvbox-bold`、`file-explorer-compact`、`readable-width`。
  - 有効なコアプラグインは、`file-explorer` `global-search` `switcher` `backlink` `outgoing-link` `tag-pane` `properties` `page-preview` `command-palette` `editor-status` `bookmarks` `outline` `word-count` `file-recovery` `sync` `bases`。
- 【この件】食い違い: `exmem/knowledge/obsidian-vault.md` の「設定」節（2026-10-01 時点の記述）は、現在の設定と違う。 行き先: 転記済（2026-10-06 → exmem/obsidian-vault.md。設定節が現状と一致していることを確認）
- 【この件】2025-09-22 に、9つのコミュニティプラグインを追加し（`44054b5`）、翌日に取り消した（`dcbe209`）。 行き先: 転記済（2026-10-06 → exmem/obsidian-vault.md）
- 【この件】dotfiles 側の 2026-10-02 より前の履歴は、履歴の作り直しで残っていない（確認: 2026-10-04、根拠: `git log --all -- windows/obsidian` の結果が、初期コミットと `bbb294b` だけ）。 行き先: 転記済（2026-10-06 → exmem/workflow-kit.md）

## Gotchas

- 状況: `colored-tags` の `data.json` を、追跡する・しないが2回切り替わった
  - 【この件】行き先: 転記済（2026-10-06 → exmem/app-config-placement.md、exmem/workflow-kit.md）
- 状況: AI が提案した記録先を「決定済み」と書いて進め、ユーザーに指摘された
  - 【汎用】行き先: 転記済（2026-10-06 → exmem/human-ai-decision-loop.md）