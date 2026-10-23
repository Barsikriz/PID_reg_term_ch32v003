# Host-side builds for the CH32V003 thermostat project.
# Firmware cross-compilation will be added after the MCU startup/linker setup is fixed.

.DEFAULT_GOAL := all

CC := gcc
BUILD_DIR := build/host

CPPFLAGS := -Ifirmware/control -Ifirmware/system
CFLAGS   := -std=c11 -Og -g3 -Wall -Wextra -Wpedantic -Wshadow -Wstrict-prototypes
LDLIBS   := -lm

CORE_SRC := firmware/control/reference.c firmware/system/state_machine.c
TEST_SRC := $(wildcard tests/test_*.c)
ALL_SRC  := $(CORE_SRC) $(TEST_SRC)

CORE_OBJ := $(patsubst %.c,$(BUILD_DIR)/%.o,$(CORE_SRC))
TEST_OBJ := $(patsubst %.c,$(BUILD_DIR)/%.o,$(TEST_SRC))
TEST_BIN := $(patsubst tests/%.c,$(BUILD_DIR)/tests/%.exe,$(TEST_SRC))
DEPFILES := $(CORE_OBJ:.o=.d) $(TEST_OBJ:.o=.d)

# Keep test object files for incremental rebuilds.
.SECONDARY: $(TEST_OBJ)

ifeq ($(OS),Windows_NT)
MKDIR = powershell -NoProfile -Command "New-Item -ItemType Directory -Force -Path '$(1)' | Out-Null"
RMDIR = powershell -NoProfile -Command "if (Test-Path '$(1)') { Remove-Item -LiteralPath '$(1)' -Recurse -Force }"
CC_FOUND := $(subst \,/,$(firstword $(shell where.exe $(CC))))
else
MKDIR = mkdir -p "$(1)"
RMDIR = rm -rf "$(1)"
CC_FOUND := $(shell command -v $(CC))
endif

CC_PATH := $(if $(CC_FOUND),$(CC_FOUND),$(CC))

.PHONY: all test clean compdb help

all: $(TEST_BIN)
	@echo Host tests built: $(words $(TEST_BIN))

test: all
ifeq ($(strip $(TEST_BIN)),)
	@echo No tests found in tests/test_*.c
else
	@$(foreach exe,$(TEST_BIN),"$(exe)" && ) echo All host tests passed.
endif

$(BUILD_DIR)/%.o: %.c
	@$(call MKDIR,$(dir $@))
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c "$<" -o "$@"

$(BUILD_DIR)/tests/%.exe: $(BUILD_DIR)/tests/%.o $(CORE_OBJ)
	$(CC) $^ -o "$@" $(LDFLAGS) $(LDLIBS)

-include $(DEPFILES)

clean:
	@$(call RMDIR,build)

# Regenerate clangd's compile_commands.json without Bear/CMake/Python.
# Paths are normalized to forward slashes for JSON and clangd on Windows.
COMMA := ,
PROJECT_DIR := $(subst \,/,$(CURDIR))
define COMPDB_ENTRY
{"directory":"$(PROJECT_DIR)","file":"$(subst \,/,$(abspath $(1)))","arguments":["$(CC_PATH)","-std=c11","-Og","-g3","-Wall","-Wextra","-Wpedantic","-Wshadow","-Wstrict-prototypes","-Ifirmware/control","-Ifirmware/system","-c","$(subst \,/,$(abspath $(1)))"]}
endef

compdb:
	$(file >compile_commands.json,[)
	$(foreach src,$(ALL_SRC),$(file >>compile_commands.json,$(call COMPDB_ENTRY,$(src))$(if $(filter $(src),$(lastword $(ALL_SRC))),,$(COMMA))))
	$(file >>compile_commands.json,])
	@echo Generated compile_commands.json for $(words $(ALL_SRC)) C files.

help:
	@echo all    - Compile host test executables
	@echo test   - Build and run all host tests
	@echo clean  - Delete the build directory
	@echo compdb - Generate compile_commands.json for clangd
