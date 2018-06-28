#include "exceptions.h"
#include <stdio.h>
#include <stdlib.h>

// this will become dynamic in future versions
// index 0 is reserved for unhandled exceptions outside try statements
jmp_buf g_jmpBufStack[DEFAULT_JMP_BUFFER_STACK_SIZE];
size_t  g_jmpCounter;

void exceptions_init() {
   int unhandledThrow = setjmp(g_jmpBufStack[0]);
   if (unhandledThrow) {
        exceptions_defaultHandler(unhandledThrow);
   }
}

jmp_buf *exceptions_getCurrentJmpBuf() {
    return &g_jmpBufStack[g_jmpCounter];
}

jmp_buf *exceptions_getNewJmpBuf() {
    ++g_jmpCounter;
    return exceptions_getCurrentJmpBuf();
}

void exceptions_destroyJmpBuf() {
    --g_jmpCounter;
}

size_t exceptions_getCurrentCounter() {
    return g_jmpCounter;
}

jmp_buf *exceptions_getJmpBufAt(size_t p_index) {
    return &g_jmpBufStack[p_index];
}

void exceptions_defaultHandler(int p_exception) {
    printf("[EXCEPTION] Unhandled %d\n", p_exception);
    exit(p_exception);
}
