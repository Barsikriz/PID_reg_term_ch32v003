# src/Makefile
CC := riscv-none-elf-gcc
OBJCOPY := riscv-none-elf-objcopy

PROJECT_ROOT := $(abspath ..)
BUILD_DIR := $(PROJECT_ROOT)/build
INCLUDE_DIR := $(PROJECT_ROOT)/include
LD_SCRIPT := $(PROJECT_ROOT)/ld/link.ld

CFLAGS := -march=rv32ec -mabi=ilp32e -O2 -ffreestanding -nostdlib -Wall -I$(INCLUDE_DIR)
LDFLAGS := -T $(LD_SCRIPT) -nostartfiles

SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

.PHONY: all clean dirs

all: dirs $(BUILD_DIR)/firmware.elf $(BUILD_DIR)/firmware.bin

dirs:
	@mkdir -p $(BUILD_DIR)

# compile each C source into build/*.o
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# link into ELF
$(BUILD_DIR)/firmware.elf: $(OBJS) $(LD_SCRIPT)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

# objcopy to binary
$(BUILD_DIR)/firmware.bin: $(BUILD_DIR)/firmware.elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(BUILD_DIR)/*
