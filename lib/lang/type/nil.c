#include "lang/type/nil.h"

object_t *nil_create(void)
{
    return ZLC_NIL;
}

char *nil_to_string(object_t *self)
{
    char *str = strndup("nil", 3);
    return str;
}
