#include "lang/type/true.h"

object_t *true_create(void)
{
    return ZLC_TRUE;
}

char *true_to_string(object_t *self)
{
    char *str = strndup("true", 4);
    return str;
}
