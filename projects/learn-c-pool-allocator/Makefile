# C のメモリプールアロケータの学習（README.md の完了条件）。WSL（Ubuntu 24.04）の gcc と make で動かす。
CC      := gcc
CFLAGS  := -std=c11 -g -O1 -Wall -Wextra -Wpedantic -Werror -fno-omit-frame-pointer
SANFLAGS := -fsanitize=address,undefined -fno-sanitize-recover=undefined
BUILD   := build

SRC     := $(wildcard src/*.c)
TESTS   := $(wildcard tests/test_*.c)
TEST_BINS := $(patsubst tests/%.c,$(BUILD)/%,$(TESTS))

.PHONY: test probe clean

# 単体テストを、ASan と UBSan つきで実行する。警告が1件でも出たら失敗する。
test: $(TEST_BINS)
	@set -e; for t in $(TEST_BINS); do echo "== $$t"; ./$$t; done

$(BUILD)/test_%: tests/test_%.c $(SRC) | $(BUILD)
	$(CC) $(CFLAGS) $(SANFLAGS) -Isrc $< $(SRC) -o $@

# サニタイザが実際に効いていることの確認（意図したバグを見逃さないこと）。成功 = 両方が検出されて非ゼロで終わる。
probe: | $(BUILD)
	$(CC) $(CFLAGS) $(SANFLAGS) -Wno-error tests/probe/asan_overflow.c -o $(BUILD)/asan_overflow
	$(CC) $(CFLAGS) $(SANFLAGS) -Wno-error tests/probe/ubsan_overflow.c -o $(BUILD)/ubsan_overflow
	@if ./$(BUILD)/asan_overflow >/dev/null 2>&1; then echo "FAIL: ASan が検出しなかった"; exit 1; else echo "OK: ASan が検出した"; fi
	@if ./$(BUILD)/ubsan_overflow >/dev/null 2>&1; then echo "FAIL: UBSan が検出しなかった"; exit 1; else echo "OK: UBSan が検出した"; fi

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)
