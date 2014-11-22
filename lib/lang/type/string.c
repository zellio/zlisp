#include "lang/type/string.h"

object_t *string_create(char *value)
{
    object_t *obj = object_create(TYPE_STRING);
    if (obj == NULL)
        error("Out of memory error in `string_create`");

    size_t size = strlen(value);

    obj->string.value = strndup(value, size);
    if (obj->string.value == NULL)
        error("Memory allocation error in `string_create`");

    obj->string.length = size;

    obj->comperator = &string_comperator;
    obj->destructor = &string_destructor;
    obj->to_string = &string_to_string;

    return obj;
}

int string_destructor(object_t *self)
{
    if (self->string.value == NULL)
        return -1;

    free(self->string.value);

    return 0;
}

int string_comperator(object_t *self, object_t *other)
{
    char *s_val = self->string.value;
    size_t s_len = self->string.length;

    char *o_val = other->string.value;
    size_t o_len = other->string.length;

    int32_t val;
    while (s_len && o_len) {
        val = s_val[s_len] - o_val[o_len];

        if (val != 0)
            return val;

        s_len -= 1;
        o_len -= 1;
    }

    return s_len - o_len;
}

char *string_to_string(object_t *self)
{
    char *str = strdup(self->string.value);
    return str;
}
