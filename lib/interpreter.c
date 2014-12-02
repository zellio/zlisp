#include "interpreter.h"

object_t *SYM_LIST;

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
        if (is_builtin(operator) && operator->builtin.special)
            return apply(operator, pair_cdr(expr), env);
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

#define ZLI_FN(label) object_t *zli_ ## label(object_t *args, object_t *env)

ZLI_FN(quote)
{
    return pair_car(args);
}

ZLI_FN(cons)
{
    return pair_create(pair_car(args), pair_cadr(args));
}

ZLI_FN(car)
{
    return pair_caar(args);
}

ZLI_FN(cdr)
{
    return pair_cdar(args);
}

ZLI_FN(if)
{
    if (is_false(eval(pair_car(args), env)))
        return eval(pair_caddr(args), env);
    return eval(pair_cadr(args), env);
}

ZLI_FN(let)
{
    object_t *bindings = pair_car(args);
    object_t *body = pair_cadr(args);

    for (object_t **b = &bindings; is_pair(*b); b = &pair_cdr(*b))
        env = zlc_acons(pair_caar(*b), eval(pair_cadar(bindings) ,env), env);

    return eval(body, env);
}

ZLI_FN(begin)
{
    object_t **e = &args;
    for (; !is_nil(pair_cdr(*e)); e = &pair_cdr(*e))
        eval(pair_car(*e), env);

    return eval(pair_cdr(*e), env);
}
