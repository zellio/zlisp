#include "lang/type/port.h"

object_t *port_create(FILE* stream)
{
    object_t *obj = object_create(TYPE_PORT);
    if (obj == NULL)
        error("Out of memory error in `pair_create`");

    obj->port.value = stream;

    obj->to_string = &port_to_string;

    return obj;
}

char *port_to_string(object_t *self)
{
    return typed_pointer_to_string("Port", 4, self);
}
