

#include "lang/functions/elementary.h"
#include "lang/functions/auxiliary.h"
#include "lang/types/boolean.h"


top_t* parlis(top_t* x, top_t* y, top_t* a) {
    if (null(x))
        return a;
    return cons(cons(car(x),car(y)),parlis(cdr(x),cdr(y),a));
}

top_t* assoc(top_t* x, top_t* a) {
    if (equal(caar(a), x))
        return car(a);
    return assoc(x, cdr(a));
}

top_t* null(top_t* sexpr) {
    return AS_BOOLEAN(sexpr == NULL);
}

top_t* equal(top_t* x, top_t* y) {
    if ( atom(x) )
        return eq(x, y);
    if (equal(car(x), car(y)))
        return equal(cdr(x), cdr(y));
    return FALSE;
}
