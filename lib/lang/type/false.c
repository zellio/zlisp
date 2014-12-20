#include "lang/type/false.h"

object_t *ZLC_FALSE = &(object_t) {
    .type = TYPE_FALSE,
    .comparator = NULL,
    .destructor = NULL,
    .to_string = &false_to_string
};

object_t *false_create(void)
{
    return ZLC_FALSE;
}

char *false_to_string(object_t *self)
{
    char *str = strndup("false", 5);
    return str;
}
