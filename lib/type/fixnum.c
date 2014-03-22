#include "type/fixnum.h"

object_t *fixnum_create(int64_t value) {
    object_t *fixnum = object_create(SCHEME_TYPE_FIXNUM);
    if (fixnum == NULL)
        error("Out of memory error in `fixnum_create`");

    fixnum->as.fixnum.value = value;

    fixnum->comperator = &fixnum_comperator;
    fixnum->destructor = &fixnum_destructor;
    fixnum->to_string = &fixnum_to_string;

    return fixnum;
}


int fixnum_destructor(object_t *self) {
    (void)self;
    return 0;
}

int fixnum_comperator(object_t *self, object_t *other) {
    return self->as.fixnum.value - other->as.fixnum.value;
}

#include <math.h>

char *fixnum_to_string(object_t *self) {
    size_t length = 0;
    int64_t value = self->as.fixnum.value;
    uint8_t is_negative = (value < 0);

    length += (size_t)(floor(log10(abs(value))) + 1);

    if (is_negative) {
        length++;
        value = abs(value);
    }

    char *str = calloc(length + 1, 1);

    while (length--) {
        str[length] = value % 10 + 48;
        value = value / 10;
    }

    if (is_negative) {
        str[0] = '-';
    }

    return str;
}