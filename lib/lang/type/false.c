#include "lang/type/false.h"

object_t *false_create(void)
{
    static object_t *obj = NULL;

    if (obj == NULL) {
        obj = object_create(TYPE_FALSE);
        if (obj == NULL)
            error("Out of memeory error in `create_false`");

        obj->to_string = &false_to_string;
    }

    return obj;
}

char *false_to_string(object_t *self)
{
    char *str = strndup("false", 5);
    return str;
}
