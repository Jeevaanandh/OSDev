nasm -f bin Bootloader/bootloader.asm -o boot.bin

nasm -f elf32 Kernel/kernel.asm -o kernel.o
nasm -f elf32 Kernel/irq.asm -o irq.o
i686-elf-gcc -m32 -ffreestanding -fno-pie -c Kernel/kernel_entry.c -o kernel_entry.o
i686-elf-gcc -m32 -ffreestanding -fno-pie -c Kernel/setup/idt.c -o idt.o
i686-elf-gcc -m32 -ffreestanding -fno-pie -c Kernel/setup/pic.c -o pic.o
i686-elf-gcc -m32 -ffreestanding -fno-pie -c Kernel/std/stdFunctions.c -o std.o
i686-elf-gcc -m32 -ffreestanding -fno-pie -c Kernel/interruptHandler/handlers.c -o handlers.o
i686-elf-gcc -m32 -ffreestanding -fno-pie -c Kernel/drivers/keyboard.c -o keyboard.o


i686-elf-ld -T linker.ld --oformat binary -o kernel.bin kernel.o irq.o kernel_entry.o idt.o pic.o std.o handlers.o keyboard.o




cat boot.bin > os-image.bin

cat kernel.bin >> os-image.bin

qemu-system-i386 -drive format=raw,file=os-image.bin