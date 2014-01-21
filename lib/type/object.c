#include "type/object.h"

void error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

object_t *object_alloc(void) {
    object_t *obj = calloc(1, sizeof(object_t));
    if (obj == NULL)
        error("Memory allocation error in object_alloc");

    return obj;
}

int object_free(object_t *object) {
    if (object == NULL)
        return -1;

    free(object);

    return 0;
}

object_t *object_create(object_type type) {
    object_t *obj = object_alloc();

    obj->type = type;

    return obj;
}

int object_destroy(object_t *object) {
    if (object->destructor)
        (*object->destructor)(object);

    return object_free(object);
}

int object_compare(object_t *object1, object_t *object2) {
    if (TYPE(object1) != TYPE(object2))
        error("Type error in object_compare");

    if (*object1->comperator)
        return (*object1->comperator)(object1, object2);

    return (uint32_t)(object1 - object2);
}

char *object_to_string(object_t *object) {
    if (object->to_string)
        return (*object->to_string)(object);

    char *str = calloc(27, 1);

    snprintf(str, 27, "#<Object:%#016lx>");

    return str;
}
