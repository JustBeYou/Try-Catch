#include <stdlib.h>
#include <string.h>

#include "exceptions.h"
#include "catch.h"


CatchTable g_catchTablesStack[DEFAULT_CATCH_TABLES_NUM];
size_t g_catchCounter;

size_t catch_getNewCatchTable() {
    ++g_catchCounter; 
    g_catchTablesStack[g_catchCounter].table = NULL;
    g_catchTablesStack[g_catchCounter].catchCount = 0;

    return g_catchCounter;
}

size_t catch_getCurrentCounter() {
    return g_catchCounter;
}

void catch_destroyCurrentTable() {
    CatchElement *table = g_catchTablesStack[g_catchCounter--].table;

    while (table != NULL) {
        CatchElement *next = table->next;
        free(table);
        table = next;
    }
}

size_t catch_getExceptionId(Exception *p_exception) {
    if (p_exception == NULL) return 0;
    
    CatchElement *table = g_catchTablesStack[g_catchCounter].table;
    size_t id = 1; 

    while (table != NULL) {
        if (!strcmp(p_exception->name, table->e.name)) {
            return id;
        }

        id++;
        table = table->next;
    }

    return EXCEPTION_NOT_HANDLED;
}

void catch_registerException(Exception *p_exception) {
    CatchElement *table = g_catchTablesStack[g_catchCounter].table;
    CatchElement *new = malloc(sizeof(CatchElement));

    new->id = ++g_catchTablesStack[g_catchCounter].catchCount;
    memcpy(&new->e, p_exception, sizeof(Exception));
    new->next = table;

    g_catchTablesStack[g_catchCounter].table = new;
}

Exception *catch_getThrownException() {
    return &g_catchTablesStack[g_catchCounter].thrown;
}

void catch_throwException(Exception *p_exception) {
    memcpy(&g_catchTablesStack[g_catchCounter].thrown, p_exception, sizeof(Exception));
}

size_t catch_getCurrentTableCatchCount() {
    return g_catchTablesStack[g_catchCounter].catchCount;
}
