# リポジトリ間の整合の基準（alignment-baseline）

works、resources（workbase）、dotfiles の運用を揃えるための基準。`review` の入力 8（kit の `review-hook.md`）が、各行を今の状態と比べ、違う行だけを見直しとして挙げる。見直しの後は、この表を更新し、基準日を直す。

基準日: 2026-10-16

## 現状

| 項目 | works | resources | dotfiles |
|---|---|---|---|
| `CLAUDE.md` が `@AGENTS.md` の1行 | ○ | ○ | ○ |
| 共通ルールのポインタ | ○ | ○ | ○ |
| 窓口 `README.md` | ○ | ○ | ○（16KB 目安） |
| 直下の `docs/log.md` | ○ | ○ | ○ |
| 読む順番 | 3段（README、log、検索のみ） | 同左 | 同左 |
| 「〜の続き」の扱い | kit の `docs-rules.md` を参照する1行 | 同左 | 同左 |
| 期日の確認の規則 | ○（`log.md` に期日の節あり） | ○（節あり。2026-10-16） | ○（節あり。2026-10-16） |
| 下位の単位 | `projects/` `areas/` `archives/` | `exmem/` `workflow-kit/` `guides/` `topics/`（各 `README.md` `AGENTS.md` `CLAUDE.md`(`@AGENTS.md`)。索引は `guides-index.md` `topics-index.md`。`exmem/` は README が索引を兼ねる） | なし |
| `.claude/` | `settings.json`（deny）を追跡 | `settings.local.json` だけ追跡しない | 同左 |
| `settings.local.json` を追跡しない | ○ | ○ | ○ |
| 公開範囲 | PUBLIC（2026-10-16 にユーザーが変更） | PUBLIC | PUBLIC |
| push の許可リスト | `main` を許可 | `main` を許可 | `main` を許可 |
| `main` と `origin/main` | 同じ | 同じ | 同じ |

## 点検の対象

`review` の入力 3（`exmem/inbox/` の未統合メモ、`decisions.md` の `→` の無い【汎用】項目）、入力 4（トピックの点検）、入力 6（機密の点検）が、works から起動しても見るリポジトリ（2026-10-16 ユーザーの決定）。`git -C <パス>` で検索する。

| リポジトリ | パス | 公開範囲 |
|---|---|---|
| works | `.` | PUBLIC |
| resources（workbase） | `resources` | PUBLIC |
| dotfiles | `repos/github.com/yuzucha16/dotfiles` | PUBLIC |

## ギャップ

| # | 内容 | 状態 | 影響 | リスク |
|---|---|---|---|---|
| 1 | resources に `docs/log.md` がない | 解消 | 中 | 低 |
| 2 | 読む順番の形が3通り | 解消 | 高 | 低 |
| 3 | 「〜の続き」の規則が `topics/AGENTS.md` にしかない | 解消（kit に1か所） | 高 | 低 |
| 4 | `guides` と `handson` が `CLAUDE.md` だけ | 解消（2026-10-16。`handson` は削除済み。`guides` は `AGENTS.md` に改名し、`README.md` を足した。`topics` に `README.md`、`workflow-kit` に `CLAUDE.md` を足した。resources `b6a9505`） | 低 | 低 |
| 5 | 期日の節が works にしかない | 解消（2026-10-16。resources と dotfiles に節を足し、定例の書式を kit の `docs-rules.md` に入れた） | 低 | 低 |
| 6 | `.claude/` の扱いの違い、works に deny がない | 解消。deny の実機確認は済み（`Read` は拒否、PowerShell の `Get-Content` は通る） | 中 | 中 |
| 7 | works の `AGENTS.md` と雛形のずれ | 解消 | 低 | 低 |
| 8 | 公開リポジトリの git 履歴にユーザー名を含むパスが残っている | 未着手（書き換えは force push が要り、禁止） | 中 | 高 |

正は kit（`workflow-kit`）。
