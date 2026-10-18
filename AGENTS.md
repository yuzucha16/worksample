# AGENTS.md

個人用 PC の作業場。PARA でこの PC のローカルの作業（個人開発など）を管理し、共有ナレッジ（`resources/`）を参照する。Obsidian の Vault のトップで、この PC だけのローカルなリポジトリ（remote: `worksample`。公開。2026-10-16 にユーザーが公開にした）。共有ナレッジは `resources/`（別リポジトリ `workbase` の clone）で、Vault 全体の規約は `resources/AGENTS.md`。

## 安全規則（先頭に置く。縮小・整理の対象外。変えるときはユーザーの承認）

- 機密・個人情報・この PC のローカルの情報（業務固有、個人的なもの）を、`resources/`（共有）に書かない。共有側のノートから、ローカル側（`areas/` `projects/` `archives/`）へ `[[リンク]]` を張らない（他の PC でリンク切れ）。`resources/` の変更は、`resources/` の中でコミットする。
- 決定として書くのは、ユーザーが明示または承認したものだけ。AI の提案は「提案」と書く。
- push は、下の許可リストのリポジトリの `main` だけ。許可リストに無いリポジトリへは push しない（公開リポジトリは、許可リストに載せたものだけ。2026-10-16 ユーザーの決定）。禁止のコマンド（`--force` など。一覧は kit の `docs-rules.md` の「しないこと」。`settings.json` の deny が機械的に止める）と、パスなしの `git add -A` / `git add .` は使わない（範囲が決まらず、他人の変更を巻き込むため。パス指定つきの `git add -A <パス>` は、削除・rename のステージに使ってよい。2026-10-15 ユーザーの決定）。
- コミットは、自分が変更したファイルだけをパス指定で。**コミット・push の前に、kit の `docs-rules.md` の「コミットと push」を、そのセッションで読んでいなければ読む**（`close` `wrap` などのフック経由でも、リポジトリが `resources/` や dotfiles でも同じ）。コミット前は `git diff --cached --stat` で行数を確認する。身元・トレーラー・機密の検索も、そこに従う（2026-10-15 ユーザーの決定。10-12 の違反を受けて）。
- 破壊的操作と、リスク・制約が生まれる変更は、事前に確認する。特に、ユーザー環境全体に効く設定、リンクやパスの構造の前提、選択肢が複数ある設計は、実装の前に前提と影響範囲を示して確認する（2026-10-15 の review。10-10〜10-12 の手戻り 3 件を受けて）。
- 手順書や規則が読めないときは、記憶で代用せず、ユーザーに伝えて止まる。

## 共通ルール

共通ルールの置き場は `$HOME\works\resources\workflow-kit`（WSL: `/mnt/c/Users/<Windows のユーザー名>/works/resources/workflow-kit`）。ユーザーが合言葉（手順書を呼ぶ短い言葉。日本語の別名つき）を言ったら、そこの `hooks.md` の表に従って手順書を読み、実行する（言われたときだけ）。`docs-rules.md` は、`docs/` の更新（`wrap` を含む）と、コミット・push の前に読む（開始時には読まない。2026-10-08〜。試験運用）。

## 読む順番

1. `README.md`（窓口。構成と管理。Vault 全体の規約は `resources/AGENTS.md`。`resources/` の作業のときに読む）
2. `docs/log.md`（開始時に読むのはここまで。「期日」の節があれば、今日以前または3日以内の項目を、**最初の返答で知らせて判断を求める**。判断はユーザーが決める）
3. `docs/decisions.md` と `docs/log-history.md` は開始時に読まない。何かを決める・変える前に、`decisions.md` を検索して、既存の決定と矛盾しないか確かめる。経緯が要るときは `log-history.md` を検索する。

下位の単位（`resources/` の中、`repos/` の各リポジトリ、`projects/` `areas/`）の「<名前> の続き」は、kit の `docs-rules.md` の「上の階層で起動して…」に従う。kit の手順が「`log.md` の Log に書く」と言うときは、`docs/log-history.md` の `## Log` の先頭に追記する（2026-10-15 に kit の `docs-rules.md` へ昇格した。ユーザーの決定）。

## 構成と管理

構成の表は `README.md`。`resources/` と `repos/` の各リポジトリは別の git リポジトリで、git 操作はそれぞれの中で行い、作業の前にその `AGENTS.md` を読む。`resources_p/` は PC ローカルの resources（この PC だけの情報の置き場。追跡しない。Vault 側の AI は読み書きしてよく、`areas/` などのような deny はしない）。

## AI 作業部屋（`projects/` `areas/` `archives/` を扱うとき）

- この 3 つの中の作業は、AI 作業部屋（専用の WSL ディストリビューション）の中で行う。Vault 側の AI（この `AGENTS.md` を読む AI）は、`projects/` `areas/` `archives/` を読まない・編集しない。`.claude/settings.json` で `Read` と `Edit` を deny している（雛形: `resources/workflow-kit/templates/workspace/claude-settings.template.json`。安全網であって境界の保証ではない。効くのは、このリポジトリのトップで起動したときだけ）。
- `room`（`resources/workflow-kit/room/`）は人が端末で実行する。AI は実行しない。
- 部屋の使い方と読み替えは `resources/workflow-kit/room/README.md` と `resources/workflow-kit/room-context.md`。
- `.claude/` は、プロジェクト固有の規則が要るリポジトリだけ `settings.json` を置いて追跡する（works のみ）。`settings.local.json` は、どのリポジトリでも追跡しない（2026-10-16 ユーザーの決定。実害が出たら個別に直す）。
- `.gitignore` に `**/_noai/`（AI に見せない領域。追跡しない）と `!**/ai/out/` を入れる（雛形: `gitignore.template`）。

## このワークスペース固有のルール

- `.obsidian/` の実体は dotfiles（`windows\obsidian\.obsidian`）。変更のコミットは dotfiles で行う（接頭辞 `[obsidian]`）。Obsidian が起動中は設定ファイル（`*.json`）を編集しない（上書きされて消える）。`workspace.json` は端末ごとの状態なのでコミットしない。詳細は `exmem/knowledge/obsidian-vault.md`。
- Obsidian 向けの作業では、導入済みの外部スキル（`obsidian@obsidian-skills`。導入の正本は dotfiles の `manifests/claude-plugins.txt`）を使う。ノートの記法は `obsidian-markdown`、Bases は `obsidian-bases`、Canvas は `json-canvas`、Vault の操作は `obsidian-cli`、Web ページの本文抽出は `defuddle`、テンプレートからの Markdown 生成は `knap`。スキル本体は写さない（更新はプラグインが持つ）。Claude Code 以外のエージェントには届かない。
- 記録: `docs/metrics/events.csv` に足すのは、`goal_change`（探索型でゴールが変わったとき。2026-10-14 に追加）、開始時の質問（`interview`）だけ（`again` と `gap` は 2026-10-16 に廃止。kit の `139091c` に合わせた。承認の確認 `approval` と改善案の行は、2026-10-08 から足さない）。`wrap` では「今日の遠回りは、なし・少し・大きく」を1問聞く。手順・列・保存先は `docs/metrics/README.md` の「エージェントの記録手順」。
- リポジトリ間の整合の基準: `docs/alignment-baseline.md`（`review` の入力 8 が、各行を今の状態と比べる。2026-10-16 ユーザーの決定）。
- `git add -f` で、ignore 済みのファイルを追加しない。

## 規模の凍結（2026-10-08〜判定日 2026-11-08。ユーザーの決定。試験運用）

手順書・指標・規則を足すときは、同時に1つ畳む。この指示（`AGENTS.md`）に、指標の数値目標を書かない（指標はユーザーの見直し専用）。根拠と判定の基準は `docs/decisions.md`。

## push の許可リスト（2026-10-08 ユーザーの決定。試験運用）

エージェントが push してよいのは、次のリポジトリの `main` だけ。条件（公開範囲の確認、fast-forward、機密の検索）は、kit の `docs-rules.md` の「push」。

| リポジトリ | ブランチ | 備考 |
|---|---|---|
| `works`（remote: `yuzucha16/worksample`。公開） | `main` | このリポジトリ |
| `resources/`（remote: `yuzucha16/workbase`。公開） | `main` | 2026-10-16 ユーザーの決定。公開のまま |
| dotfiles（remote: `yuzucha16/dotfiles`。公開） | `main` | 同上 |

ほかのリポジトリは対象外。公開リポジトリは、kit の条件で機密の検索を広げる。クラウドのセッションからも、この許可リストのリポジトリには、同じ条件で push してよい（2026-10-08 ユーザー）。

## コミット

- メッセージは `[領域] 変更内容`。`git add` はパスを指定する。
