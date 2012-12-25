


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
    static int BUFFER_SIZE = 1024;
    static int BUFFER_SCALAR = 10;

    char* buffer = calloc(BUFFER_SIZE, sizeof(char));
    fgets( buffer, BUFFER_SIZE, stdin );

    int scratch_buffer_size;
    char* scratch_buffer;
    while ((buffer[BUFFER_SIZE-2]!='\n')&&(buffer[BUFFER_SIZE-2]!='\0')) {
        scratch_buffer_size = BUFFER_SIZE * BUFFER_SCALAR;
        scratch_buffer = malloc(scratch_buffer_size * sizeof(char));

        int i;
        for ( i = 0; i < BUFFER_SIZE; i++ )
            scratch_buffer[i] = buffer[i];
        for (; i < scratch_buffer_size; i++ )
            scratch_buffer[i] = '\0';

        fgets((scratch_buffer + BUFFER_SIZE) - 1, scratch_buffer_size, stdin);
        free(buffer);

        buffer = scratch_buffer;
        BUFFER_SIZE = scratch_buffer_size;
    }

    return buffer;
}
