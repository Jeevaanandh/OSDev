//
// Created by Jeevaanandh Ilayaraja on 28/02/26.
//

#ifndef OSDEV_TASK_STRUCT_H
#define OSDEV_TASK_STRUCT_H
#include <stdint.h>
typedef struct {
    uint32_t ESP;
    uint32_t stack[1024];
} task_struct;


extern int task_count;
extern task_struct tasks[2];

void createTask(void (*taskEntry)());
#endif //OSDEV_TASK_STRUCT_H