# dotfiles に足したもの（dotfiles-additions）

この Project の作業で、dotfiles に追加したコマンド・パッケージ・設定を、足した時点で1行ずつ記録する。作業の最後に、ユーザーへまとめて報告する（ユーザーの指示、2026-10-06）。

| 日付 | 追加したもの | 理由 | 反映先（dotfiles のファイル） | コミット（dotfiles） | 実機（WSL）への導入 |
|---|---|---|---|---|---|
| 2026-10-06 | `clang-format`（apt） | コードリーディングのコストを下げる（一貫性のためではない。ユーザーの意図） | `manifests/apt.txt`（`# devel`）、`docs/log.md` | `14711b5` | **未導入**（`sudo` にパスワードが要るため、ユーザーが実行する）: `sudo apt install -y clang-format`、または `bash scripts/linux/20_packages.sh` |

導入後の確認: `clang-format --version`、続けて `make check` を実行し、`SKIP: format-check` が `OK: format-check` に変わること（変わらなければ、`.clang-format` の設定が clang-format 18 に合っていない）。
