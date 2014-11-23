#include "lang/type/vector.h"

object_t *vector_create(size_t length)
{
    object_t *obj = object_create(TYPE_VECTOR);
    if (obj == NULL)
        error("Out of memory error in `vector_create`");

    obj->vector.value = calloc(length, sizeof(object_t*));
    if (obj->vector.value == NULL)
        error("Memory allocation error in `vector_create`");

    obj->vector.length = length;

    obj->destructor = &vector_destructor;
    obj->to_string = &vector_to_string;

    return obj;
}

int vector_destructor(object_t *self)
{
    if (self->vector.value == NULL)
        return -1;

    size_t size = self->vector.length;
    while (size--)
        object_destroy(self->vector.value[size]);

    free(self->vector.value);

    return 0;
}

char *vector_to_string(object_t *self)
{
    object_t **vector_values = self->vector.value;
    size_t vector_length = self->vector.length;
    char **sub_strings = calloc(vector_length, sizeof(char*));

    size_t string_length = 1;
    for (size_t i = 0; i < vector_length; i++) {
        sub_strings[i] = object_to_string(vector_values[i]);
        string_length += strlen(sub_strings[i]) + 2;
    }

    char *str = calloc(string_length, 1);
    char *ptr = str;

    *ptr++ = '[';

    int32_t write_size;
    for (size_t i = 0; i < vector_length; i++) {
        if (i != 0) {
            ptr += snprintf(ptr, string_length, ", ");
            string_length -= 2;
        }

        write_size = snprintf(ptr, string_length, "%s", sub_strings[i]);
        free(sub_strings[i]);

        ptr += write_size;
        string_length -= write_size;
    }

    *ptr++ = ']';
    *ptr++ = '\0';

    free(sub_strings);

    return str;
}
