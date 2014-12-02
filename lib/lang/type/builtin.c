#include "lang/type/builtin.h"

object_t *builtin_create(object_t *(*fn)(object_t *args, object_t *env))
{
    object_t *obj = object_create(TYPE_BUILTIN);
    if (obj == NULL)
        error("Out of memory error in `pair_create`");

    obj->builtin.fn = fn;

    obj->to_string = &builtin_to_string;

    return obj;
}

object_t *builtin_create_s(object_t *(*fn)(object_t *args, object_t *env))
{
    object_t *obj = builtin_create(fn);
    obj->builtin.special = 1;

    return obj;
}

char *builtin_to_string(object_t *self)
{
    return typed_pointer_to_string("Builtin", 7, self);
}
