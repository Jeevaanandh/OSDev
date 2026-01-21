nasm -f bin Bootloader/bootloader.asm -o boot.bin

nasm -f elf32 Kernel/kernel.asm -o kernel.o
i686-elf-gcc -m32 -ffreestanding -fno-pie -c Kernel/kernel_entry.c -o kernel_entry.o
i686-elf-ld -T linker.ld --oformat binary -o kernel.bin kernel.o kernel_entry.o


cat boot.bin > os-image.bin

cat kernel.bin >> os-image.bin

qemu-system-i386 -drive format=raw,file=os-image.bin