# dotfiles に足したもの（dotfiles-additions）

この Project の作業で、dotfiles に追加したコマンド・パッケージ・設定を、足した時点で1行ずつ記録する。作業の最後に、ユーザーへまとめて報告する（ユーザーの指示、2026-10-06）。

| 日付 | 追加したもの | 理由 | 反映先（dotfiles のファイル） | コミット（dotfiles） | 実機（WSL）への導入 |
|---|---|---|---|---|---|
| 2026-10-06 | `clang-format`（apt） | コードリーディングのコストを下げる（一貫性のためではない。ユーザーの意図） | `manifests/apt.txt`（`# devel`）、`docs/log.md` | `14711b5` | **導入済み**（ユーザーが実行。`clang-format 18.1.3`、Ubuntu 1ubuntu1。ユーザーの報告: 2026-10-06） |
| 2026-10-06 | `gcc-arm-none-eabi`（apt。約 490MB。`libnewlib-arm-none-eabi` も推奨で入る） | Cortex-M 向けの `.text` `.data` `.bss` の実測と、ARM 向けの libc 非依存の検査（`make size-arm` `make check-arm`） | `manifests/apt.txt`（`# devel`）、`docs/log.md` | `08df993` | **導入済み**（ユーザーが実行。`arm-none-eabi-gcc (15:13.2.rel1-2) 13.2.1 20231009`。ユーザーの報告: 2026-10-06） |

`gcc-arm-none-eabi` の導入後の確認（2026-10-06。ユーザーの実行）: `make size-arm` が実測値を出した。`make check-arm` は、Cortex-M0 で未定義シンボル（`__aeabi_uidiv` `__aeabi_uidivmod`）を検出して失敗した（意図した検査の成果。判断待ち。`docs/design.md` の判断 F）。

`clang-format` の導入後の確認（2026-10-06）: `make check` で、`SKIP: format-check` が `OK: format-check` に変わった。最初の実行で、手で揃えたマクロの `\` を指摘し、`make format` で直した（`.clang-format` の設定は、clang-format 18 で動いた）。
