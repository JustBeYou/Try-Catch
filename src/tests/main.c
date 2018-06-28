#include <stdio.h>

#include "exceptions.h"

int main() {
    try( 
    {
      printf("Empty try\n");  
    }
    );

    printf("test\n");

    return 0;
}
