# 判断の記録（decisions）

なぜそうしたか（Why）、却下案、遭遇した詰まり、実機で確認した事実を残す。現在の状態と次にやることは `docs/log.md`。

`.obsidian/` に関する 2026-10-04 以前の項目は、git 履歴と、`exmem/knowledge/` の記述から復元したもの。根拠と却下案が履歴に残っていないものは、Facts に事実として書く（判断の理由は推測で補わない）。

## Principles

- 【汎用】作業ログは `exmem` に置かず、作業ディレクトリ側の `docs/` に置く。 行き先: 転記済（2026-10-06 → kit/docs-rules.md、exmem/workflow-kit.md）
- 【汎用】小さく一過性のディレクトリには、専用の `docs/` を置かない。親の作業ディレクトリの `docs/` に含める。 行き先: 転記済（2026-10-06 → kit/docs-rules.md。exmem 側にも済み）
- 【汎用】アプリが自動で書き換えるファイルを追跡するかは、次の5項目で決める。 行き先: 転記済（2026-10-06 → exmem/app-config-placement.md）
- 【この件】Obsidian の設定は、使っているものだけに絞る。 行き先: 転記済（2026-10-06 → exmem/obsidian-vault.md）
- 【汎用】記録する決定は、ユーザーが明示したものだけにする。AI の提案は「提案」と書き、承認の確認が取れるまで決定として書かない。 行き先: 転記済（2026-10-06 → kit/docs-rules.md。exmem 側にも済み）

## Decisions

### 【この件】L1 の推奨案 F を採る: リポジトリは 2 つのまま、作業ログの分割、呼び出し表の 1 か所化、共有側の依存の逆転（2026-10-08。ユーザーが承認。試験運用）

- 背景: L1 の第三者レビュー（`docs/drafts/review-l1-structure-result.md`。判定は「条件つきではい」）。常時読み込みの大半は、作業ログと判断記録を毎回読む設計から来ていた。呼び出し表の写しが 5 か所にあり、2 か所が旧名のままだった。共有側（公開されうる）の手順書が作業側の構造を前提にしていた。
- 決めたこと: ① 案 F（手順書を薄く + 1 ファイル + 1 語 + 境界の修正 + ログ分割）を採る。リポジトリは `works`（非公開）と `workbase`（公開されうる）の 2 つのまま。案 B（手順書を独立）と案 D（版つきの写し）は採らない。② 台帳は、2026-10-22 の試験判断まで拡張だけ止める（レビューは凍結を勧めたが、試験期間中のため）。③ `contexts/` は、業務の文脈を共有側に置かない（公開されうる前提で書く。公開の予定はあるが未決定。ユーザーの回答）。`ai-business-adoption` と `office-deliverable-workflow` を削除した（固有名詞・機微情報は無かったが、念のため。ユーザーの指示）。④ 非公開の remote は GitHub、またはリモートの無いローカル git。GitHub ならクラウドのセッションから clone してよい（ユーザーの回答）。
- 実施（2026-10-08）: ステップ 0（`pre-l1-20261008` のタグを 3 リポジトリに）、1（旧 `notes` の clone を `C:\Users\ck\_archive\notes-old-clone-20261008` へ。未追跡のメモは統合済みを確認）、`contexts/` の 2 件の削除、2（`docs/log.md` を現在状態に、経緯を `docs/log-history.md` に。`decisions.md` は開始時に読まず、決める前に検索する）、3（`workflow-kit/hooks.md` を正本にし、各 AGENTS・ひな形・見本・README の写しを 1 行のポインタに。旧名の案内ファイル 3 つを削除）、5（作業側 AGENTS を 4,418 → 2,950 字に。安全規則を先頭にまとめ、記録手順を `docs/metrics/README.md` に移し、`docs-rules.md` は開始時でなく `docs/` 更新・コミット・push の前に読む）、6（`hooks.md` に作業ディレクトリへの「契約」を追加。手順書 6 本から作業側のファイル名を抜き、記録名 `events` `sessions` `reviews` `rule-hits` に置き換え。保存先は作業側の AGENTS が定める）。この時点の常時読み込みは 5,703 字（79,804 字から約 93% 減）。続いて 7（版番号と README の変更履歴を廃止。タグ `kit-history-20261008` に全文が残る。`kit:` フィールドと `Workflow-Kit:` トレーラーも廃止。規則の時点は `Kit-Rev`）、9（`exmem/AGENTS.md` に、`contexts/` に業務の文脈を書かない方針）。常時読み込みは 6,198 字。
- 効果（`extract-threads.ps1 -Report` の常時読み込み）: 79,804 字 → 16,967 字（約 79% 減。`log.md` 1,221 字、`decisions.md` を除外）。目安の 1 万字以下までは、`docs-rules.md`（8,838 字）と作業側 AGENTS（約 5,000 字）の縮小が残る。
- 実測の補足（第三者レビューの確認事項への回答）: 実際の `log.md` の最初の Read は、直近の `works` のスレッドで 2.0〜3.4 万字（ファイルの約半分。長い行の打ち切りが疑わしいが原因は未確認）。Codex は使われている（セッション 31 件）ので、作業側 AGENTS だけで最低限動くことを保つ。
- 未決: ステップ 4〜10（手順書の場所の 1 か所化 + フォールバック、作業側 AGENTS の縮小と運用規則の分解、契約、手順書を薄く、知識側、`contexts/` の方針、周辺物）。ログ分割を kit の `docs-rules.md` と `templates/AGENTS.md` の「読む順番」に昇格するか（1 週間試して手戻りが無ければ）。合言葉の統合は L3、検査スクリプトは L5。
- 却下案: リポジトリの切り直し（案 B・D）、判断記録の YAML/CSV 化（構造化より簡素化）。
- 行き先: local

### 【この件】目的の頂点を「ユーザーの負担を減らす」に置き直し、追加は `again` と `wrap` の1問だけ、規模を凍結する（2026-10-08。ユーザーが承認。試験運用）

- 背景: L0 の第三者レビュー（`docs/drafts/review-l0-purpose-result.md`。判定は「条件つきではい」）。主目的が「生産性向上」だと、ユーザーの言葉（言わない・聞かれない・最短）とずれる。本命の「言わない」を直接測る指標が無く、効果の証拠（参照率 24%、読まれた知識 42 件中 5 件、`review` 0 件）がコストに見合っていない。
- 決めたこと: ① 主目的は「ユーザーの負担（再伝達・不要な往復・手戻り）を減らす」。目標は、言わない・聞かれない・最短。再利用率・参照率は診断用の補助で、目標値を置かず、AI に目標として示さない。② 指標の追加は 2 つだけ: `kind=again`（ユーザーが `again` と書く。`answerable` で「情報が既にあったか」の 1 ビット。機械検出 `again_hint` は目安）と、`wrap` の 1 問 `detour`（なし・少し・大きく）。③ 採用率は集計をやめる。④ 規模を凍結する（手順書・指標・規則は、1 つ足すなら 1 つ畳む）。`AGENTS.md` に数値目標を書かない。⑤ 週 1・15 分の `review`。判定日は 2026-11-08。
- 常時読み込みのベースライン（2026-10-08、字数）: 合計 79,804（`AGENTS.md` 4,765、`resources/AGENTS.md` 1,912、`docs/log.md` 50,720、`docs/decisions.md` 13,569、`docs-rules.md` 8,838）。`extract-threads.ps1 -Report` で再計測する。支配項は `log.md`。
- 判定（2026-11-08）の成功の基準: `again` が記録されている。同種の `again` の再発が月 1 件以下。`review` が 4 回行われ、1 回以上は畳む・直す判断に使われた。常時読み込みの字数と手順書の数が増えていない。
- やめる基準: 1 か月、どの判断にも使われなかった指標は記録をやめる。3 か月読まれなかった知識はアーカイブへ、手順書は統合・廃止を検討する。`again` の記録が定着しなければ、計測による自己改善（経路 2）を畳み、`AGENTS.md` への追記だけを残す。基盤整備の自己判定が 2 週連続で「元が取れていない」なら、拡張を止める。
- 受け入れなかった点: 参照率の収集は止めない（自動で追加コストがほぼ無い）。目標値を置かず、四半期の棚卸しだけに使う。
- 未決: kit の `start-hook.md` `close-hook.md` に、`adopted` の確定の記述が残っている（採用率の廃止に合わせて直す。凍結の方針どおり、1 つ畳む対と合わせて行う）。`log.md` の退避（常時読み込みの縮小）。L1 以降（リポジトリ構成）のレビュー。レビューの案 1（1 ファイル + 1 語方式）を、L1 の構造の比較に入れる。
- 却下案: 指標の記録を全部止めて月 1 の棚卸しだけにする（レビューの案 2）。母数が小さい今は有力だが、`again` の記録を 1 か月試してから判断する。
- 行き先: local

### 【この件】再利用率を直接測る指標を足す: 参照率・未参照の知識・手順書の参照・活用率・空振り（2026-10-08。ユーザーの指示。試験運用）

- 決めたこと: `threads.csv` に `know_reads` `know_searches` `know_files` `kit_files` を足し（会話履歴の `Read` と検索から自動）、`sessions.csv` に `knowledge_used` `knowledge_miss` を足す（`wrap` で AI が数える）。定義は `docs/metrics/README.md` の「再利用率の指標」。`extract-threads.ps1 -Report` が出す。
- 根拠: 目的は「同じことを何度も言わない・聞かれない・最短で目的地に近づく」。適合率・冗長率は質問・提案の質の指標で、知識が再利用されたかは測っていなかった。肥大化の原因は、効果を測らずに量が増えたことだと見る（ユーザー）。
- 初回の実測（2026-10-06 以降、業務側スレッド 17 件）: 参照率 4/17（24%）。`knowledge/` 42 件のうち、読まれたのは 5 件。空振りの合図 7 件。kit で読まれていない手順書は `init-hook.md` だけ。下限値（`Read` と検索の呼び出しだけ数える）。
- 未決: 下限値と実際の使用の突き合わせ（精度）。維持コストとの比の取り方。
- 行き先: local

### 【汎用】Project の構造は、固定の核（README・docs・直下の最終成果物）に、type（doc / dev / research）別の追加を足す（2026-10-08。ユーザーが承認。試験運用）

- 決めたこと: type は成果物の種類で決める（Area は既定値のヒント）。`doc` は `drafts/` と `refs/`、`dev` は `src/` `tests/` `tools/`、`research` は `sources/` と `report.md`。`docs/` は作業の記録（log・decisions）だけにして、下書きは `drafts/` に分ける。深さは直下から2階層まで。空のディレクトリは先に作らない。正本は kit の `open-hook.md`「Project の構造」。ひな形は `templates/project/README.template.md`。
- 根拠: 浅くてフラットな構造にしたい（ユーザーの希望）。`write-pc-loan-procedure` は下書きが `docs/` に入って、log と混ざっていた。`dev` は `learn-c-pool-allocator` の実績どおり。
- 未決: `research` と、混合の Project の扱いは、実測が無い。既存の `write-pc-loan-procedure`（下書きが `docs/`）は、移行せず、閉じるときに扱う。
- 行き先: 転記済（2026-10-08 → kit/open-hook.md「Project の構造」）

### 【汎用】フックの権限を、一律でなく線引きで移譲する: wrap の改善案の自動採用、push の許可リスト、転記の台帳と review フック（2026-10-08。ユーザーの決定。試験運用）

- 背景（データ。2026-10-08、`summarize.ps1`）: 改善案の承認は 89 件中 88 件が採用で、`fix` と補足は 0。ゲートとしての情報量がほぼ無い。一方、一般の承認確認は 55 件中、修正 7・補足 21 で機能している。
- 決めたこと: ① `wrap` の改善案は、運用の補助だけ「自動採用の規則」の節に、承認なしで追加・削除してコミットする（ID 付き。1改善 = 1コミット）。安全規則（push・機密・破壊的操作・身元・決定の原則・書き込み先・承認の規則）と手順の本体、ほかのフックの改善案は、承認制のまま。② push は許可リスト（当面 `works` の `main` だけ）で、エージェントが行う。毎回、公開範囲（非公開）・fast-forward・機密の検索を確認し、満たさなければ止まる。`workbase` と dotfiles は、公開範囲が決まってから、ユーザーが広げる。③ 転記は、`integrate` が台帳（`exmem/integrated.md`）に追記し、`review` が台帳を読んで `転記待ち` を `転記済（…。本文残し）` に一括で進め、次の回で本文を外す（2段階）。台帳に無い、日付が合わない、統合先に見出しが無い項目は、ユーザーに聞く（**この方式は、下の追加の決定（第三者レビューの反映）で置き換えた**）。④ 見直しのフックは `review`（別名「見直して」。週1回を目途）。チェック機能は、今後ここに集約していく。
- 根拠: ① 承認が素通りで、ゲートとして働いていない（上のデータ）。ただし、安全に関わる規則は、素通りでも事故の被害が大きいので、承認を残す。② コンフリクトの機会が少ない（ユーザー一人の利用）。公開リポジトリへの push は、後から消せないので、非公開の確認を毎回入れる。③ 手間の本体は、突き合わせと承認で、マークを付ける作業ではない。2026-10-06 の突き合わせでは、`works` の 5 件すべてに転記先の欠落・誤りがあったので、メモの消滅だけで `転記済` にしない。
- 見直し（`review`）の指標: 削除率を、再発率（削除後に同種の `gap` が出た割合）と規則の総量と組で見る（削除率の単独目標化を避ける）。保険の規則は、頻度では削除しない。
- 却下案: 全フックの一律の承認廃止（影響分析の結果、安全規則と手順の本体を分けた）。簡易案（`integrate` の後に承認を事後報告にするだけ。台帳なしで、メモの消滅だけを根拠にする。時系列整合が崩れるため）。
- 追加の決定（2026-10-08。ユーザー）: 試験期間は2週間（2026-10-08 〜 2026-10-22。期間末に、継続・修正・撤回を判断する）。`workbase` と dotfiles は、push の許可の対象外のまま。第三者の意見は、別モデルに依頼する（依頼文: `docs/drafts/review-ledger-third-party-prompt.md`。回答の採否は、ユーザーが決める）。
- 追加の決定（2026-10-08。ユーザー）: `wrap` の棚卸し（`check-docs.ps1` など）を `review` へ移すかは、`review` を数回試してから判断する。それまでは `wrap` に残す。
- 追加の決定（2026-10-08。ユーザーが承認。第三者レビュー: 別モデル。`docs/drafts/review-ledger-third-party-answer-opus5-5.md`。判定は「条件つきではい」）: ③の台帳方式を次のように直した（kit 版 `2026-10-08.4`）。(a) 照合を、`integrate` の時点（メモが手元にある）に移した。メモに無い記述と、メモから落ちた記述の一覧を、ユーザーが1メモにつき1回承認してから、台帳に追記する（統合・台帳・メモの削除は1コミット）。(b) 日付比較をやめ、`転記待ち` の行に本文ハッシュ（`tools/item-hash.ps1`）を記録し、`review` が一致を確認する。不一致は `未仕分け（前回の転記: …）` に戻して、訂正メモの候補にする。(c) 本文外しの2段階を廃止した。(d) 台帳に種別（統合・取消・訂正）と照合の列を足し、有効な行は日付が最新のものとし、`merge=union` を指定した。(e) 台帳に載ったメモ名は再利用しない。14日を超えた `転記待ち` を `review` が報告する。(f) 試験期間（〜2026-10-22）中は、`review` を3〜4日おきに実行する。根拠: レビューの重大度「高」4件（日付比較は機能しない、メモ名の再利用、本文外し前の照合が承認なしの AI 判断になる、統合先の見出しの一致は内容を保証しない）は、影響分析が見逃した点。却下案: 本文を外さない運用（レビューの案2。正本が2つになる）。ID の新設（メモ名の再利用の禁止で足りる軽量版にした）。未確認: ハッシュが、軽微な編集（整形、追記）でも不一致になりすぎないか（試験で測る）。
- 実装済み（2026-10-08）: kit 版 `2026-10-08.3`（`resources/` のコミット `6307c31`）。`works` の `AGENTS.md`（許可リスト、`review` の呼び出し）、`docs/metrics/reviews.csv` `rule-hits.csv`。
- 行き先: 転記待ち（→ exmem/inbox/2026-10-08-hook-authority-delegation-ledger.md、本文ハッシュ f0556ecb）

### 【汎用】フックを寿命の階層ごとに開始と終了の対にし、英語の短い名前にする: init / open・close / start・wrap / stock / integrate（2026-10-08。ユーザーの決定）

- 体系: ワークスペースは `init`（導入。終了なし）。Project は `open`（ひな形の `README` `AGENTS` を作る）と `close`（`archives/` へ移す）。セッションは `start`（開始インタビュー。旧「作業を始めて」）と `wrap`（旧「終了処理して」）。随時は `stock`（旧「ナレッジ化して」）と `integrate`（旧「inboxを整理して」）。連鎖: `init`、`open → [start → 作業 → wrap]×N → close`。
- 定義（既存のナレッジと同じ）: スレッド = Claude Code の1会話。セッション = `start` から `wrap` までの作業手順の単位。スレッドはフックの対象にしない。`open` と `close` は Project の寿命であり、スレッドの開始・終了ではない（ユーザーの当初の案は「スレッドの open / close」だったが、既存の定義との照合で Project の寿命に直した）。
- `open` は、ひな形を作ったあとに `start` を呼ぶ。`start` は単独でも呼べる（進行中の Project があるとき）。
- セッションの終了は `end` でなく `wrap` にする。理由（ユーザー）: `end` は紛らわしい。
- 日本語のトリガーは、覚える負担が大きいので、主な呼び出しにしない。残す場合は別名（エイリアス）として。
- 却下案: `end`（紛らわしい。ユーザー）。ほかは未検討。
- 実装済み（2026-10-08）: kit 版 `2026-10-08.1`（コミット `ac7d574`）。旧ファイル名は案内だけを残し、削除は名前が定着してから一斉に行う（ユーザーの決定）。日本語の別名は、いま決まっている言葉だけ残す（ユーザーの決定。後で揃える）。
- 未決: 別名の範囲、旧名を削除する時期、`init` に終了のフックが要るか。
- 行き先: 転記待ち（→ exmem/inbox/2026-10-08-workflow-hook-naming-lifecycle.md）

### 【汎用】Vault のトップを `C:\vault\works` から `$HOME\works` に移し、ghq の root を `$HOME\works\repos` にする。Linux 側（WSL・ネイティブ）も `~/works`、`~/works/repos` にそろえる（2026-10-06。ユーザーの決定と指示）

- 固有（この PC の確認）: 新しい場所で Obsidian と Claude Code が動いた（2026-10-06）。WSL への `WORKS_DIR` の受け渡し（`WSLENV`）は、実機で渡っていなかった（2026-10-06、エージェント経由の確認。原因は未特定。この PC の WSL は未移行）。
- 行き先: 転記済（2026-10-06 → exmem/knowledge/obsidian-vault.md の「置き場を `$HOME\works` へ移す」。根拠と却下案「未検討」を突き合わせ済み。実機の WSL の確認結果は固有なので残す）

### 【汎用】PARA の `areas/` `projects/` `archives/` の役割と判断基準を定める（2026-10-06。ユーザーが承認。試行で見直す前提）

- 行き先: 転記済（2026-10-06 → exmem/knowledge/para-operations.md）

### 【汎用】PARA のディレクトリ構造は B1（フラット）にし、フックは開始と終了を先に作る（2026-10-06。ユーザーが承認）

- 行き先: 転記済（2026-10-06 → exmem/knowledge/para-operations.md）

### 【汎用】フックを「Project の寿命」と「セッションの寿命」の2層で連鎖させ、開始インタビューは育成・改善方式で作る（2026-10-06。ユーザーが承認）

- 行き先: 転記済（2026-10-06 → exmem/knowledge/para-operations.md）

### 【汎用】開始インタビューの指標を、1質問1行のイベントログで集める（2026-10-06。ユーザーの指示。形式と推奨指標は、同日にユーザーが承認）

- 固有: kit の `knowledge-hook.md` に節「改善案の指標の記録」を足した（版 `2026-10-06.19`。`docs/metrics/events.csv` があるときだけ記録する試験運用）。
- 行き先: 転記済（2026-10-06 → exmem/knowledge/para-operations.md。kit 固有の運用は kit に記載済みなので exmem には写していない）

### 【汎用】AI 活用と workflow の効果を、スレッド・セッションの指標で測る（2026-10-06。ユーザーが承認。試験運用）

- 固有: 当面は works の `AGENTS.md` の終了処理の手順として試験運用し、kit（`closing-hook.md`）への昇格は安定してから判断する。
- 行き先: 転記済（2026-10-06 → exmem/knowledge/ai-work-metrics.md。works の試験運用の状態は固有なので上の1行を残す）

### 【この件】PARA 試行の前提（2026-10-06。ユーザーの明示）

- PC1（会社 PC、remote なしのローカルリポジトリ）と PC2（個人 PC、非公開 remote `worksample`）は、別リポジトリ・別インスタンスで、同じ構造を使い回す。
- 管理の優先順位は、案件の業務、学習、個人開発の順。
- 最初の試行は PC2 の学習（C か C++。選択は最初の Project の Open Question）。PoC として改善プロセスを回し、kit を強化してから PC1 に投入する。
- `areas/dev-env` は廃止済み（CA 証明書は `$HOME\.certs` へ移行済み）。
- 行き先: local（この PC のトップの運用方針）

### 【この件】会社 CA 証明書の置き場を `areas/dev-env/certs/` から `$HOME/.certs` に移す（2026-10-06。上の `certs` の移動を置き換える）

- 確認済み（2026-10-06）: 旧 `areas/dev-env/certs` は空。
- 行き先: 転記済（2026-10-06 → exmem/knowledge/obsidian-vault.md）

### 【汎用】docs の項目に「行き先」を持たせ、滞留するデータを検出する（2026-10-06。試験運用）

- 行き先: 転記済（2026-10-06 → exmem/knowledge/workflow-kit.md、kit/docs-rules.md）

### 【この件】Vault のトップを `notes` から `works` に rename し、`certs` を `areas/dev-env/certs/` へ移す（2026-10-06）

- 行き先: 転記済（2026-10-06 → exmem/obsidian-vault.md）

### 【汎用】Vault のトップを PC ローカルのリポジトリにし、共有部分を `workbase` として入れ子で clone する（2026-10-05）

- 行き先: 転記済（2026-10-06 → exmem/obsidian-vault.md）

### 【汎用】「ナレッジ化して」の自己点検を、点検スクリプトで機械化し、編集済みの知識との重複を明記する（2026-10-05）

- 行き先: 転記済（2026-10-06 → kit/knowledge-hook.md、exmem/workflow-kit.md）

### 【汎用】「ナレッジ化して」で作った inbox のメモは、コミットしない（2026-10-05。全体に適用）

- 行き先: 転記済（2026-10-06 → kit/docs-rules.md、exmem/workflow-kit.md）

### 【汎用】「ナレッジ化して」の改善2点を採用する（2026-10-05）

- 行き先: 転記済（2026-10-06 → kit/knowledge-hook.md、exmem/workflow-kit.md）

### 【この件】Linux 側の試験スクリプトを dotfiles の `tests/` に置く（2026-10-05）

- 行き先: 転記済（2026-10-06 → dotfiles/docs/decisions.md）

### 【汎用】（撤回済み 2026-10-05）項目 5 の既定の対象を、Claude を開いたディレクトリ（cwd）にする

- 行き先: 転記済（2026-10-06 → kit/improvements.md、exmem/workflow-kit.md）

### 【汎用】「workflowを導入して」だけでワークスペースを生成する（2026-10-05）

- 行き先: 転記済（2026-10-06 → kit/setup-hook.md、exmem/workflow-kit.md）

### 【汎用】コミットの権限をエージェントに移す（2026-10-05。全体に適用）

- 行き先: 転記済（2026-10-06 → kit/docs-rules.md、exmem/workflow-kit.md）

### 【汎用】トップのワークスペースを kit の導入フックで生成する（2026-10-05）

- 行き先: 転記済（2026-10-06 → kit/setup-hook.md、exmem/workflow-kit.md）

### 【この件】`.obsidian` を dotfiles へ戻す（2026-10-05。2026-10-03 と 2026-10-04 の決定を撤回）

- 行き先: 転記済（2026-10-06 → exmem/app-config-placement.md）

### 【汎用】`notes/` を作業ディレクトリとし、`docs/` を `notes/docs/` に置く（2026-10-04）

- 行き先: 転記済（2026-10-06 → exmem/workflow-kit.md）

### 【汎用】`notes/docs/` はローカル専用のままにする（2026-10-04）

- 行き先: 転記済（2026-10-06 → exmem/workflow-kit.md）

### 【汎用】共通機能の導入手順を、「workflowを導入して」の導入フックにする（2026-10-04）

- 行き先: 転記済（2026-10-06 → kit/setup-hook.md、exmem/workflow-kit.md）

### 【汎用】`contexts/` を「`notes` から見えない場所の引継ぎコンテキスト」にする（2026-10-04）

- 行き先: 転記済（2026-10-06 → exmem/knowledge/workflow-kit.md、exmem/README.md、exmem/AGENTS.md）

### 【この件】`.obsidian/` を dotfiles から `notes` リポジトリへ移した（2026-10-03）

- 行き先: 転記済（2026-10-06 → exmem/obsidian-vault.md）

### 【汎用】改行コードを LF に統一する（2026-10-03）

- 行き先: 転記済（2026-10-06 → exmem/git-line-endings.md）

### 【この件】`colored-tags` の `data.json` は追跡する（2026-10-04）

- 行き先: 転記済（2026-10-06 → exmem/app-config-placement.md）

### 【この件】`types.json` で `created` と `updated` を日付型にする（2026-10-03）

- 決めたこと: `created` と `updated` のプロパティを `date` 型にする（`e81182c`）。
- 根拠: Bases での並べ替えや日付フィルタが正しく動く（`exmem/knowledge/obsidian-vault.md` の Proposals の記述）。
- 却下案: 履歴から不明。
- 行き先: local（Obsidian 固有の設定値）

### 【この件】ファイルアイコンは CSS のみで種類ごとに色分けする（2026-10-04）

- 行き先: 転記済（2026-10-06 → exmem/obsidian-appearance.md）

### 【この件】本文の幅をフォントサイズに比例させる（2026-10-04）

- 行き先: 転記済（2026-10-06 → exmem/obsidian-vault.md）

## Facts

- 【汎用】ripgrep（Claude Code の Grep を含む）は `.gitignore` を尊重する。 行き先: 転記済（2026-10-06 → exmem/modern-cli-tools.md、kit/templates/workspace/ignore.template）
- 【この件】`docs/` は、トップのリポジトリで追跡する（共有の `workbase` には載らない）。2026-10-04 の「`notes/docs/` はローカル専用のままにする」の趣旨（共有リポジトリに載せない）は保たれる。個人用 PC では、非公開 remote（`worksample`）へ push するかは、ユーザーが決める。 行き先: local（この PC のトップの運用）
- 【汎用】ジャンクション越しのディレクトリは、Claude Code の Grep / Glob、`rg`（既定）、PowerShell の `Get-ChildItem -Recurse` が辿らない。 行き先: 転記済（2026-10-06 → exmem/modern-cli-tools.md）
- 【この件】`_archive/obsolete/` は、プロジェクト管理の旧雛形27ファイル（プレースホルダ `your_project` など）で、作成は 2026-10-02 の1コミットだけ。使われた形跡は、コミットからは見つからなかった（確認: 2026-10-05、根拠: `git log -- resources/_archive`）。 行き先: local（廃止した旧雛形の事実）
- 【汎用】`git filter-repo` 2.47.0 を scoop で導入した（2026-10-05。ユーザーの承認）。 行き先: 転記済（2026-10-06 → exmem/git-subdirectory-split.md）
- 【この件】`notes` のルートに作った `docs/` は、`.gitignore` のホワイトリスト（`/*`）により、既定でローカル専用になる（確認: 2026-10-04、根拠: `git check-ignore -v docs/log.md` が `.gitignore:3:/*` を返した）。共有するには、`.gitignore` に `!/docs/` を足す必要がある。 行き先: 破棄（旧 `.gitignore` のホワイトリストは廃止済み）
- 【この件】`notes` の `AGENTS.md` と `CLAUDE.md` は、導入フックの実行前から存在した。`CLAUDE.md` は `@AGENTS.md` の1行（確認: 2026-10-04、根拠: ファイルの読み取り）。 行き先: 破棄（導入時の観測。log に記録済み）
- 【この件】テーマは Material Gruvbox。以前は Obsidian gruvbox と Everforest で、`78e3975`（2026-10-03）で変更した。変更の理由は、履歴から不明。Zed の自作テーマ（Material Gruvbox Dark）と同じ名前だが、そろえる意図があったかは未確認（仮説）。 行き先: local（この Vault のテーマ）
- 【この件】フォントは PlemolJP Console NF（UI・本文・等幅とも）。以前は Noto Sans JP、BIZ UDPゴシック、HackGen Console NF 系で、`1d75fce`（2026-10-03）で変更した。変更の理由は、履歴から不明。 行き先: local（この Vault のフォント）
- 【この件】現在の Obsidian の設定（確認: 2026-10-04、根拠: `.obsidian/*.json` の読み取り）: 行き先: local（現在の Obsidian の設定値）
  - 新規ノートの保存先は現在のフォルダ（`newFileLocation: current`）、添付は `./`、行番号を表示、削除の確認あり、タブ幅 2、検索から除外するフィルターは `.tmp.` `_archive/` `.claude/`。
  - コミュニティプラグインは `colored-tags` だけ。有効なスニペットは `material-gruvbox-bold`、`file-explorer-compact`、`readable-width`。
  - 有効なコアプラグインは、`file-explorer` `global-search` `switcher` `backlink` `outgoing-link` `tag-pane` `properties` `page-preview` `command-palette` `editor-status` `bookmarks` `outline` `word-count` `file-recovery` `sync` `bases`。
- 【この件】食い違い: `exmem/knowledge/obsidian-vault.md` の「設定」節（2026-10-01 時点の記述）は、現在の設定と違う。 行き先: 転記済（2026-10-06 → exmem/obsidian-vault.md。設定節が現状と一致していることを確認）
- 【この件】2025-09-22 に、9つのコミュニティプラグインを追加し（`44054b5`）、翌日に取り消した（`dcbe209`）。 行き先: 転記済（2026-10-06 → exmem/obsidian-vault.md）
- 【この件】dotfiles 側の 2026-10-02 より前の履歴は、履歴の作り直しで残っていない（確認: 2026-10-04、根拠: `git log --all -- windows/obsidian` の結果が、初期コミットと `bbb294b` だけ）。 行き先: 転記済（2026-10-06 → exmem/workflow-kit.md）

## Gotchas

- 状況: PowerShell のスクリプトで `docs/log.md` を書き換えて書き戻したら、ファイルが二重になり、直そうとした次のスクリプトで空になった（2026-10-06）
  - 【汎用】行き先: 転記済（2026-10-06 → exmem/knowledge/windows-cli-pitfalls.md の Gotchas と Decisions。原因・解決・「Edit で行う」の決定を突き合わせ済み）
- 状況: `colored-tags` の `data.json` を、追跡する・しないが2回切り替わった
  - 【この件】行き先: 転記済（2026-10-06 → exmem/app-config-placement.md、exmem/workflow-kit.md）
- 状況: AI が提案した記録先を「決定済み」と書いて進め、ユーザーに指摘された
  - 【汎用】行き先: 転記済（2026-10-06 → exmem/human-ai-decision-loop.md）
