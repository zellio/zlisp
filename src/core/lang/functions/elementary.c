

#include "lang/functions/elementary.h"


top_t* cons(top_t* car, top_t* cdr) {
    return cons_create(car, cdr);
}

top_t* car(top_t* sexpr) {
    if ( LANG_TYPE(sexpr) != LANG_T_CONS )
        return FALSE;
    return ((cons_t*)sexpr)->car;
}

top_t* cdr(top_t* sexpr) {
    if ( LANG_TYPE(sexpr) != LANG_T_CONS )
        return FALSE;
    return ((cons_t*)sexpr)->cdr;
}

top_t* eq(top_t* l, top_t* r) {
    if ( LANG_TYPE(l) != LANG_T_ATOM || LANG_TYPE(r) != LANG_T_ATOM )
        return FALSE;
    return L_BOOLEAN(atom_compare((atom_t*)l, (atom_t*)r));
}

top_t* atom(top_t* sexpr) {
    return L_BOOLEAN( LANG_TYPE(sexpr) == LANG_T_ATOM );
}

top_t* caar(top_t* sexpr) {
    return car(car(sexpr));
}

top_t* cdar(top_t* sexpr) {
    return cdr(car(sexpr));
}

top_t* cadr(top_t* sexpr) {
    return car(cdr(sexpr));
}

top_t* caddr(top_t* sexpr) {
    return car(cdr(cdr(sexpr)));
}
top_t* cadar(top_t* sexpr) {
    return car(cdr(car(sexpr)));
}
