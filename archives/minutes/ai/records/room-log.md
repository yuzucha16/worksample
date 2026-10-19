# 部屋の記録（room-log）

`room start` / `room close` の実行ごとに追記する（`room.py` が書く）。

| 日時 | 操作 | Area | ディストロ | マウント点 | チェック | 結果 |
|---|---|---|---|---|---|---|
| 2026-10-19 21:29 | open | office | room-office | /mnt/room/minutes | area 一致、boundary あり | ひな形を作成 |
| 2026-10-19 21:35 | start | office | room-office | /mnt/room/minutes | area 一致、boundary=internal、in 0 件の来歴 OK、共有知の写し送付 | 終了コード 0、変更 2 件 |
| 2026-10-19 21:37 | close | office | room-office | /mnt/room/minutes | area 一致、案件 0 件 | archives へ移動、reap_after 2026-11-02 |
