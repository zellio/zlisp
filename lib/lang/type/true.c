#include "lang/type/true.h"

object_t *ZLC_TRUE = &(object_t) {
    .type = TYPE_TRUE,
    .comparator = NULL,
    .destructor = NULL,
    .to_string = &true_to_string
};

object_t *true_create(void)
{
    return ZLC_TRUE;
}

char *true_to_string(object_t *self)
{
    char *str = strndup("true", 4);
    return str;
}
