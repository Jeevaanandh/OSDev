nasm -f bin Kernel/kernel.asm -o kernel.bin

nasm -f bin Bootloader/bootloader.asm -o boot.bin

cat boot.bin kernel.bin > os-image.bin
qemu-system-i386 -drive file=os-image.bin,format=raw,if=ide
