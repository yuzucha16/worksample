#!/usr/bin/env bash
# docs/coding-rules.md の機械で確認できる制約を、オブジェクトファイルから検査する。
#   - グローバル変数・静的記憶域の変数（.data / .bss）を持たない（static のローカル変数も対象）
#   - 動的確保（malloc 系）を呼ばない
#   - 改行コードは LF、文字コードは UTF-8（BOM なし）（.h も対象）
# 使い方: tools/check-rules.sh <file.c>...   違反があれば、内容を出して終了コード 1。
# 再帰の禁止は、ここでは検査しない（docs/coding-rules.md の「未検査」）。
set -u

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
  [[ "$src" == *.c ]] || continue
  obj="$tmp/$(basename "${src%.c}").o"
  if ! "$CC" -std=c11 -O0 -c "$src" -o "$obj"; then
    echo "FAIL: コンパイルできない: $src"
    fail=1
    continue
  fi
  # 型 B/b（.bss）、D/d（.data）、C（common）、G/g、S/s（小さいデータ）が、変数の定義
  vars=$(nm --defined-only "$obj" | awk '$2 ~ /^[BbDdCGgSs]$/ { print $3 " (" $2 ")" }')
  if [[ -n "$vars" ]]; then
    echo "FAIL: $src: 静的記憶域の変数がある:"
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
