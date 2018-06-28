#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdbool.h>

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
        finally ( {
            printf ("DONE\n");
        } );
    }
 );

 */
#define try(block) \
    block

/*
 *
 */
#define catch(exception, block)

/*
 * 
 */
#define finally(block)

/*
 *
 */
void exceptions_init();

/*
 *
 */
jmp_buf *exceptions_getCurrentJmpBuffer();

/*
 *
 */
jmp_buf *exceptions_getNewJmpBuffer();

/*
 *
 */
void exceptions_destroyJmpBuffer();

#endif // EXCEPTIONS_H
