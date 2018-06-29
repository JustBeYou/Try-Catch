#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * exceptions.h
 *
 * This header contains declarations for try statement and exceptions.
 */

// TODO: this should be dynamic value
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
    catch_getNewCatchTable(); \
    \
    int exceptionHandlerNo = setjmp(*currentBuf); \
    switch (exceptionHandlerNo) { \
        case 0: \
        block \
        break; \
        default: \
            exceptions_defaultHandler(catch_getThrownException()); \
    } \
    exceptions_destroyJmpBuf(); \
    catch_destroyCurrentTable();

#define EXCEPTION_NOT_HANDLED 0xdeadbeef

// TODO: should be dynamic
#define EXCEPTION_NAME_LEN 128
#define EXCEPTION_MSG_LEN 512

// Exception general structure
typedef struct {
    char name[EXCEPTION_NAME_LEN];
    char msg[EXCEPTION_MSG_LEN];
    void *data;
} Exception;

/*
 * Exception declarator is just a macro that generates a function with the 
 * desired exception name. This function setups an exception object and return
 * it.
 */
#define DECL_EXCEPTION(exception_name) \
    __attribute__((unused)) static Exception *exception_name(const char *msg, void *data) { \
        Exception *e = malloc(sizeof(Exception)); \
        strncpy(e->name, #exception_name , EXCEPTION_NAME_LEN); \
        strncpy(e->msg, msg, EXCEPTION_MSG_LEN); \
        e->data = data; \
        return e; \
    }

// Default test exception
DECL_EXCEPTION(DefaultException)

/*
 * Initialize standard functionality like unexpected exceptions handling.
 */
void exceptions_init();

/*
 *  Returns the current jump buffer. It is the buffer of the current context.
 */
jmp_buf *exceptions_getCurrentJmpBuf();

/*
 *  Generates a new context and returns its buffer.
 */
jmp_buf *exceptions_getNewJmpBuf();

/*
 * End the current context.
 */
void exceptions_destroyJmpBuf();

/*
 * Get the current context ID.
 */
size_t exceptions_getCurrentCounter();

/*
 * Get the context buffer at specified position.
 */
jmp_buf *exceptions_getJmpBufAt(size_t p_index);

/*
 * If there is no try-catch that could handle the exception,
 * this function will be called.
 */
void exceptions_defaultHandler(Exception *p_exception);

#endif // EXCEPTIONS_H
