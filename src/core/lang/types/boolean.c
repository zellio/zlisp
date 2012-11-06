

#include "lang/types/boolean.h"


top_t* boolean_true(void) {
    static top_t* T = NULL;
    if ( T == NULL )
        T = atom_create_symbol("T");
    return T;
}
