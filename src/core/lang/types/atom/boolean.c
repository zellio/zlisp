

#include <stdlib.h>

#include "lang/types/atom/boolean.h"


top_t* boolean_true(void) {
    static top_t* T = NULL;
    if ( T == NULL )
        T = atom_create_symbol("T");
    return T;
}

top_t* boolean_false(void) {
    static top_t* NIL = NULL;
    if ( NIL == NULL )
        NIL = atom_create_symbol("NIL");
    return NIL;
}

int boolean_to_int(top_t* value) {
    return value == TRUE;
}

top_t* int_to_boolean(int value) {
    if ( value )
        return TRUE;
    return FALSE;
}
