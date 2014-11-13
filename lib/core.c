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

// object_t *extend_global_env(object_t *key, object_t *val) {
//     pair_set_cdr(global_env, cons(cons(key, val), cdr(global_env)));
//     return val;
// }

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
        tmp = assoc(env, expr);
        if (is_nil(tmp))
            error("Unbound symbol");
        return cdr(tmp);

    case SCHEME_TYPE_PAIR:
        tmp = eval(car(expr), env);
        if (is_special(tmp))
            return apply(tmp, cdr(expr), env);
        return apply(tmp, evlist(cdr(expr), env), env);

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

ZEME_FN(quote) {
    return car(args);
}

ZEME_FN(cons) {
    return pair_create(car(args), car(cdr(args)));
}

ZEME_FN(begin) {
    object_t *exprs = args;
    while (!is_nil(cdr(exprs))) {
        eval(car(exprs), env);
        exprs = cdr(exprs);
    }
    return eval(car(exprs), env);
}

ZEME_FN(let) {
    object_t *bindings = car(args);
    object_t *form = car(cdr(args));

    while (!is_nil(bindings)) {
        env = extend(env, car(car(bindings)), eval(car(cdr(car(bindings))), env));
        bindings = cdr(bindings);
    }

    return eval(form, env);
}

ZEME_FN(car) {
    return car(car(args));
}

ZEME_FN(cdr) {
    return cdr(car(args));
}

object_t *init_env(void) {

    nil = nil_create();
    sym_list = nil;

    intern("nil");

    object_t *env = nil;

    env = extend(env, intern("nil"), nil);
    env = extend(env, intern("#t"), true_create());
    env = extend(env, intern("#f"), false_create());
    env = extend(env, intern("quote"), builtin_create_special(&zeme_fn_quote));
    env = extend(env, intern("cons"), builtin_create(&zeme_fn_cons));
    env = extend(env, intern("car"), builtin_create(zeme_fn_car));
    env = extend(env, intern("cdr"), builtin_create(zeme_fn_cdr));
    env = extend(env, intern("if"), builtin_create_special(&zeme_fn_if));
    env = extend(env, intern("let"), builtin_create_special(&zeme_fn_let));
    env = extend(env, intern("begin"), builtin_create_special(&zeme_fn_begin));

    return env;
}

int main(void) {
    object_t *env = init_env();

    object_t *quote_stmt = cons(intern("quote"), cons(intern("foo"), nil));

    fprintf(stdout, "%s\n", object_to_string(quote_stmt));
    fprintf(stdout, "%s\n", object_to_string(eval(quote_stmt, env)));

    object_t *cons_stmt = cons(intern("cons"),
                                   cons(quote_stmt,
                                        cons(cons(intern("quote"), cons(intern("bar"), nil)), nil)));

    fprintf(stdout, "%s\n", object_to_string(cons_stmt));
    fprintf(stdout, "%s\n", object_to_string(eval(cons_stmt, env)));

    object_t *car_stmt = cons(intern("car"), cons(cons_stmt, nil));

    fprintf(stdout, "%s\n", object_to_string(car_stmt));
    fprintf(stdout, "%s\n", object_to_string(eval(car_stmt, env)));

    object_t *cdr_stmt = cons(intern("cdr"), cons(cons_stmt, nil));

    fprintf(stdout, "%s\n", object_to_string(cdr_stmt));
    fprintf(stdout, "%s\n", object_to_string(eval(cdr_stmt, env)));

    object_t *if_stmt = cons(intern("if"),
                                  cons(intern("#f"),
                                       cons(quote_stmt,
                                            cons(cons(intern("quote"), cons(intern("bar"), nil)), nil))));

    fprintf(stdout, "%s\n", object_to_string(if_stmt));
    fprintf(stdout, "%s\n", object_to_string(eval(if_stmt, env)));

    object_t *let_stmt = cons(intern("let"),
                              cons(cons(cons(intern("x"), cons(fixnum_create(1), nil)),
                                        cons(cons(intern("y"), cons(fixnum_create(2), nil)), nil)),
                                   cons(cons(intern("cons"),
                                             cons(intern("x"),
                                                  cons(intern("y"), nil))), nil)));
    fprintf(stdout, "%s\n", object_to_string(let_stmt));
    fprintf(stdout, "%s\n", object_to_string(eval(let_stmt, env)));

    object_t *begin_stmt = cons(intern("begin"), cons(if_stmt, cons(quote_stmt, cons(cons_stmt, nil))));
    fprintf(stdout, "%s\n", object_to_string(begin_stmt));
    fprintf(stdout, "%s\n", object_to_string(eval(begin_stmt, env)));


    fprintf(stdout, "%s\n", object_to_string(env));

    return 0;
}
