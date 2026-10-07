# AGENTS.md

個人用 PC の作業場。PARA でこの PC のローカルの作業（個人開発など）を管理し、共有ナレッジ（`resources/`）を参照する。

Obsidian の Vault のトップ。この PC だけのローカルなリポジトリ（remote: 非公開リポジトリ `https://github.com/yuzucha16/worksample`）。共有ナレッジは `resources/`（別リポジトリ `workbase` の clone）にあり、Vault 全体の規約は `resources/AGENTS.md`。

## 共通ルール

共通ルールの置き場は `$HOME\works\resources\workflow-kit`（WSL: `/mnt/c/Users/<Windows のユーザー名>/works/resources/workflow-kit`）。ユーザーが合言葉（手順書を呼ぶ短い言葉。日本語の別名つき）を言ったら、そこの `hooks.md` の表に従って手順書を読み、実行する（言われたときだけ）。`docs-rules.md` は、作業を始める前と、`docs/` を更新するときに読む。

読めない場合（`resources/` を clone していない PC など）は、記憶で代用せず、ユーザーに伝えて止まる。

## 読む順番

1. `docs/log.md`（現在状態だけ。4KB 目安）
2. `resources/AGENTS.md`（Vault 全体の規約）

`docs/decisions.md` と `docs/log-history.md` は開始時に読まない。何かを決める・変える前に、`decisions.md` を検索して、既存の決定と矛盾しないか確かめる。kit の手順が「`log.md` の Log に書く」と言うときは、`docs/log-history.md` の `## Log` の先頭に追記する（2026-10-08〜。試験運用。1週間後に kit の `docs-rules.md` へ昇格するか判断）。

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
- ユーザーへの質問（聞き取り）、AI の提案への承認の確認、改善フックの改善案は、`docs/metrics/events.csv` に1件1行で記録する（記録するのはエージェント。定義と列は `docs/metrics/README.md`、集計は `docs/metrics/summarize.ps1`）。回答を受けた同じターンで行を足し、`wrap`（終了処理）で `reversed` を確定する（採用率は集計しない。2026-10-08 廃止）。要旨に、機密・個人情報を書かない。補正（`fix` `supplement` `gap`）の行には、起因 `cause`（`ai` `user` `review`）を付ける。
- ユーザーが `again`（または「前にも言った」）と書いたら、同じターンで `events.csv` に `kind=again` の行を足す（`question` に再度言ったことの要旨。`answerable` は、その情報が既に知識・`AGENTS.md`・`docs/` にあったら 1、無かったら 0）。そのうえで、前提を `AGENTS.md` か知識（`stock`）に昇格する案を出す（承認制）。`wrap` では、「今日の遠回りは、なし・少し・大きく のどれか」を1問だけ聞き、`sessions.csv` の `detour` に書く。
- 終了処理（「終了処理して」）の `docs/` 更新の中で、スレッド・セッションの指標を足す（試験運用。定義は `docs/metrics/README.md` の「スレッドとセッションの指標」。用途はユーザー本人の自己改善だけ）。手順: ① `pwsh -NoProfile -File docs/metrics/extract-threads.ps1` で `threads.csv` を更新 ② `-Current -Cwd <Claude を開いた作業ディレクトリ（シェルのカレントではない）>` で今のスレッド ID を取り、`sessions.csv` に1行足す（`outcome` `prompt_complete`、根拠 `prompt_evidence`、`review` `mechanism` `note` `start_mode`（`bare` か `briefed`。最初の依頼の形から判定する）、`knowledge_used`（このセッションで読んだ exmem の知識のうち、判断・成果物に反映した件数）、`knowledge_miss`（探した・読んだが、無い・古い・ずれていた件数。1件ごとに `gap` の行にもする。定義は `docs/metrics/README.md` の「再利用率の指標」）。「並行の可能性」の警告が出たら、選んだ会話が今のものか（最初のプロンプトの内容や時刻）を確かめ、確かめられなければユーザーに聞く。根拠はユーザーの発言の要旨を残し、忖度しない。機密・個人情報を書かない） ③ `-Report` で無駄の合図を見て、報告に1〜2行書く。

- `start` `open` `close`（試験運用）: 進行中の Project が無い、または新しい Project を始めるときは、先に `open` で Project を作る。実務で出た漏れ・補正は、ここの `docs/metrics/events.csv` に記録し、承認されたら kit を直す。`docs/drafts/` の3つ（project-open / project-close / session-start-interview）は、実測の経緯の記録として残す（PARA の試行の経緯は `docs/log-history.md`、判断は `docs/decisions.md`）。
- `review`（試験運用）: 週1回を目途。`wrap` の報告が、前回から7日以上たっていれば勧める。記録は `docs/metrics/reviews.csv` と `docs/metrics/rule-hits.csv`。
- `wrap` の改善案は、線引きで扱う（2026-10-08 ユーザーの決定。試験運用。正本は kit の `wrap-hook.md` の「自動採用の範囲」）。運用の補助は、承認なしに追加・削除してコミットする（`review` が要・不要を判断する）。安全規則（push・機密・破壊的操作・身元・決定の原則・書き込み先・承認の規則）と手順の本体は、承認制のまま。

## 規模の凍結（2026-10-08〜判定日 2026-11-08。ユーザーの決定。試験運用）

手順書・指標・規則を足すときは、同時に1つ畳む。この指示（`AGENTS.md`）に、指標の数値目標を書かない（指標はユーザーの見直し専用）。根拠と判定の基準は `docs/decisions.md`。

## push の許可リスト（2026-10-08 ユーザーの決定。試験運用）

エージェントが push してよいのは、次のリポジトリの `main` だけ。条件（公開範囲の確認、fast-forward、機密の検索）は、kit の `docs-rules.md` の「push」。

| リポジトリ | ブランチ | 備考 |
|---|---|---|
| `works`（remote: `yuzucha16/worksample`。非公開） | `main` | このリポジトリ |

`resources/`（`workbase`）、dotfiles、ほかのリポジトリは対象外（公開範囲が決まってから、ユーザーが広げる）。`workbase` を push するときは、ユーザーが行う。

## コミット

- メッセージは `[領域] 変更内容`。`git add` はパスを指定する。
