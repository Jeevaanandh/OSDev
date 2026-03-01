//
// Created by Jeevaanandh Ilayaraja on 28/02/26.
//

#include "task_struct.h"


/*
 *We use the ESP (Stack Pointer) value to context switch.
 *When a timer interrupt occurs, we save the current running task's ESP in that tasks task_struct
 *Then, the scheduler picks the next task ----- the CPU's ESP is is loaded with that tasks ESP value. (THIS IS CONTEXT SWITCH)

*/




//inline assembly to do: mov esp, current_task->ESP
void save_esp(task_struct *current_task) {
    asm volatile(
        "mov %%esp, %0"
        :"=r"(current_task->ESP)
        );
}



// inline assembly to do: mov current_task->ESP, esp
void load_esp(task_struct *current_task) {
    asm volatile(
        "mov %0, %%esp"
        :
        :"r"(current_task->ESP)
        );
}



//This is important. Update this when you pick the next task to execute.
int current_task=-1;
uint32_t schedule(uint32_t current_esp) {

    if (task_count == 0)
        return current_esp;

    if (current_task >= 0)
        tasks[current_task].ESP = current_esp;

    current_task = (current_task + 1) % task_count;


    return tasks[current_task].ESP;
}


//This is to pick the task that was executed the least amount of times. There is still a slight bias.
uint32_t schedule2(uint32_t current_esp) {
    if (task_count == 0) {
        return current_esp;

    }

    if (current_task>=0) {
        tasks[current_task].ESP = current_esp;
        tasks[current_task].time_executed+=1;
    }

    int task_to_execute=-1;
    int least_time_executed= 1000000000;
    for (int i=0; i<task_count; i++) {
        if (tasks[i].time_executed<least_time_executed) {
            task_to_execute=i;
            least_time_executed=tasks[i].time_executed;
        }
    }

    current_task= task_to_execute;
    return tasks[task_to_execute].ESP;

}