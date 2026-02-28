//
// Created by Jeevaanandh Ilayaraja on 26/02/26.
//

#ifndef OSDEV_INLINE_H
#define OSDEV_INLINE_H

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0"
                      : "=a"(ret)
                      : "Nd"(port)
                      : "memory");
    return ret;
}

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1"
                      :
                      : "a"(val), "Nd"(port)
                      : "memory");
}



//insw can read 1 word (2B= 16bits) at a time. But, it can read it multiple times using count.
// So, count= 256 => 512B
static inline void insw(uint16_t port, void *addr, uint32_t count)
{
    __asm__ volatile (
        "rep insw"
        : "+D"(addr), "+c"(count)
        : "d"(port)
        : "memory"
    );
}


static inline void sti() {
    asm volatile("sti");
}




#endif //OSDEV_INLINE_H