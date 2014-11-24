#include "lang/type/nil.h"

object_t *ZLC_NIL = &(object_t) {
    .type = TYPE_NIL,
    .comperator = NULL,
    .destructor = NULL,
    .to_string = &nil_to_string
};

object_t *nil_create(void)
{
    return ZLC_NIL;
}

char *nil_to_string(object_t *self)
{
    char *str = strndup("nil", 3);
    return str;
}
