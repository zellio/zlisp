


#include "lang/types/cons.h"
#include <stdlib.h>

top_t* cons_create(top_t* car, top_t* cdr) {
    cons_t* cons = calloc(1, sizeof( cons_t ));
    if ( cons == NULL )
        return NULL;
    cons->car = car;
    cons->cdr = cdr;
    cons->type = LANG_T_CONS;
    return (top_t*)cons;
}

int cons_destroy(cons_t* cons) {
    if ( cons != NULL )
        free( cons );
    return 0;
}
