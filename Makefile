CC = x86_64-w64-mingw32-gcc
CFLAGS = -I../loader/include -std=c99 -s -O2 -g0 -Wno-write-strings -fno-exceptions -fmerge-all-constants
LDFLAGS = -L../loader -lloader -fvisibility=hidden

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Source files
SRCS = $(shell find $(SRC_DIR) -type f -name '*.c')
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Executable name
TARGET = libfetch.a

.PHONY: all clean

all: $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(TARGET): $(OBJS)
	x86_64-w64-mingw32-ar rcs $@ $(OBJS)


clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: clean
