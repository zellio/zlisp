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

        for (object_t **p = &params;
             is_pair(*p) && is_pair(vals);
             p = &pair_cdr(*p), vals = pair_cdr(vals)) {
            env = zlc_acons(pair_car(*p), pair_car(vals), env);
            ;
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

    return eval(pair_car(*e), env);
}

ZLI_FN(lambda)
{
    object_t *params = pair_car(args);
    object_t *body = pair_cdr(args);

    if (!is_nil(pair_cdr(body))) {
        body = pair_create(intern("begin"), body);
    }
    else {
        body = pair_car(body);
    }

    return closure_create(params, body, env);
}

object_t *init_env(void)
{
    SYM_LIST = ZLC_NIL;

    object_t *env = ZLC_NIL;

    env = zlc_acons(intern("nil"), ZLC_NIL, env);
    env = zlc_acons(intern("#t"), ZLC_TRUE, env);
    env = zlc_acons(intern("#f"), ZLC_FALSE, env);
    env = zlc_acons(intern("quote"), builtin_create_s(&zli_quote), env);
    env = zlc_acons(intern("cons"), builtin_create(&zli_cons), env);
    env = zlc_acons(intern("car"), builtin_create(&zli_car), env);
    env = zlc_acons(intern("cdr"), builtin_create(&zli_cdr), env);
    env = zlc_acons(intern("if"), builtin_create_s(&zli_if), env);
    env = zlc_acons(intern("let"), builtin_create_s(&zli_let), env);
    env = zlc_acons(intern("begin"), builtin_create_s(&zli_begin), env);
    env = zlc_acons(intern("lambda"), builtin_create_s(&zli_lambda), env);

    return env;
}

int main(void)
{
    object_t *env = init_env();
    object_t *ast = NULL;

    printf("*** Testing parser ***\n");

    zlisp_parse("asdf", &ast);
    printf("asdf parses as %s\n", object_to_string(ast));

    zlisp_parse("\"ASDF\"", &ast);
    printf("\"ASDF\" parses as %s\n", object_to_string(ast));

    zlisp_parse("-1234", &ast);
    printf("-1234 parses as %s\n", object_to_string(ast));

    zlisp_parse("-1432.2523", &ast);
    printf("-1432.2523 parses as %s\n", object_to_string(ast));

    zlisp_parse("()", &ast);
    printf("() parses as %s\n", object_to_string(ast));

    zlisp_parse("(a . b)", &ast);
    printf("(a . b) parses as %s\n", object_to_string(ast));

    zlisp_parse("((a) . (b))", &ast);
    printf("((a) . (b)) parses as %s\n", object_to_string(ast));

    zlisp_parse("(a b c)", &ast);
    printf("(a b c) parses as %s\n", object_to_string(ast));

    zlisp_parse("(a (a b (a b c)) ((a b) . c))", &ast);
    printf("(a (a b (a b c)) ((a b) . c)) parses as %s\n", object_to_string(ast));

    printf("\n");
    printf("*** Testing interpreter ***\n");

    zlisp_parse("nil", &ast);
    printf("nil evals to %s\n", object_to_string(eval(ast, env)));

    zlisp_parse("#t", &ast);
    printf("#t evals to %s\n", object_to_string(eval(ast, env)));

    zlisp_parse("#f", &ast);
    printf("#f evals to %s\n", object_to_string(eval(ast, env)));

    zlisp_parse("-1334", &ast);
    printf("-1334 evals to %s\n", object_to_string(eval(ast, env)));

    zlisp_parse("-1334.2425", &ast);
    printf("-1334.2425 evals to %s\n", object_to_string(eval(ast, env)));

    zlisp_parse("(quote a)", &ast);
    printf("(quote a) evals to %s\n", object_to_string(eval(ast, env)));

    zlisp_parse("(cons 1 2)", &ast);
    printf("(cons 1 2) evals to %s\n", object_to_string(eval(ast, env)));

    zlisp_parse("(if #t 1 2)", &ast);
    printf("(if #t 1 2) evals to %s\n", object_to_string(eval(ast, env)));

    zlisp_parse("(if #f 1 2)", &ast);
    printf("(if #f 1 2) evals to %s\n", object_to_string(eval(ast, env)));

    zlisp_parse("(let ((x 1)) (cons x x))", &ast);
    printf("(let ((x 1)) (cons x x)) evals to %s\n", object_to_string(eval(ast, env)));

    zlisp_parse("(begin (cons 1 2) (cons 2 3))", &ast);
    printf("(begin (cons 1 2) (cons 2 3)) evals to %s\n", object_to_string(eval(ast, env)));

    zlisp_parse("((lambda (x y) (cons x y)) 1 2)", &ast);
    printf("((lambda (x y) (cons x y)) 1 2) evals to %s\n", object_to_string(eval(ast, env)));

    zlisp_parse("((lambda (x y) (cons x y)) 1 2)", &ast);
    printf("((lambda (x y) (cons x y)) 1 2) evals to %s\n", object_to_string(eval(ast, env)));

    zlisp_parse("((let ((x 1)) (lambda (y) (cons x y))) 2)", &ast);
    printf("((let ((x 1)) (lambda (y) (cons x y))) 2) evals to %s\n", object_to_string(eval(ast, env)));


    env = zlc_acons(intern("lambda"), builtin_create_s(&zli_lambda), env);


    return 0;
}
