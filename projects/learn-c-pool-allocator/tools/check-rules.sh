#!/usr/bin/env bash
# docs/coding-rules.md の機械で確認できる制約を、オブジェクトファイルから検査する。
#   - 初期値つきの .data を持たない。グローバル変数（外部リンケージの変数）を持たない。グローバルでないゼロ初期化の .bss は許可
#   - 動的確保（malloc 系）を呼ばない
#   - 改行コードは LF、文字コードは UTF-8（BOM なし）（.h も対象）
# 使い方: tools/check-rules.sh <file.c>...   違反があれば、内容を出して終了コード 1。
# 再帰の禁止は、ここでは検査しない（docs/coding-rules.md の「未検査」）。
set -u

# --encoding-only: 改行・文字コードだけを見る（テストなど、制約の対象外のファイル用）
encoding_only=0
if [[ "${1:-}" == "--encoding-only" ]]; then
  encoding_only=1
  shift
fi

CC=${CC:-gcc}
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
fail=0

# サニタイザは、自前の .data / .bss を足すので、検査用のビルドには付けない。
# 動的確保の呼び出しが最適化で消えないよう、-O0 にする。
for src in "$@"; do
  # 改行コードは LF、文字コードは UTF-8（BOM なし）。ヘッダもここで見る。
  if grep -q $'\r' "$src"; then
    echo "FAIL: $src: CR（CRLF の改行）がある"
    fail=1
  fi
  if [[ "$(head -c 3 "$src" | od -An -tx1 | tr -d ' \n')" == "efbbbf" ]]; then
    echo "FAIL: $src: BOM がある"
    fail=1
  fi
  if ! iconv -f UTF-8 -t UTF-8 "$src" >/dev/null 2>&1; then
    echo "FAIL: $src: UTF-8 として読めない"
    fail=1
  fi
  [[ $encoding_only -eq 0 && "$src" == *.c ]] || continue
  obj="$tmp/$(basename "${src%.c}").o"
  if ! "$CC" -std=c11 -O0 -c "$src" -o "$obj"; then
    echo "FAIL: コンパイルできない: $src"
    fail=1
    continue
  fi
  # 禁止: 初期値つきの .data（D/d。フットプリントと起動のため）、外部リンケージの変数（大文字 B/C/G/S。グローバル変数）。
  # 許可: グローバルでないゼロ初期化の .bss（小文字 b。static のローカル変数など）、.rodata（static const）。
  # 限界: ファイルスコープの static 変数（小文字 b）も許可になる。nm では、関数内の static と区別できない。
  vars=$(nm --defined-only "$obj" | awk '$2 ~ /^[DdBCGS]$/ { print $3 " (" $2 ")" }')
  if [[ -n "$vars" ]]; then
    echo "FAIL: $src: 禁止された変数がある（.data、またはグローバル変数）:"
    echo "$vars" | sed 's/^/    /'
    fail=1
  fi
  calls=$(nm -u "$obj" | awk '$2 ~ /^(malloc|calloc|realloc|free|aligned_alloc|posix_memalign|strdup|strndup)$/ { print $2 }')
  if [[ -n "$calls" ]]; then
    echo "FAIL: $src: 動的確保を呼んでいる:"
    echo "$calls" | sed 's/^/    /'
    fail=1
  fi
done

if [[ $fail -eq 0 ]]; then echo "OK: check-rules（$# ファイル）"; fi
exit $fail
