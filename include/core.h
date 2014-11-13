#ifndef __ZEME_CORE_H__
#define __ZEME_CORE_H__ 1

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

#include <string.h>

object_t *sym_list, *nil, *tee, *eff;

#define car(X) (pair_car((X)))
#define cdr(X) (pair_cdr((X)))
#define cons(X, Y) (pair_create((X), (Y)))
#define symbol_label(X) ((X)->as.symbol.value)

object_t *intern(char *label);

#define extend(ENV, KEY, VAL) (cons(cons((KEY), (VAL)), (ENV)))

object_t *extend_global_env(object_t *key, object_t *val);
object_t *assoc(object_t *alist, object_t *key);

object_t *eval(object_t *expr, object_t *env);
object_t *evlist(object_t *exprs, object_t *env);
object_t *apply(object_t *proc, object_t *vals, object_t *env);

#define ZEME_FN(label) object_t *zeme_fn_ ## label(object_t *args, object_t* env)

// ZEME_FN(if);
// ZEME_FN(quote);

object_t *init_env(void);

// "type/object"

// "type/boolean"

// "type/character"

// "type/fixnum"

// "type/symbol"

// "type/pair"

// "type/string"

// "type/vector"

// "type/port"

// "type/builtin"

// "type/closure"

int main(void);

#ifdef __cplusplus
};
#endif

#endif
