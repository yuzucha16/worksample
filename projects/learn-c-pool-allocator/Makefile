# C のメモリプールアロケータの学習（README.md の完了条件）。WSL（Ubuntu 24.04）の gcc と make で動かす。
# チェックの一覧と根拠は docs/coding-rules.md。
CC      := gcc
WARN    := -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wvla -Wstrict-prototypes -Wmissing-prototypes -Werror
CFLAGS  := -std=c11 -g -O1 $(WARN) -fno-omit-frame-pointer
SANFLAGS := -fsanitize=address,undefined -fno-sanitize-recover=undefined
BUILD   := build

SRC     := $(wildcard src/*.c)
TESTS   := $(wildcard tests/test_*.c)
TEST_BINS := $(patsubst tests/%.c,$(BUILD)/%,$(TESTS))
ALL_C   := $(SRC) $(TESTS) $(wildcard src/*.h)

.PHONY: check test analyze check-rules format format-check probe clean

# 全チェック。1つでも失敗すれば失敗する。
check: format-check analyze check-rules test probe

# 単体テストを、ASan と UBSan つきで実行する。警告が1件でも出たら失敗する。
test: $(TEST_BINS)
	@set -e; for t in $(TEST_BINS); do echo "== $$t"; ./$$t; done

$(BUILD)/test_%: tests/test_%.c $(SRC) | $(BUILD)
	$(CC) $(CFLAGS) $(SANFLAGS) -Isrc $< $(SRC) -o $@

# gcc の静的解析（-fanalyzer）。解析だけで、実行ファイルは作らない。
analyze:
	@set -e; for f in $(SRC) $(TESTS); do echo "analyze $$f"; $(CC) $(CFLAGS) -fanalyzer -Isrc -c $$f -o /dev/null; done

# コーディングルールの制約（初期値つき .data なし、グローバル変数なし、動的確保なし）。対象は src/ のみ（組込み用途の実装コードだけ。
# テストは実現のしやすさを優先する）。改行・文字コードは、テストも含めて見る。
check-rules:
	@if [ -n "$(SRC)" ]; then tools/check-rules.sh $(SRC) $(wildcard src/*.h); fi
	@if [ -n "$(TESTS)" ]; then tools/check-rules.sh --encoding-only $(TESTS); fi

# 整形。clang-format が無いときは、検査を飛ばしたことを明示する（dotfiles の manifests/apt.txt で導入する）。
format:
	clang-format -i $(ALL_C)

format-check:
	@if command -v clang-format >/dev/null 2>&1; then clang-format --dry-run --Werror $(ALL_C) && echo "OK: format-check"; else echo "SKIP: format-check（clang-format が未導入）"; fi

# サニタイザと check-rules が実際に効いていることの確認（意図したバグ・違反を見逃さないこと）。成功 = すべてが検出されて失敗する。
probe: | $(BUILD)
	$(CC) $(CFLAGS) $(SANFLAGS) -Wno-error tests/probe/asan_overflow.c -o $(BUILD)/asan_overflow
	$(CC) $(CFLAGS) $(SANFLAGS) -Wno-error tests/probe/ubsan_overflow.c -o $(BUILD)/ubsan_overflow
	@if ./$(BUILD)/asan_overflow >/dev/null 2>&1; then echo "FAIL: ASan が検出しなかった"; exit 1; else echo "OK: ASan が検出した"; fi
	@if ./$(BUILD)/ubsan_overflow >/dev/null 2>&1; then echo "FAIL: UBSan が検出しなかった"; exit 1; else echo "OK: UBSan が検出した"; fi
	@if tools/check-rules.sh tests/probe/rules_global.c >/dev/null 2>&1; then echo "FAIL: check-rules がグローバル変数を検出しなかった"; exit 1; else echo "OK: check-rules がグローバル変数を検出した"; fi
	@if tools/check-rules.sh tests/probe/rules_static_data.c >/dev/null 2>&1; then echo "FAIL: check-rules が初期値つき .data を検出しなかった"; exit 1; else echo "OK: check-rules が初期値つき .data を検出した"; fi
	@if tools/check-rules.sh tests/probe/rules_ok.c >/dev/null 2>&1; then echo "OK: check-rules が許可される例（static const、ゼロ初期化 .bss）を通した"; else echo "FAIL: check-rules が許可される例を誤検出した"; exit 1; fi
	@if tools/check-rules.sh tests/probe/rules_malloc.c >/dev/null 2>&1; then echo "FAIL: check-rules が malloc を検出しなかった"; exit 1; else echo "OK: check-rules が malloc を検出した"; fi
	@if tools/check-rules.sh tests/probe/rules_libc.c >/dev/null 2>&1; then echo "FAIL: check-rules が libc 依存を検出しなかった"; exit 1; else echo "OK: check-rules が libc 依存を検出した"; fi
	@sed 's/$$/\r/' tests/test_smoke.c > $(BUILD)/probe_crlf.c
	@if tools/check-rules.sh $(BUILD)/probe_crlf.c >/dev/null 2>&1; then echo "FAIL: check-rules が CRLF を検出しなかった"; exit 1; else echo "OK: check-rules が CRLF を検出した"; fi
	@printf '\357\273\277int bom_probe(void) { return 0; }\n' > $(BUILD)/probe_bom.c
	@if tools/check-rules.sh $(BUILD)/probe_bom.c >/dev/null 2>&1; then echo "FAIL: check-rules が BOM を検出しなかった"; exit 1; else echo "OK: check-rules が BOM を検出した"; fi

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)
