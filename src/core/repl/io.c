


#include <stdio.h>
#include <stdlib.h>

#include "repl/io.h"




int print_sexpr( top_t* sexpr ) {
    if ( sexpr == NULL ) {
        printf( "()" );
        return 0;
    }

    switch (LANG_TYPE(sexpr)) {
    case LANG_T_ATOM:
        switch (ATOM_TYPE(sexpr)) {
        case ATOM_T_SYMBOL:
            printf( "%s", ((atom_t*)sexpr)->data.as_symbol->name );
            break;
        case ATOM_T_NUMBER:
            printf( "%lu", ((atom_t*)sexpr)->data.as_number );
            break;
        case ATOM_T_UNIT:
        case ATOM_T_POINTER:
        default:
            break;
        }
        break;
    case LANG_T_CONS:
        printf("(");
        print_sexpr( car( sexpr ));
        printf( " . " );
        print_sexpr( cdr( sexpr ));
        printf(")");
        break;
    case LANG_T_TOP:
    default:
        break;
    }
    return 0;
}


char* read_sexpr( void ) {
    static char* buffer = NULL;
    if ( buffer == NULL )
        buffer = malloc( READ_BUFFER + 1);

    for (int i = 0; i < READ_BUFFER + 1; i++ )
        buffer[i] = 0x0;

    fgets( buffer, READ_BUFFER, stdin );

    buffer[READ_BUFFER] = '\0';
    return buffer;
}
