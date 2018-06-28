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
 * This header file includes the whole library headers.
 * The try-catch-throw statements are defined here as they are just macros,
 * but their functionality is implemented in separate files
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
 * It receives an exception object and registers it to the catch-table,
 * then it generates a 'case x:' statement using its ID in the table.
 * TODO: remove basic implementation and respect function brief
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
 * This statement generates an exception event using the received object.
 * It checks the catch-table and calls longjmp with the corresponding ID.
 * TODO: remove basic implementation and respect function brief
 */
#define throw(exception) \
    longjmp(*exceptions_getCurrentJmpBuf(), exception);

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
    static Exception exception_name(const char *msg, void *data) { \
        Exception e; \
        strncpy(e.name, #exception_name , EXCEPTION_NAME_LEN); \
        strncpy(e.msg, msg, EXCEPTION_MSG_LEN); \
        e.data = data; \
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
void exceptions_defaultHandler(int p_exception);

#endif // EXCEPTIONS_H
