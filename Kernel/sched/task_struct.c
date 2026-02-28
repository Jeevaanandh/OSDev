
#include <stdint.h>
#include "task_struct.h"



int task_count=0;
task_struct tasks[2];
void createTask(void (*taskEntry)()) {
    task_struct *t= &tasks[task_count];

    //Every task gets its own Stack Region.
    uint32_t *stack_top= &t->stack[1024];

    *(--stack_top)= 0x202;
    *(--stack_top)= 0x08;
    *(--stack_top)= (uint32_t)taskEntry;  //This is the EIP (Instruction Pointer)

    //Register values
    for (int i=0; i<8; i++) {
        *(--stack_top)=0;
    }

    t->ESP= (uint32_t)stack_top;
    task_count++;

}