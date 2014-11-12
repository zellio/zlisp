#include "core.h"

#include <string.h>

object_t *intern(char *label) {
    object_t *sym;

    for (object_t *syms = sym_list; !is_nil(syms); syms = cdr(syms)) {
        sym = car(syms);
        if (!strcmp(label, symbol_label(sym)))
            return sym;
    }

    sym = symbol_create(label);
    sym_list = cons(sym, sym_list);
    return sym;
}

/// ENV

object_t *extend_global_env(object_t *key, object_t *val) {
    pair_set_cdr(global_env, cons(cons(key, val), cdr(global_env)));
    return val;
}

object_t *assoc(object_t *alist, object_t *key) {
    if (is_nil(alist))
        return nil;
    if (!object_compare(car(car(alist)), key))
        return car(alist);
    return assoc(cdr(alist), key);
}

/// EVAL

object_t *eval(object_t *expr, object_t *env) {
    object_t *tmp;

    switch (TYPE(expr)) {
    case SCHEME_TYPE_NIL:
    case SCHEME_TYPE_TRUE:
    case SCHEME_TYPE_FALSE:
    case SCHEME_TYPE_CHARACTER:
    case SCHEME_TYPE_FIXNUM:
    case SCHEME_TYPE_STRING:
    case SCHEME_TYPE_VECTOR:
        return expr;

    case SCHEME_TYPE_SYMBOL:
        tmp = assoc(expr, env);
        if (is_nil(tmp))
            error("Unbound symbol");
        return cdr(tmp);

    case SCHEME_TYPE_PAIR:
        return apply(eval(car(expr), env), evlist(cdr(expr), env), env);

    case SCHEME_TYPE_PORT:
    case SCHEME_TYPE_BUILTIN:
    case SCHEME_TYPE_CLOSURE:
        return expr;
    }
}

object_t *evlist(object_t *exprs, object_t *env) {
    if (exprs == nil)
        return nil;

    return cons(eval(car(exprs), env), evlist(cdr(exprs), env));
}

object_t *apply(object_t *proc, object_t *vals, object_t *env) {
    switch (TYPE(proc)) {
    case SCHEME_TYPE_BUILTIN:
        return (*proc->as.builtin.fn)(vals, env);
    case SCHEME_TYPE_CLOSURE:
        return proc;
    default:
        return NULL;
    }
}

/// SYSOPS

// #define ZEME_FN(label) object_t *zeme_fn_ ## label(object_t *args, object_t* env)

ZEME_FN(if) {
    if (is_false(eval(car(args), env)))
        return eval(car(cdr(cdr(args))), env);
    return eval(car(cdr(args)), env);
}

// ZEME_FN(quote) {
//     return car(args);
// }

// ZEME_FN(car) {
//     return car(car(args));
// }

// ZEME_FN(cdr) {
//     return cdr(car(args));
// }

// ZEME_FN(cons) {
//     return pair_create(car(car(args)), cdr(car(args)));
// }

object_t *init_env(void) {
    nil = nil_create();

    global_env = cons(nil, nil);
    sym_list = cons(nil, nil);

    extend_global_env(intern("nil"), nil);
    extend_global_env(intern("#t"), true_create());
    extend_global_env(intern("#f"), false_create());
    extend_global_env(intern("if"), builtin_create(zeme_fn_if));
    // extend_global_env(intern("quote"), builtin_create(zeme_fn_quote));
    // extend_global_env(intern("car"), builtin_create(zeme_fn_car));
    // extend_global_env(intern("cdr"), builtin_create(zeme_fn_cdr));
    // extend_global_env(intern("cons"), builtin_create(zeme_fn_cons));

    return global_env;
}

int main(void) {
    init_env();
    fprintf(stdout, "%s\n", object_to_string(global_env));
    return 0;
}
