

#include "lang/functions/evalquote.h"
#include "lang/functions/elementary.h"
#include "lang/functions/auxiliary.h"

/*
*/


top_t* evalquote(top_t* fn, top_t* x) {
    return apply(fn, x, NULL);
}

top_t* apply(top_t* fn, top_t* x, top_t* a) {
    if (atom( fn )) {
        if (atom_symbol_compare_string( fn, "CAR" )) {
            return caar(x);
        }
        if (atom_symbol_compare_string( fn, "CDR" )) {
            return cdar(x);
        }
        if (atom_symbol_compare_string( fn, "CONS" )) {
            return cons(car(x), cadr(x));
        }
        if (atom_symbol_compare_string( fn, "ATOM" )) {
            return atom(car(x));
        }
        if (atom_symbol_compare_string( fn, "EQ" )) {
            return eq(car(x), cadr(x));
        }
        return apply( eval(fn, a), x, a );
    }
    if (atom_symbol_compare_string( car(fn), "LAMBDA" )) {
        return eval(caddr(fn), parlis(cadr(fn), x, a));
    }
    if (atom_symbol_compare_string( car(fn), "LABEL" )) {
        return apply(caddr(fn), x, cons(cons(cadr(fn), caddr(fn)), a));
    }
    return NULL;
}

top_t* eval(top_t* e, top_t* a) {
    if ( atom(e) )
        return cdr(assoc(e,a));
    top_t* e_car = car(e);
    if (atom(e_car)) {
        if (atom_symbol_compare_string(e_car, "QUOTE")) {
            return cadr(e);
        }
        if (atom_symbol_compare_string(e_car, "COND")) {
            return evcon(cdr(e), a);
        }
    }
    return apply( e_car, evlis(cdr(e), a), a);
}

top_t* evcon(top_t* c, top_t* a) {
    if (eval(caar(c), a))
        return eval(cadar(c),a);
    return evcon(cdr(c), a);
}

top_t* evlis(top_t* m, top_t* a ) {
    if (null(m))
        return NULL;
    return cons(eval(car(m), a), evlis(cdr(m), a));
}
