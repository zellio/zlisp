

#include "repl.h"

#include <stdio.h>


int main( void ) {
    char* buffer;
    top_t* ast;

    printf( "Welcome to an amazing lazy LISP REPL\n" );

    while ( 1 ) {
        printf( "* " );
        buffer = read_sexpr();
        ast = eval(parse(buffer), NULL);
        print_sexpr( ast );
        printf("\n");
    }

    return 0;
}
