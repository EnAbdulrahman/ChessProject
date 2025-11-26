# --- Build Configuration Variables ---
TARGET := chess
CC := gcc
BUILD_DIR := build
# Default build mode is Release (Optimized)
BUILD_MODE ?= Release

# Source and Generated Files
# Add all your .c files here
SRC := main.c draw.c
OBJ := $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))
DEP := $(addprefix $(BUILD_DIR)/, $(SRC:.c=.d))
EXECUTABLE := $(BUILD_DIR)/$(TARGET)

# --- Compiler Flags ---

# CFLAGS: Common Flags (System-wide Setup)
# -Wall, -Wextra: Robust warnings
# -std=c17: Modern C standard
# -MMD: Auto-generate dependency files
# Note: Removed -I. because system headers (raylib.h) are found automatically
CFLAGS := -Wall -Wextra -std=c17 -MMD

# Conditional CFLAGS based on the mode
ifeq ($(BUILD_MODE), Debug)
# -g means debug mode
# -O0 zero optimizations
CFLAGS += -g -O0 -DDEBUG
$(info Building in DEBUG mode (-g -O0, C17)...)
else
# -O2 standard build optimization
# -s strip (remove the symbols table from out binary)
CFLAGS += -O2 -s
$(info Building in RELEASE mode (-O2, C17)...)
endif

# LDFLAGS: Linker Flags
# The compiler finds libraylib.so in the standard system path automatically
LDFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# --- Targets ---

.PHONY: all debug run clean

# Default Target: 'make' builds the optimized RELEASE version
all: $(BUILD_DIR) $(EXECUTABLE)

# Debug Target: 'make debug' builds the DEBUG version
debug:
	$(MAKE) BUILD_MODE=Debug all

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $@

# Final Linking
$(EXECUTABLE): $(OBJ)
	@echo "Linking $(EXECUTABLE)..."
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Compiling .c to .o
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Include auto-generated dependency files
-include $(DEP)

# Run Target
run: $(EXECUTABLE)
	@echo "Running $(EXECUTABLE)..."
	./$(EXECUTABLE)

# Clean Target
clean:
	@echo "Cleaning build directory..."
	rm -rf $(BUILD_DIR)
