#include "type/builtin.h"

object_t *builtin_create(object_t *(*fn)(object_t *arguments)) {
    object_t *builtin = object_create(SCHEME_TYPE_BUILTIN);
    if (builtin == NULL)
        error("Out of memory error in `pair_create`");

    builtin->as.builtin.fn = fn;

    builtin->comperator = &builtin_comperator;
    builtin->destructor = &builtin_destructor;
    builtin->to_string = &builtin_to_string;

    return builtin;
}

int builtin_destructor(object_t *self) {
    (void)self;
    return 0;
}
int builtin_comperator(object_t *self, object_t *other) {
    return self - other;
}

char *builtin_to_string(object_t *self) {
    return typed_pointer_to_string("Builtin", 7, self);
}
