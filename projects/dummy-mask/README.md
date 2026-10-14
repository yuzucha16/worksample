---
status: active
area: office-admin
type: verification
review: 仮置き（未承認）
created: 2026-10-14
updated: 2026-10-14
---

# dummy-mask

マスク・復元の確認用のダミー Project。実在の名前は一切ない（架空の顧客 A=アクメ商事、B=ベータ工業、担当者=田中太郎）。次の確認・試行の参考に残す。所属 Area: [[areas/office-admin/README|office-admin]]

## 中身

- 生成: `resources/workflow-kit/room/tests/dummy_fixture.py` を `python tests/dummy_fixture.py <この Project のディレクトリ>` で実行する（`room` の下で）。`_noai/` は追跡されないので、これで作り直せる。
- `_noai/raw/dummy_sales.xlsx`: 実際のピボットテーブル、コメント、定義名、プロパティ（作成者・会社）、シート名に語、通常+太字の run をまたぐ語（「アクメ」+「商事」）。
- `_noai/raw/dummy_customers.csv`: cp932。全角・半角カナ・英字の表記ゆれ、辞書にない顧客（列指定で拾う）。
- `_noai/mask.toml`: ダミー用の語の表。

## 含めていないもの

- プリンタ設定（`printerSettings*.bin`）。手で作れないので、実機のブックで別に確認する。
