

#include "lang/functions/elementary.h"
#include "lang/functions/auxiliary.h"


top_t* parlis(top_t* x, top_t* y, top_t* a) {
    if ( C_BOOLEAN(null(x)) )
        return a;
    return cons(cons(car(x),car(y)),parlis(cdr(x),cdr(y),a));
}

top_t* assoc(top_t* x, top_t* a) {
    if ( C_BOOLEAN(equal(caar(a), x)) )
        return car(a);
    return assoc(x, cdr(a));
}

top_t* null(top_t* sexpr) {
    return L_BOOLEAN(sexpr == FALSE);
}

top_t* equal(top_t* x, top_t* y) {
    if ( C_BOOLEAN(atom(x)) )
        return eq(x, y);
    if (equal(car(x), car(y)))
        return equal(cdr(x), cdr(y));
    return FALSE;
}
