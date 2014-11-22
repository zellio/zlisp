#include "lang/type/true.h"

object_t *true_create(void)
{
    static object_t *obj = NULL;

    if (obj == NULL) {
        obj = object_create(TYPE_TRUE);
        if (obj == NULL)
            error("Out of memeory error in `create_true`");

        obj->to_string = &true_to_string;
    }

    return obj;
}

char *true_to_string(object_t *self)
{
    char *str = calloc(4, 1);
    strncpy(str, "true", 3);
    return str;
}
