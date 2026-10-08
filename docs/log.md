# 作業ログ（log）

`works`（Vault のトップ。PC ローカルのリポジトリ）の現在状態と次にやること。**開始時に読むのはこのファイルだけ**（上書きで更新する。4KB 目安）。経緯と、過去の Next Actions の全文は `docs/log-history.md`（開始時に読まない。必要なとき検索する）。判断の根拠は `docs/decisions.md`（何かを決める前に検索する）。

## Next Actions（2026-10-08 時点）

1. **目的の置き直しと規模の凍結（判定日 2026-11-08）**: 週1・15分の `review`（見るのは `again` と `gap` の事例、`extract-threads.ps1 -Report` の常時読み込みの字数）。
1b. **2026-10-15 頃の点検（担当: エージェント。ユーザーは `again` の場面と体感を伝える）**: ① 読み落とし: 会話履歴から、コミットの前に `git diff --cached` を実行したか、`docs-rules.md` を読んだか、`decisions.md` に提案が決定として混ざっていないか、決める前に `decisions.md` を検索したかを調べる（その場限りのスクリプト。恒久の列は足さない）。② ログ分割と `docs-rules.md` の開始時読み込み廃止で手戻りが出たか。問題が無ければ kit に昇格する。③ CRLF の混入元（`events.csv` と `review-hook.md` で Git が警告）を調べて直す。
2. **構造の見直し（L1 の推奨案 F。`docs/drafts/review-l1-structure-result.md`）**: 済み（2026-10-08）: ステップ0（タグ）、1（旧 clone を `C:\Users\ck\_archive` へ退避）、2（このログの分割。1週間試し、手戻りが増えたら戻す）、3（呼び出し表を `hooks.md` の1か所に。旧名ファイルの削除）、5（作業側 AGENTS の縮小）、6（`hooks.md` に契約）、7（版番号と README の変更履歴を廃止。README 24.8k→4.6k 字、改善記録 42KB→2.9k 字。タグ `kit-history-20261008`）、8（`exmem/AGENTS.md` の縮小と知識の索引）、9（`contexts/` に業務の文脈を書かない方針）、`contexts/` の2件の削除。常時読み込みは 79,804 → 6,198 字。次: 8の残り（`転記待ち` の簡素化。台帳の試験判断 10-22 の後）、4（手順書の場所を PC ごとの指示に1か所化。Codex が読むので作業側 AGENTS に1行のフォールバックを残す。不確実性が高いので最後）、10（周辺物）。手順書本体（`stock-hook.md` 27KB など）をさらに薄くするのは、ステップ7の続き（`README.md` と `improvements.md` 以外）。各ステップは単独で戻せる。
3. **権限移譲の試験運用（2026-10-22 に継続・修正・撤回を判断）**: `review` を3〜4日おきに。台帳は拡張しない。`summarize.ps1` で自動採用の行を分ける。台帳に記録が無い旧い統合は、従来の方式で確定する。
4. **PARA の試行**: 3回目の Project（候補は `areas/learning/README.md`）。kit への昇格は安定してから。
5. **保留**: 旧 `C:\vault` と GitHub の旧 `notes` の削除、`claude --resume` の確認、WSL の `WORKS_DIR` の実機確認（詳細は `log-history.md` の Next Actions）。

## Open Questions

- `workbase` の公開: 予定はあるが未決定。公開されうる前提で書く（ユーザー、2026-10-08）。非公開の remote は GitHub（またはリモート無しのローカル git）。
- このログの分割と、`docs-rules.md` を開始時に読まない運用で、手戻りが出ないか。1週間後（約 2026-10-15）に確認し、問題なければ kit の `docs-rules.md` とひな形に昇格する。
