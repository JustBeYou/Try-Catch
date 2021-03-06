#ifndef CATCH_H
#define CATCH_H

#include <stddef.h>

#include "exceptions.h"

/*
 * It receives an exception object and registers it to the catch-table,
 * then it generates a 'case x:' statement using its ID in the table.
 * TODO: remove basic implementation and respect function brief
 */
#define catch(exception, block) \
    else if (exceptionHandlerNo == catch_getExceptionId(exception)) block

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
    catch_throwException(exception); \
    longjmp(*exceptions_getCurrentJmpBuf(), catch_getExceptionId(catch_getThrownException()));


typedef struct catch_element {
    Exception *e;
    size_t id;
    struct catch_element *next;
} CatchElement;

#define DEFAULT_CATCH_TABLES_NUM 512

typedef struct catch_table {
    CatchElement *table;
    Exception *thrown;
    size_t catchCount;
} CatchTable;

// Searching and insertion should be implemented in an efficient manner TODO

size_t catch_getNewCatchTable();

size_t catch_getCurrentCounter();

void catch_destroyCurrentTable();

size_t catch_getExceptionId(Exception *p_exception);

void catch_registerException(Exception *p_exception);

Exception *catch_getThrownException();

void catch_throwException(Exception *p_exception);

size_t catch_getCurrentTableCatchCount();

#endif // CATCH_H
