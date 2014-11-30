#include "interpreter.h"

object_t *SYM_LIST = &(object_t) { .type = TYPE_NIL };

object_t *intern(char *label)
{
    object_t *sym;
    for (object_t **sl = &SYM_LIST; is_pair(*sl); sl = &pair_cdr(*sl)) {
        sym = pair_car(*sl);
        if (!strcmp(label, sym->symbol.value))
            return sym;
    }

    sym = symbol_create(label);
    SYM_LIST = pair_create(sym, SYM_LIST);
    return sym;
}

object_t *eval(object_t *expr, object_t *env)
{
    switch (TYPE(expr)) {
    case TYPE_NIL:
    case TYPE_TRUE:
    case TYPE_FALSE:
    case TYPE_CHARACTER:
    case TYPE_FIXNUM:
    case TYPE_REAL:
    case TYPE_STRING:
    case TYPE_VECTOR:
    case TYPE_PORT:
    case TYPE_BUILTIN:
    case TYPE_CLOSURE:
        return expr;
    case TYPE_SYMBOL: {
        object_t *val_pair = zlc_assoc(expr, env);
        if (is_nil(val_pair))
            error("Unbound symbol");
        return pair_cdr(val_pair);
    }
    case TYPE_PAIR: {
        object_t *operator = eval(pair_car(expr), env);
        return apply(operator, evlist(pair_cdr(expr), env), env);
    }
    }
}

object_t *evlist(object_t *exprs, object_t *env)
{
    if (is_nil(exprs))
        return ZLC_NIL;
    return pair_create(eval(pair_car(exprs), env),
                       evlist(pair_cdr(exprs), env));
}

object_t *apply(object_t *proc, object_t *vals, object_t *env)
{
    switch (TYPE(proc)) {
    case TYPE_BUILTIN:
        return (*proc->builtin.fn)(vals, env);
    case TYPE_CLOSURE: {
        object_t *params = proc->closure.parameters;
        object_t *body = proc->closure.body;
        object_t *env = proc->closure.env;

        for (object_t **p = &params; is_pair(*p); p = &pair_cdr(*p)) {
            env = zlc_acons(pair_car(*p), pair_cdr(vals), env);
            vals = pair_cdr(vals);
        }

        return eval(body, env);
    }
    default:
        error("Proc value cannot be applied");
        return NULL;
    }
}
