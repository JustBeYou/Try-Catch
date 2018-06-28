#include <stdio.h>

#include "exceptions.h"

int main() {
    exceptions_init();
    
    try( 
    {
      printf("Empty try\n");
    }
    );

    throw(123);

    printf("test\n");

    return 0;
}
