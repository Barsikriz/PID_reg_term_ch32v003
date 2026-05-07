CC = riscv-none-elf-gcc
OBJCOPY = riscv-none-elf-objcopy

# абсолютный путь к include (относительно местоположения Makefile)
INCLUDE_DIR := $(abspath ../include)

CFLAGS = -march=rv32ec \
         -mabi=ilp32e \
         -mcmodel=medany \
         -O2 \
         -ffreestanding \
         -nostdlib \
         -nostartfiles \
         -Wall \
         -I$(INCLUDE_DIR)

SRCS = main.c startup.c
OBJS = $(SRCS:.c=.o)

all: firmware.elf firmware.bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

firmware.elf: $(OBJS) ../ld/link.ld
	$(CC) $(CFLAGS) -T ../ld/link.ld $(OBJS) -o $@

firmware.bin: firmware.elf
	$(OBJCOPY) -O binary firmware.elf firmware.bin

clean:
	rm -f $(OBJS) *.elf *.bin *.hex
