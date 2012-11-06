

#include "lang/types/top.h"
#include <stdlib.h>


top_t* top_create(void) {
    top_t* top = calloc(1, sizeof(top_t));
    if ( top == NULL )
        return NULL;
    top->type = LANG_T_TOP;
    return top;
}

int top_destroy(top_t* top) {
    if ( top != NULL )
        free( top );
    return 0;
}
