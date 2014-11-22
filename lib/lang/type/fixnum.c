#include "lang/type/fixnum.h"

#include <math.h>

object_t *fixnum_create(int64_t value)
{
    object_t *obj = object_create(TYPE_FIXNUM);
    if (obj == NULL)
        error("Out of memory error in `fixnum_create`");

    obj->as.fixnum.value = value;

    obj->comperator = &fixnum_comperator;
    obj->to_string = &fixnum_to_string;

    return obj;
}

int fixnum_comperator(object_t *self, object_t *other)
{
    return self->as.fixnum.value - other->as.fixnum.value;
}

#define cint_to_char(x) ((x) + 0x30)

char *fixnum_to_string(object_t *self)
{
    size_t length = 0;
    int64_t value = self->as.fixnum.value;
    uint8_t is_negative = (value < 0);

    length += (size_t)(floor(log10(labs(value))) + 1);

    if (is_negative) {
        length++;
        value = labs(value);
    }

    char *str = calloc(length + 1, 1);

    while (length--) {
        str[length] = cint_to_char(value % 10);
        value = value / 10;
    }

    if (is_negative) {
        str[0] = '-';
    }

    return str;
}
