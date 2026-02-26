cmake_minimum_required(VERSION 3.27)
project(OSDev C ASM)

set(CMAKE_C_STANDARD 11)

include_directories(
        Kernel
        Kernel/drivers
        Kernel/setup
        Kernel/std
        Kernel/interruptHandler
)

file(GLOB_RECURSE C_FILES
        Kernel/*.c
)

add_executable(dummy ${C_FILES}
        Kernel/InlineAssembly/inline.h)