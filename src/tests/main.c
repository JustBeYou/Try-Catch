#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "stdexcept.h"

DECL_EXCEPTION(NullPointer);
DECL_EXCEPTION(ValueError);
DECL_EXCEPTION(GenericError);

int main() {
    exceptions_init();
    
    try( 
        {
            // TODO:this should not be called manually (BUG)
            catch_registerException(NullPointer(NULL, NULL));
            catch_registerException(ValueError(NULL, NULL));
            catch_registerException(GenericError(NULL, NULL));
            
            srand(time(NULL));
            int val = rand() % 100;
            char *s = NULL;

            if (val > 70) {
                throw(ValueError("The generated value is too big", NULL));
            } else if (val % 2 == 0){
                s = malloc(512);
            }

            if (s != NULL) free(s);
            else throw(NullPointer("The pointer that needs to be freed is NULL", NULL));

            if (val < 20) {
                throw(GenericError("I just came here to blow your mind", NULL));
            }
        }

        catch( NullPointer(NULL, NULL),
            {
                Exception *e = catch_getThrownException();
                printf("We should alloc some memory (%s|%s)\n", e->name, e->msg);
            }
        )

        catch( ValueError(NULL, NULL), 
            {
                Exception *e = catch_getThrownException();
                printf("Hoooooold on (%s|%s)\n", e->name, e->msg);
            }
        )

        catch( GenericError(NULL, NULL),
            {
                printf("This just does not matter\n");
            }
        )
    );

    throw(GenericError("DONE!", NULL));

    return 0;
}
