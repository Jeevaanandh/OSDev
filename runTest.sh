#!/bin/bash
set -e

IMAGE="disk.img"

echo "[+] Assembling..."
nasm -f bin Bootloader/bootloader.asm -o stage1.bin
nasm -f bin Bootloader/testBoot2.asm -o stage2.bin

echo "[+] Creating image..."
dd if=/dev/zero of=$IMAGE bs=512 count=40960

echo "[+] Formatting FAT16 with 20 reserved sectors..."
mkfs.fat -F 16 -R 20 $IMAGE

echo "[+] Writing stage1 to sector 0..."
dd if=stage1.bin of=$IMAGE conv=notrunc bs=512 count=1

echo "[+] Writing stage2 into reserved area (sector 1)..."
dd if=stage2.bin of=$IMAGE conv=notrunc bs=512 seek=1

echo "[+] Done!"

qemu-system-x86_64 -drive format=raw,file=disk.img