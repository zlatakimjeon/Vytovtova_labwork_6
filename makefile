CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g -O0 -Iinclude
SRC = src/cbs.c
TEST_SRC = test/test.c
TEST_BIN = test/test

ifeq ($(OS),Windows_NT)
    RM = del /Q
    MKDIR = if not exist test mkdir test
    EXE_EXT = .exe
    TEST_BIN := $(TEST_BIN)$(EXE_EXT)
else
    RM = rm -f
    MKDIR = mkdir -p test
    EXE_EXT =
endif

.PHONY: all clean test

all: test

test: $(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) src/cbs.c
	$(MKDIR)
	$(CC) $(CFLAGS) $(TEST_SRC) src/cbs.c -o $(TEST_BIN)

clean:
	-$(RM) $(TEST_BIN) 2>nul || true
