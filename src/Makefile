# Makefile для CH32V003

CC = riscv-none-elf-gcc
OBJCOPY = riscv-none-elf-objcopy

CFLAGS = -march=rv32ec \
         -mabi=ilp32e \
         -mcmodel=medany \
         -O2 \
         -ffreestanding \
         -nostdlib \
         -nostartfiles \
         -Wall

all: firmware.elf firmware.bin

firmware.elf: main.c
	$(CC) $(CFLAGS) -T link.ld main.c startup.c -o firmware.elf

firmware.bin: firmware.elf
	$(OBJCOPY) -O binary firmware.elf firmware.bin

clean:
	del *.elf *.bin *.hex *.o
