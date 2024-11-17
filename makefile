# Program name
PROG = enchiridion

# Compiler
CC = gcc

# Output directories
SRC_DIR = src
BUILD_DIR = build
OUT_DIR = bin

# Automatically discover all source files in the src directory
SEARCHPATH = $(shell find $(SRC_DIR) -type d | sort)
SRCS = $(wildcard $(SRC_DIR)/**/*.c $(SRC_DIR)/*.c)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Dependencies
DEPS = $(wildcard $(SRC_DIR)/**/*.h $(SRC_DIR)/*.h)

# Compiler and linker flags
CXXFLAGS := $(shell sdl2-config --cflags)  # SDL2-specific flags
CXXFLAGS += -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds
LDFLAGS += $(shell sdl2-config --libs) -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lm

# Build target
all: $(OUT_DIR)/$(PROG)

$(OUT_DIR)/$(PROG): $(OBJS)
	@mkdir -p $(OUT_DIR)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

# Rule to compile each source file into an object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove built files
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(OUT_DIR)

# Debugging info
.PHONY: debug
debug:
	@echo "Source files: $(SRCS)"
	@echo "Object files: $(OBJS)"
