#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_JMP_BUFFER_STACK_SIZE 512

/*
 * Try statement is used to execute a block of instructions until an exception
 * is raisen. The block could not contain any catch or finnaly statement,
 * the default behaviour is to end the block and ignore the exception.
 * In that case there is no guarantee that there won't be any runtime error.
 * Instruction block should be surrounded by brackets.
 * Add catch/finally statements only at the end of the block,
 * don't mix up things!
 * Example
 
 try( {
        int x = 123;
        int y = some_call(x);

        printf ("%d\n", y);
        
        catch ( SOME_EXCEPTION, {
            handle_some_call();
        } );
        finally ( { -> this would not be implemented soon
            printf ("DONE\n");
        } );
    }
 );

 */
#define try(block) \
    jmp_buf *currentBuf = exceptions_getNewJmpBuf(); \
    \
    int exceptionHandlerNo = setjmp(*currentBuf); \
    switch (exceptionHandlerNo) { \
        case 0: \
        block \
        break; \
        default: \
            exceptions_defaultHandler(exceptionHandlerNo); \
    } \
    exceptions_destroyJmpBuf();

/*
 *
 */
#define catch(exception, block) \
    break; \
    case exception: \
        block

/*
 * This would not be implemented soon. 
 */
#define finally(block)

/*
 * 
 */
#define throw(exception) \
    longjmp(*exceptions_getCurrentJmpBuf(), exception);



// TODO: should be dynamic
#define EXCEPTION_NAME_LEN 128
#define EXCEPTION_MSG_LEN 512

typedef struct {
    char name[EXCEPTION_NAME_LEN];
    char msg[EXCEPTION_MSG_LEN];
    void *data;
} Exception;

#define DECL_EXCEPTION(exception_name) \
    static Exception exception_name(const char *msg) { \
        Exception e; \
        strncpy(e.name, #exception_name , EXCEPTION_NAME_LEN); \
        strncpy(e.msg, msg, EXCEPTION_MSG_LEN); \
        e.data = NULL; \
        return e; \
    }

DECL_EXCEPTION(DefaultException)

/*
 *
 */
void exceptions_init();

/*
 *
 */
jmp_buf *exceptions_getCurrentJmpBuf();

/*
 *
 */
jmp_buf *exceptions_getNewJmpBuf();

/*
 *
 */
void exceptions_destroyJmpBuf();

/*
 *
 */
size_t exceptions_getCurrentCounter();

/*
 *
 */
jmp_buf *exceptions_getJmpBufAt(size_t p_index);

/*
 *
 */
void exceptions_defaultHandler(int p_exception);

#endif // EXCEPTIONS_H
