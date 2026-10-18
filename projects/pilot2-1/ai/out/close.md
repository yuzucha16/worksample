# close: pilot2-1（開通テスト）

開通テストは問題なし。WSL 上の隔離領域で動いていて、Windows からのリモート接続経由で指示を受け取れている。

- **作業環境**: `/home/ai`（Linux 6.18 WSL2、bash）。git リポジトリではない。部屋の実体は `/mnt/room/pilot2-1`。
- **共有知**: `~/shared/ROOM.md` を読んだ。`~/shared` は 2026-10-18 21:39 に送られた読み取り専用の写しで、セッション中は更新されず、書き込めない。基準コミットは `d75c013afcdacf1560de9072efce7bc7cc85ca25`。
- **規約**: `~/shared/AGENTS.md` も読み込まれた。合言葉（`start`、`wrap` など）は `~/shared/workflow-kit/hooks.md` の表に従って処理する。
- **未認証のコネクタ**: Google Drive コネクタは未認証なので、今は使えない。使う場合は claude.ai のコネクタ設定で認証が要る。

## 完了条件

`ai/ctx/README.md` の完了条件は未記入（ひな形のまま）。開通テストの確認だけで、完了条件の実測はしていない。

## 未解決の振り分け

- 【案件】`ai/ctx/README.md` の目的・完了条件・成果物・範囲外がひな形のまま。Area 側で扱うか、破棄するかを決める。
