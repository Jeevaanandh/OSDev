//
// Created by Jeevaanandh Ilayaraja on 28/02/26.
//

#include "task_struct.h"


/*
 *We use the ESP (Stack Pointer) value to context switch.
 *When a timer interrupt occurs, we save the current running task's ESP in that tasks task_struct
 *Then, the scheduler picks the next task ----- the CPU's ESP is is loaded with that tasks ESP value. (THIS IS CONTEXT SWITCH)

*/


void save_esp(task_struct *current_task) {
    asm volatile(
        "mov %%esp, %0"
        :"=r"(current_task->ESP)
        );
}



void load_esp(task_struct *current_task) {
    asm volatile(
        "mov %0, %%esp"
        :
        :"r"(current_task->ESP)
        );
}

int current_task=-1;
uint32_t schedule(uint32_t current_esp) {

    if (task_count == 0)
        return current_esp;

    if (current_task >= 0)
        tasks[current_task].ESP = current_esp;

    current_task = (current_task + 1) % task_count;


    return tasks[current_task].ESP;
}