#include "lang/type/real.h"

#include <math.h>

object_t *real_create(double value)
{
    object_t *obj = object_create(TYPE_REAL);
    if (obj == NULL)
        error("Out of memory error in `real_create`");

    obj->real = value;

    obj->comperator = &real_comperator;

    return obj;
}

int real_comperator(object_t *self, object_t *other)
{
    return self->real - other->real;
}
