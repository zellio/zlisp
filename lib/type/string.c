#include "type/string.h"

#include <string.h>


object_t *string_create(char *value) {
    object_t *string = object_create(SCHEME_TYPE_STRING);
    if (string == NULL)
        error("Out of memory error in `string_create`");

    size_t size = strlen(value);

    string->as.string.value = calloc(size + 1, 1);
    if (string->as.string.value == NULL)
        error("Memory allocation error in `string_create`");

    strncpy(string->as.string.value, value, size);

    string->as.string.length = size;

    string->comperator = &string_comperator;
    string->destructor = &string_destructor;
    string->to_string = &string_to_string;

    return string;
}

int string_destructor(object_t *self) {
    if (self->as.string.value == NULL)
        return -1;

    free(self->as.string.value);

    return 0;
}

int string_comperator(object_t *self, object_t *other) {
    char *s_val = self->as.string.value;
    size_t s_len = self->as.string.length;

    char *o_val = other->as.string.value;
    size_t o_len = other->as.string.length;

    int32_t val;
    while (s_len && o_len) {
        val = s_val[s_len] - o_val[o_len];

        if (val != 0)
            return val;

        s_len--; o_len--;
    }

    return s_len - o_len;
}

char *string_to_string(object_t *self) {
    size_t length = self->as.string.length + 1;
    char *str = calloc(length, 1);

    strncpy(str, self->as.string.value, length);

    return str;
}
