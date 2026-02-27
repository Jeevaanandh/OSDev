#!/bin/bash
set -e

echo "[+] Assembling bootloader..."
nasm -f bin Bootloader/bootloader.asm -o boot.bin

echo "[+] Compiling kernel components..."
nasm -f elf32 Kernel/kernel.asm -o kernel.o
nasm -f elf32 Kernel/irq.asm -o irq.o
i686-elf-gcc -m32 -ffreestanding -fno-pie -c Kernel/kernel_entry.c -o kernel_entry.o
i686-elf-gcc -m32 -ffreestanding -fno-pie -c Kernel/setup/idt.c -o idt.o
i686-elf-gcc -m32 -ffreestanding -fno-pie -c Kernel/setup/pic.c -o pic.o
i686-elf-gcc -m32 -ffreestanding -fno-pie -c Kernel/std/stdFunctions.c -o std.o
i686-elf-gcc -m32 -ffreestanding -fno-pie -c Kernel/interruptHandler/handlers.c -o handlers.o
i686-elf-gcc -m32 -ffreestanding -fno-pie -c Kernel/drivers/keyboard.c -o keyboard.o
i686-elf-gcc -m32 -ffreestanding -fno-pie -c Kernel/drivers/disk.c -o disk.o

echo "[+] Linking kernel..."
i686-elf-ld -T linker.ld --oformat binary -o kernel.bin kernel.o irq.o kernel_entry.o idt.o pic.o std.o handlers.o keyboard.o disk.o

echo "[+] Creating disk image..."
dd if=/dev/zero of=os-image.bin bs=1M count=20

echo "[+] Creating FAT16 filesystem WITH 20 reserved sectors..."
mkfs.fat -F 16 -R 20 os-image.bin

echo "[+] Writing bootloader to reserved sector 0 (preserving FAT)..."
dd if=boot.bin of=os-image.bin conv=notrunc bs=512 count=1

echo "[+] Writing kernel to reserved sectors starting at 1..."
dd if=kernel.bin of=os-image.bin conv=notrunc bs=512 seek=1

echo "[+] Done! Boot sector and kernel written to reserved area."
echo "[+] FAT filesystem starts at sector 20 (LBA 20)"

qemu-system-i386 -drive format=raw,file=os-image.bin