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

- 行き先: 転記済（2026-10-06 → exmem/knowledge/para-operations.md）

### 【汎用】PARA のディレクトリ構造は B1（フラット）にし、フックは開始と終了を先に作る（2026-10-06。ユーザーが承認）

- 行き先: 転記済（2026-10-06 → exmem/knowledge/para-operations.md）

### 【汎用】フックを「Project の寿命」と「セッションの寿命」の2層で連鎖させ、開始インタビューは育成・改善方式で作る（2026-10-06。ユーザーが承認）

- 行き先: 転記済（2026-10-06 → exmem/knowledge/para-operations.md）

### 【汎用】開始インタビューの指標を、1質問1行のイベントログで集める（2026-10-06。ユーザーの指示。形式と推奨指標は、同日にユーザーが承認）

- 固有: kit の `knowledge-hook.md` に節「改善案の指標の記録」を足した（版 `2026-10-06.19`。`docs/metrics/events.csv` があるときだけ記録する試験運用）。
- 行き先: 転記済（2026-10-06 → exmem/knowledge/para-operations.md。kit 固有の運用は kit に記載済みなので exmem には写していない）

### 【汎用】AI 活用と workflow の効果を、スレッド・セッションの指標で測る（2026-10-06。ユーザーが承認。試験運用）

- 固有: 当面は works の `AGENTS.md` の終了処理の手順として試験運用し、kit（`closing-hook.md`）への昇格は安定してから判断する。
- 行き先: 転記済（2026-10-06 → exmem/knowledge/ai-work-metrics.md。works の試験運用の状態は固有なので上の1行を残す）

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
