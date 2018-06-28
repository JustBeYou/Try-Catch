#include <setjmp.h>
#include <stdint.h>
#include <stddef.h>

#include "exceptions.h"

// this will become dynamic in future versions
jmp_buf g_jmpBufferStack[DEFAULT_JMP_BUFFER_STACK_SIZE];
size_t  g_jmpCounter;

void exceptions_init() {

}

jmp_buf *exceptions_getCurrentJmpBuffer() {
    return &g_jmpBufferStack[g_jmpCounter];
}

jmp_buf *exceptions_getNewJmpBuffer() {
    ++g_jmpCounter;
    return exceptions_getCurrentJmpBuffer();
}

void exceptions_destroyJmpBuffer() {
    --g_jmpCounter;
}
