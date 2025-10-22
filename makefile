CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g -O0 -Iinclude
SRC = src/cbs.c
OBJ = $(SRC:.c=.o)
LIBDIR = lib
LIB = $(LIBDIR)/libcbs.a
TEST_SRC = test/test.c
TEST_BIN = test/test

ifeq ($(OS),Windows_NT)
	RM = del /Q
	MKDIR = if not exist $(LIBDIR) mkdir $(LIBDIR)
	EXE_EXT = .exe
	TEST_BIN := $(TEST_BIN)$(EXE_EXT)
else
	RM = rm -f
	MKDIR = mkdir -p $(LIBDIR)
	EXE_EXT =
endif

.PHONY: all clean lib test

all: lib test

lib: $(LIB)

$(LIB): $(OBJ)
	$(MKDIR)
	ar rcs $(LIB) $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(LIB)
	$(MKDIR)
	$(CC) $(CFLAGS) $(TEST_SRC) $(LIB) -o $(TEST_BIN)

clean:
	-$(RM) src\*.o 2>nul || true
	-$(RM) $(LIB) 2>nul || true
	-$(RM) $(TEST_BIN) 2>nul || true
	@if [ -d "$(LIBDIR)" ]; then rmdir $(LIBDIR) 2>/dev/null || true; fi