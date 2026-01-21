
#define VGA 0xB8000


void printk(const char *msg) {
    volatile unsigned short *vga = (unsigned short*)VGA;
    
    int i = 0;
    while (msg[i]) {
        vga[i] = (0x0F << 8) | msg[i];
        i++;
    }
}

void kernel_entry() {
    printk("Hello from C kernel!\n Hello again!!!");
    
    while (1);
}
