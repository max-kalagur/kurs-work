#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void checkMemErr( int n_args, ... );

void checkMemErr( int n_args, ... ) {

    register int i;
    void * p;
    va_list ap;

    va_start(ap, n_args);
    for(i = 1; i <= n_args; i++) {
        p = va_arg(ap, void *);
        
        if( p == NULL ) {
            printf("Вибачте за незручності, невистачає пам'яті.\n");
            exit(EXIT_FAILURE);
        }
    }
    
    va_end(ap);
}