# AGENTS.md

個人用 PC の作業場。PARA でこの PC のローカルの作業（個人開発など）を管理し、共有ナレッジ（`resources/`）を参照する。Obsidian の Vault のトップで、この PC だけのローカルなリポジトリ（remote: 非公開 `worksample`）。共有ナレッジは `resources/`（別リポジトリ `workbase` の clone）で、Vault 全体の規約は `resources/AGENTS.md`。

## 安全規則（先頭に置く。縮小・整理の対象外。変えるときはユーザーの承認）

- 機密・個人情報・この PC のローカルの情報（業務固有、個人的なもの）を、`resources/`（共有）に書かない。共有側のノートから、ローカル側（`areas/` `projects/` `archives/`）へ `[[リンク]]` を張らない（他の PC でリンク切れ）。`resources/` の変更は、`resources/` の中でコミットする。
- 決定として書くのは、ユーザーが明示または承認したものだけ。AI の提案は「提案」と書く。
- push は、下の許可リストのリポジトリの `main` だけ。公開リポジトリへ push しない。`--force`、`--no-verify`、`--amend`、`reset --hard`、`rebase`、`git add -f`、パスなしの `git add -A` / `git add .` は使わない（範囲が決まらず、他人の変更を巻き込むため。パス指定つきの `git add -A <パス>` は、削除・rename のステージに使ってよい。2026-10-15 ユーザーの決定）。
- コミットは、自分が変更したファイルだけをパス指定で。身元・トレーラー・機密の検索は、kit の `docs-rules.md` の「コミットと push」に従う。
- 破壊的操作や、リスク・制約が生まれる変更は、事前に確認する。
- 手順書や規則が読めないときは、記憶で代用せず、ユーザーに伝えて止まる。

## 共通ルール

共通ルールの置き場は `$HOME\works\resources\workflow-kit`（WSL: `/mnt/c/Users/<Windows のユーザー名>/works/resources/workflow-kit`）。ユーザーが合言葉（手順書を呼ぶ短い言葉。日本語の別名つき）を言ったら、そこの `hooks.md` の表に従って手順書を読み、実行する（言われたときだけ）。`docs-rules.md` は、`docs/` の更新（`wrap` を含む）と、コミット・push の前に読む（開始時には読まない。2026-10-08〜。試験運用）。

## 読む順番

1. `docs/log.md`（現在状態だけ。4KB 目安）
2. `resources/AGENTS.md`（Vault 全体の規約）
3. `docs/log.md` の「期日」に、今日以前（または3日以内）の項目があれば、**最初の返答で知らせ、判断を求める**（判断はユーザーが決める）。

`docs/decisions.md` と `docs/log-history.md` は開始時に読まない。何かを決める・変える前に、`decisions.md` を検索して、既存の決定と矛盾しないか確かめる。kit の手順が「`log.md` の Log に書く」と言うときは、`docs/log-history.md` の `## Log` の先頭に追記する（試験運用。1週間後に kit の `docs-rules.md` へ昇格するか判断）。

## 構成と管理

| パス | 内容 | 管理 |
|---|---|---|
| `areas/` `projects/` `archives/` | PARA。この PC のローカルの作業 | このリポジトリ |
| `docs/` `AGENTS.md` `CLAUDE.md` | この PC の作業ログと規約 | このリポジトリ |
| `resources/` | 共有ナレッジ（`workbase`）。このリポジトリの `.gitignore` で除外する | 別リポジトリ（git 操作は `resources/` の中で行う） |
| `.obsidian/` | Obsidian の設定。dotfiles からのジャンクション。このリポジトリでは追跡しない | dotfiles |

## このワークスペース固有のルール

- `.obsidian/` の実体は dotfiles（`windows\obsidian\.obsidian`）。変更のコミットは dotfiles で行う（接頭辞 `[obsidian]`）。Obsidian が起動中は設定ファイル（`*.json`）を編集しない（上書きされて消える）。`workspace.json` は端末ごとの状態なのでコミットしない。詳細は `exmem/knowledge/obsidian-vault.md`。
- 記録: `docs/metrics/events.csv` に足すのは、`again`、`gap`、開始時の質問（`interview`）だけ（承認の確認 `approval` と改善案の行は、2026-10-08 から足さない）。ユーザーが `again`（または「前にも言った」）と書いたら `kind=again` の行を足し、前提を昇格する案を出す。`wrap` では「今日の遠回りは、なし・少し・大きく」を1問聞く。手順・列・保存先は `docs/metrics/README.md` の「エージェントの記録手順」。
- 自動採用（`wrap` の改善案を、承認なしに規則の節へ追加・削除する仕組み）は、2026-11-08 まで停止する（2026-10-08 ユーザーの決定。規則を生む流量を絞るため）。再開するかは、11-08 の判定で決める。安全規則と手順の本体は承認制。

## 規模の凍結（2026-10-08〜判定日 2026-11-08。ユーザーの決定。試験運用）

手順書・指標・規則を足すときは、同時に1つ畳む。この指示（`AGENTS.md`）に、指標の数値目標を書かない（指標はユーザーの見直し専用）。根拠と判定の基準は `docs/decisions.md`。

## push の許可リスト（2026-10-08 ユーザーの決定。試験運用）

エージェントが push してよいのは、次のリポジトリの `main` だけ。条件（公開範囲の確認、fast-forward、機密の検索）は、kit の `docs-rules.md` の「push」。

| リポジトリ | ブランチ | 備考 |
|---|---|---|
| `works`（remote: `yuzucha16/worksample`。非公開） | `main` | このリポジトリ |

`resources/`（`workbase`）、dotfiles、ほかのリポジトリは対象外（公開範囲が決まってから、ユーザーが広げる）。`workbase` を push するときは、ユーザーが行う。クラウドのセッションからも、この許可リストのリポジトリには、同じ条件で push してよい（2026-10-08 ユーザー）。

## コミット

- メッセージは `[領域] 変更内容`。`git add` はパスを指定する。
