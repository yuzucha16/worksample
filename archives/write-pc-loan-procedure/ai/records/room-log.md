# 部屋の記録（room-log）

`room start` / `room close` の実行ごとに追記する。手作業の試行（`room.py` 未実装）の記録を含む。

| 日時 | 操作 | Area | ディストロ | マウント点 | チェック | 結果 |
|---|---|---|---|---|---|---|
| 2026-10-12 | 手作業 start（1巡目） | office-admin | room-office-admin | /mnt/room/write-pc-loan-procedure | `area` 一致、`ai/in/` は空 | AI が `out/review-notes.md` を作成。`out/pc-loan-procedure.html` は無変更 |
| 2026-10-12 | 手作業 close（2巡目） | office-admin | room-office-admin | /mnt/room/write-pc-loan-procedure | `area` 一致、`boundary: internal`、`ai/in/` は空、README の写しを `ctx/` に置いた | AI が `out/close.md` を作成し `docs/log.md` を更新。指示は `session-close-prompt.md`。Area の `inbox.md` へ【案件】6件を転記し、`archives/` へ移動 |

- zombie: 部屋の会話履歴 `~/.claude/projects/-mnt-room-write-pc-loan-procedure/`（`room-office-admin`）。`reap_after` は README の frontmatter（既定14日）。
