CC = x86_64-elf-gcc
AR = x86_64-elf-ar
CFLAGS = -Wall -Wextra -ffreestanding -nostdinc -O2 -Iinclude

SRCS = $(shell find . -path ./tests -prune -o -name "*.c" -print)
OBJS = $(SRCS:.c=.o)

TARGET = libc.a

HOSTCC = gcc
HOSTCFLAGS = -Wall -Wextra -g -O1 -fno-builtin
HOST_LIB_CFLAGS = -Wall -Wextra -ffreestanding -g -O2 -Iinclude -fno-builtin -fno-tree-loop-distribute-patterns

BUILD_DIR = build/test
TEST_BIN = $(BUILD_DIR)/run_tests
TEST_SRCS = $(wildcard tests/*.c) $(wildcard tests/*/*.c) $(wildcard src/string/*.c) $(wildcard src/ctype/*.c)
TEST_OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(TEST_SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_OBJS)
	$(HOSTCC) $(HOSTCFLAGS) -o $@ $^

$(BUILD_DIR)/tests/%.o: tests/%.c
	@mkdir -p $(dir $@)
	$(HOSTCC) $(HOSTCFLAGS) -c $< -o $@

$(BUILD_DIR)/src/string/%.o: src/string/%.c
	@mkdir -p $(dir $@)
	$(HOSTCC) $(HOST_LIB_CFLAGS) -c $< -o $@

$(BUILD_DIR)/src/ctype/%.o: src/ctype/%.c
	@mkdir -p $(dir $@)
	$(HOSTCC) $(HOST_LIB_CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf build

.PHONY: all clean test
