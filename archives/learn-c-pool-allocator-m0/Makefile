# C のメモリプールの学習（README.md の完了条件）。WSL（Ubuntu 24.04）の gcc と make で動かす。
# チェックの一覧と根拠は docs/coding-rules.md、設計は docs/design.md。
CC      := gcc
WARN    := -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wvla -Wstrict-prototypes -Wmissing-prototypes -Werror
# -fno-strict-aliasing: 空きブロックに void * を書く侵入型リストのため（docs/design.md の判断 E1。ユーザー承認）
CFLAGS  := -std=c11 -g -O1 $(WARN) -fno-strict-aliasing -fno-omit-frame-pointer
SANFLAGS := -fsanitize=address,undefined -fno-sanitize-recover=undefined
BUILD   := build

SRC     := $(wildcard src/*.c)
TESTS   := $(wildcard tests/test_*.c)
TEST_BINS := $(patsubst tests/%.c,$(BUILD)/%,$(TESTS))
TEST_BINS_O2 := $(patsubst tests/%.c,$(BUILD)/o2/%,$(TESTS))
WHITE   := $(wildcard tests/white_*.c)
ALL_C   := $(SRC) $(TESTS) $(WHITE) $(wildcard src/*.h) $(wildcard tests/*.h)

# 組込み向けの freestanding ビルド（フットプリントの測定。サニタイザなし）。
FREE    := -std=c11 -Os -ffreestanding -fno-pic -fno-stack-protector -fno-strict-aliasing
ARM_GCC := arm-none-eabi-gcc
# 対象: Cortex-M0 / M0+（除算命令なし。src/pool.c が除算を使わない経路を自動で選ぶ）と、M3 / M4。
ARM_CPUS := cortex-m0 cortex-m0plus cortex-m3 cortex-m4
# 除算を使わない経路を、ホストでも強制して試験する（src/pool.c の POOL_NO_HW_DIV）。
SOFT    := -DPOOL_NO_HW_DIV

.PHONY: check test test-o2 test-soft test-soft-o2 test-white test-white-soft analyze check-rules check-arm size size-arm format format-check probe clean

# 全チェック。1つでも失敗すれば失敗する。
check: format-check analyze check-rules check-arm test test-o2 test-soft test-soft-o2 test-white test-white-soft probe

# 単体テストを、ASan と UBSan つきで実行する。警告が1件でも出たら失敗する。
test: $(TEST_BINS)
	@set -e; for t in $(TEST_BINS); do echo "== $$t"; ./$$t; done

# -O2（strict aliasing など、最適化に依存する問題を見る）でも同じテストを実行する。
test-o2: $(TEST_BINS_O2)
	@set -e; for t in $(TEST_BINS_O2); do echo "== $$t"; ./$$t; done

# 除算を使わない経路（M0 用）を、ホストで同じテストにかける（-O1 と -O2）。
TEST_BINS_SOFT := $(patsubst tests/%.c,$(BUILD)/soft/%,$(TESTS))
TEST_BINS_SOFT_O2 := $(patsubst tests/%.c,$(BUILD)/soft_o2/%,$(TESTS))

test-soft: $(TEST_BINS_SOFT)
	@set -e; for t in $(TEST_BINS_SOFT); do echo "== $$t"; ./$$t; done

test-soft-o2: $(TEST_BINS_SOFT_O2)
	@set -e; for t in $(TEST_BINS_SOFT_O2); do echo "== $$t"; ./$$t; done

$(BUILD)/soft/test_%: tests/test_%.c $(SRC) | $(BUILD)/soft
	$(CC) $(CFLAGS) $(SOFT) $(SANFLAGS) -Isrc $< $(SRC) -o $@

$(BUILD)/soft_o2/test_%: tests/test_%.c $(SRC) | $(BUILD)/soft_o2
	$(CC) $(filter-out -O1,$(CFLAGS)) -O2 $(SOFT) $(SANFLAGS) -Isrc $< $(SRC) -o $@

$(BUILD)/test_%: tests/test_%.c $(SRC) | $(BUILD)
	$(CC) $(CFLAGS) $(SANFLAGS) -Isrc $< $(SRC) -o $@

$(BUILD)/o2/test_%: tests/test_%.c $(SRC) | $(BUILD)/o2
	$(CC) $(filter-out -O1,$(CFLAGS)) -O2 $(SANFLAGS) -Isrc $< $(SRC) -o $@

# ホワイトボックステスト（tests/white_*.c は pool.c を直接取り込む。リンクしない）。除算の経路と、
# 除算なしの経路（POOL_NO_HW_DIV）の両方で実行する。
test-white: | $(BUILD)
	@set -e; for f in $(WHITE); do echo "== $$f"; $(CC) $(CFLAGS) $(SANFLAGS) -Isrc -Itests $$f -o $(BUILD)/white; ./$(BUILD)/white; done

test-white-soft: | $(BUILD)
	@set -e; for f in $(WHITE); do echo "== $$f (soft)"; $(CC) $(CFLAGS) $(SOFT) $(SANFLAGS) -Isrc -Itests $$f -o $(BUILD)/white_soft; ./$(BUILD)/white_soft; done
# gcc の静的解析（-fanalyzer）。解析だけで、実行ファイルは作らない。
analyze:
	@set -e; for f in $(SRC) $(TESTS) $(WHITE); do echo "analyze $$f"; $(CC) $(CFLAGS) -fanalyzer -Isrc -c $$f -o /dev/null; done

# コーディングルールの制約（初期値つき .data なし、グローバル変数なし、動的確保なし、libc 非依存）。対象は src/ のみ
# （組込み用途の実装コードだけ。テストは実現のしやすさを優先する）。改行・文字コードは、テストも含めて見る。
check-rules:
	@if [ -n "$(SRC)" ]; then tools/check-rules.sh $(SRC) $(wildcard src/*.h); fi
	@if [ -n "$(TESTS)" ]; then tools/check-rules.sh --encoding-only $(TESTS) $(WHITE) $(wildcard tests/*.h); fi

# ARM（Cortex-M）向けにコンパイルして、未定義シンボル（libgcc の除算などの補助関数を含む）が無いことを確認する。
# ツールチェーンが無いときは、飛ばしたことを明示する（dotfiles の manifests/apt.txt の gcc-arm-none-eabi）。
check-arm: | $(BUILD)
	@if ! command -v $(ARM_GCC) >/dev/null 2>&1; then echo "SKIP: check-arm（$(ARM_GCC) が未導入）"; \
	elif [ -z "$(SRC)" ]; then echo "OK: check-arm（src が無い）"; \
	else fail=0; for cpu in $(ARM_CPUS); do for f in $(SRC); do \
	  o=$(BUILD)/arm_$${cpu}_$$(basename $$f .c).o; \
	  $(ARM_GCC) -mcpu=$$cpu -mthumb $(FREE) -Isrc -c $$f -o $$o || exit 1; \
	  u=$$(arm-none-eabi-nm -u $$o | awk '{print $$NF}' | tr '\n' ' '); \
	  if [ -n "$$u" ]; then echo "FAIL: $$f ($$cpu): 未定義シンボル: $$u"; fail=1; else echo "OK: $$f ($$cpu)"; fi; \
	done; done; \
	exit $$fail; fi

# フットプリント（.text .data .bss）。ホスト（x86-64）の値は参考。目標は .data が 0。
size: | $(BUILD)
	@set -e; for f in $(SRC); do $(CC) $(FREE) -Isrc -c $$f -o $(BUILD)/size_$$(basename $$f .c).o; done; \
	if [ -n "$(SRC)" ]; then echo "== host $(CC) $(FREE)"; size $(BUILD)/size_*.o; fi

# ARM（Cortex-M）向けのフットプリント。ツールチェーンが無いときは、飛ばしたことを明示する。
size-arm: | $(BUILD)
	@if ! command -v $(ARM_GCC) >/dev/null 2>&1; then echo "SKIP: size-arm（$(ARM_GCC) が未導入）"; \
	else set -e; for cpu in $(ARM_CPUS); do for f in $(SRC); do \
	  $(ARM_GCC) -mcpu=$$cpu -mthumb $(FREE) -Isrc -c $$f -o $(BUILD)/sz_$$cpu.o; \
	  echo "== $$cpu $$f"; arm-none-eabi-size $(BUILD)/sz_$$cpu.o; \
	done; done; fi

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
	@if tools/check-rules.sh tests/probe/rules_int2ptr.c >/dev/null 2>&1; then echo "FAIL: check-rules が整数からポインタへのキャストを検出しなかった"; exit 1; else echo "OK: check-rules が整数からポインタへのキャストを検出した"; fi
	@if tools/check-rules.sh tests/probe/rules_recursion.c >/dev/null 2>&1; then echo "FAIL: check-rules が再帰を検出しなかった"; exit 1; else echo "OK: check-rules が再帰（直接・相互）を検出した"; fi
	@sed 's/$$/\r/' tests/test_smoke.c > $(BUILD)/probe_crlf.c
	@if tools/check-rules.sh $(BUILD)/probe_crlf.c >/dev/null 2>&1; then echo "FAIL: check-rules が CRLF を検出しなかった"; exit 1; else echo "OK: check-rules が CRLF を検出した"; fi
	@printf '\357\273\277int bom_probe(void) { return 0; }\n' > $(BUILD)/probe_bom.c
	@if tools/check-rules.sh $(BUILD)/probe_bom.c >/dev/null 2>&1; then echo "FAIL: check-rules が BOM を検出しなかった"; exit 1; else echo "OK: check-rules が BOM を検出した"; fi

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/o2:
	mkdir -p $(BUILD)/o2

$(BUILD)/soft:
	mkdir -p $(BUILD)/soft

$(BUILD)/soft_o2:
	mkdir -p $(BUILD)/soft_o2

clean:
	rm -rf $(BUILD)
