#include <stdio.h>

#include "stdexcept.h"

DECL_EXCEPTION(TestException);

int main() {
    exceptions_init();
    
    try( 
    {
      printf("The try starts here\n");

      throw(TestException("This is a test", NULL));

      printf("Should not arrive here...\n");

    }
    );

    printf("Neither here\n");

    return 0;
}
