# AGENTS.md

個人用 PC の作業場。PARA でこの PC のローカルの作業（個人開発など）を管理し、共有ナレッジ（`resources/`）を参照する。

Obsidian の Vault のトップ。この PC だけのローカルなリポジトリ（remote: 非公開リポジトリ `https://github.com/yuzucha16/worksample`）。共有ナレッジは `resources/`（別リポジトリ `workbase` の clone）にあり、Vault 全体の規約は `resources/AGENTS.md`。

## 共通ルール

共通ルールの置き場は `$HOME\works\resources\workflow-kit`（WSL: `/mnt/c/Users/<Windows のユーザー名>/works/resources/workflow-kit`）。次の時機に、該当のファイルを読む。

- `docs-rules.md`: 作業を始める前と、`docs/` を更新するときに読む。`docs/` の運用。作業の終わりに `docs/log.md` と `docs/decisions.md` を更新する。
- `wrap-hook.md`: ユーザーが「wrap」（別名「終了処理して」）と言ったときに読み、実行する（言われたときだけ）。作業の終わりの `docs/` 更新・棚卸し・ナレッジ化・コミットを、順に行う。
- `stock-hook.md`: ユーザーが「stock」（別名「ナレッジ化して」）と言ったときに読み、実行する（言われたときだけ）。書き込みは `exmem/inbox/` の新規ファイルだけ（例外は `stock-hook.md`）。
- `integrate-hook.md`: ユーザーが「integrate」（別名「inboxを整理して」）と言ったときに読み、実行する（言われたときだけ。exmem 側の作業）。
- `init-hook.md`: ユーザーが「init」（別名「workflowを導入して」）と言ったときに読み、実行する（言われたときだけ。このワークスペース配下の作業ディレクトリへの導入の入口）。

上のファイルが読めない場合（`resources/` を clone していない PC など）は、記憶で代用せず、ユーザーに伝えて止まる。

## 読む順番

1. `docs/log.md`
2. `resources/AGENTS.md`（Vault 全体の規約）
3. `docs/decisions.md`

## 構成と管理

| パス | 内容 | 管理 |
|---|---|---|
| `areas/` `projects/` `archives/` | PARA。この PC のローカルの作業 | このリポジトリ |
| `docs/` `AGENTS.md` `CLAUDE.md` | この PC の作業ログと規約 | このリポジトリ |
| `resources/` | 共有ナレッジ（`workbase`）。このリポジトリの `.gitignore` で除外する | 別リポジトリ（git 操作は `resources/` の中で行う） |
| `.obsidian/` | Obsidian の設定。dotfiles からのジャンクション。このリポジトリでは追跡しない | dotfiles |

## このワークスペース固有のルール

- このリポジトリの remote は、非公開リポジトリ `worksample` だけ。公開リポジトリへ push しない。
- ローカル側から共有側（`resources/`）への `[[リンク]]` は張ってよい。共有側のノートから、ローカル側（`areas/` `projects/` `archives/`）へは張らない。他の PC でリンク切れになる。
- この PC のローカルの情報（業務固有のもの、個人的なもの）を、`resources/`（共有）に書かない。`resources/` の変更は、`resources/` の中でコミットする（このリポジトリのコミットには含まれない）。
- `git add -f` で、ignore 済みのファイルを追加しない。
- `.obsidian/` の実体は dotfiles（`windows\obsidian\.obsidian`）にある。変更のコミットは dotfiles で行う（接頭辞 `[obsidian]`）。Obsidian が起動中は、設定ファイル（`*.json`）を編集しない（Obsidian が上書きして、変更が消える）。プラグインやテーマを追加・削除するときは、設定ファイルと `community-plugins.json` を合わせる。`workspace.json` と `workspace-mobile.json` は端末ごとの状態なので、コミットしない（dotfiles の `.gitignore` 済み）。
- ユーザーへの質問（聞き取り）、AI の提案への承認の確認、改善フックの改善案は、`docs/metrics/events.csv` に1件1行で記録する（記録するのはエージェント。定義と列は `docs/metrics/README.md`、集計は `docs/metrics/summarize.ps1`）。回答を受けた同じターンで行を足し、`wrap`（終了処理）で `adopted` と `reversed` を確定する。要旨に、機密・個人情報を書かない。補正（`fix` `supplement` `gap`）の行には、起因 `cause`（`ai` `user` `review`）を付ける。
- 終了処理（「終了処理して」）の `docs/` 更新の中で、スレッド・セッションの指標を足す（試験運用。定義は `docs/metrics/README.md` の「スレッドとセッションの指標」。用途はユーザー本人の自己改善だけ）。手順: ① `pwsh -NoProfile -File docs/metrics/extract-threads.ps1` で `threads.csv` を更新 ② `-Current -Cwd <Claude を開いた作業ディレクトリ（シェルのカレントではない）>` で今のスレッド ID を取り、`sessions.csv` に1行足す（`outcome` `prompt_complete`、根拠 `prompt_evidence`、`review` `mechanism` `note` `start_mode`（`bare` か `briefed`。最初の依頼の形から判定する）。「並行の可能性」の警告が出たら、選んだ会話が今のものか（最初のプロンプトの内容や時刻）を確かめ、確かめられなければユーザーに聞く。根拠はユーザーの発言の要旨を残し、忖度しない。機密・個人情報を書かない） ③ `-Report` で無駄の合図を見て、報告に1〜2行書く。

- 「start」（別名「作業を始めて」）と言われたら、kit の `start-hook.md`（開始インタビュー。試験運用）に従う。進行中の Project が無い、または新しい Project を始めるときは、先に `open-hook.md` で Project を作る（`open` は `start` を呼ぶ）。Project を閉じる（`close`）ときは、`close-hook.md`。手順書の正本は kit（2026-10-08 に `docs/drafts/` から移した）。実務で出た漏れ・補正は、ここの `docs/metrics/events.csv` に記録し、承認されたら kit を直す。`docs/drafts/` の3つは、実測の経緯の記録として残す（PARA の試行の経緯は `docs/log.md`、判断は `docs/decisions.md`）。

## コミット

- メッセージは `[領域] 変更内容`。`git add` はパスを指定する。
