# Project を閉じる（close）手順書の下書き

状態: **下書き**。最初の Project（`learn-c-pool-allocator`）を閉じるときの手順を、実測しながら起こす。実測で直し、安定したら kit への昇格を判断する（いまは PoC で、kit は変更しない）。判断基準は `docs/decisions.md`（「PARA の `areas/` `projects/` `archives/` の役割と判断基準を定める」の 4・6・7）。

## 閉じる契機

- 完了条件を達成した、中止を判断した、または見直し日を2回超えて更新が無いとき（基準6）。
- **完了条件を達成したら、見直し日を待たずに閉じる**（2026-10-06 ユーザーの指示。AI が「見直し日まで残す」と提案して、直された）。AI は、完了条件の達成を確認した時点で、close を提案する。

## 手順（順序を固定する）

1. **完了条件を確認する**: `README.md` の完了条件を、実測（コマンドと結果）で確かめる。未達なら、閉じずに、残りを Next Actions に書く。
2. **暫定の見直し**: Project で暫定にしていた決定（制約、数値、方式）を、実測で見直す。結果を `docs/decisions.md` に書き、変更するものはユーザーの承認を得る。
3. **未解決を整理する**: Next Actions と Open Questions の残りを、次の Project、親の Area（`areas/<名>/README.md`）、または破棄に振り分ける。持ち越すものは、移し先に書く。
4. **ナレッジ化の候補を示す**: `docs/decisions.md` の `未仕分け` のうち【汎用】の項目を一覧にして、ユーザーに示す。**「ナレッジ化して」は、ユーザーが言ったときだけ実行する**（自動で実行しない。`knowledge-hook.md`）。実行の有無と時期は、ユーザーが決める。
5. **状態を更新する**: `README.md` の frontmatter を `status: done`（中止は `cancelled`）、`closed: <日付>` にする。完了条件の結果（実測の数字）と、成果物の場所を、`README.md` に1段落で足す。
6. **`archives/` へ移す**: `projects/<名>/` を `archives/<名>/` に `git mv` する。親の Area の一覧（`areas/<名>/README.md`）を、「完了した Project」に移し、リンクを新しいパスにする。ほかの参照（`docs/log.md`、`docs/decisions.md`、`docs/metrics/events.csv` の `project` 列など）は、パスでなく名前なので、変更は不要か、`grep` で確認する。
7. **指標を確定する**: この Project の `events.csv` の行の `adopted` と `reversed` を確定する。`summarize.ps1` の Project の単位で集計して、`docs/log.md` に結果を書く。
8. **記録してコミットする**: `docs/log.md` に、閉じたことと結果を書く（日報の入力になる形）。パスを指定して `git add` し、コミットする（push はユーザー）。

## 初回の実測で確認すること

- 手順 6 で、`git mv` の後に Obsidian のリンク（`[[projects/…]]`）が切れないか。
- 手順 4 で、候補の一覧が、ユーザーにとって判断しやすい長さか（`未仕分け` の件数が多いときの扱い）。
- 手順 7 で、`reversed` を確定する根拠（確認期間）をどう決めるか。
