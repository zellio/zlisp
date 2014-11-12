#include "type/vector.h"

#include <string.h>

object_t *vector_create(size_t length) {
    object_t *vector = object_create(SCHEME_TYPE_VECTOR);
    if (vector == NULL)
        error("Out of memory error in `vector_create`");

    vector->as.vector.value = calloc(length, sizeof(object_t*));
    if (vector->as.vector.value == NULL)
        error("Memory allocation error in `vector_create`");

    vector->as.vector.length = length;

    vector->comperator = &vector_comperator;
    vector->destructor = &vector_destructor;
    vector->to_string = &vector_to_string;

    return vector;
}

int vector_destructor(object_t *self) {
    if (self->as.vector.value == NULL)
        return -1;

    while(self->as.vector.length--)
        object_destroy(*self->as.vector.value++);

    return 0;
}

int vector_comperator(object_t *self, object_t *other) {
    return self - other;
}

char *vector_to_string(object_t *self) {
    object_t **vector_values = self->as.vector.value;
    size_t vector_length = self->as.vector.length;
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
