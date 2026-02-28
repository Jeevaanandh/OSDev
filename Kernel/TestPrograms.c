//
// Created by Jeevaanandh Ilayaraja on 28/02/26.
//

#include <stdbool.h>

#include "std/stdFunctions.h"


void Task1() {
    while (1) {
        printk("A");
        for (volatile int i=0;i<1000000;i++);
    }
}

void Task2() {
    while (1) {
        printk("B");
        for (volatile int i=0;i<1000000;i++);
    }
}



