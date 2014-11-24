#include "interpreter.h"

object_t *SYM_LIST = &(object_t) { .type = TYPE_NIL };

object_t *intern(char *label)
{
}

object_t *eval(object_t *expr, object_t *env)
{
}

object_t *evlist(object_t *exprs, object_t *env)
{
}

object_t *apply(object_t *proc, object_t *vals, object_t *env)
{
}
