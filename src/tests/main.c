#include <stdio.h>

#include "exceptions.h"

#define TEST_EXCEPTION 123

int main() {
    exceptions_init();
    
    try( 
    {
      printf("The try starts here\n");

      throw(TEST_EXCEPTION);

      printf("Should not arrive here...\n");

      catch(TEST_EXCEPTION, 
        {
            printf("Gotcha!\n");
        }
      );
    }
    );

    throw(TEST_EXCEPTION);

    printf("Neither here\n");

    return 0;
}
