#include "type/closure.h"

object_t *closure_create(object_t *parameters, object_t *body, object_t *env) {
    object_t *closure = object_create(SCHEME_TYPE_CLOSURE);
    if (closure == NULL)
        error("Out of memory error in `pair_create`");

    closure->as.closure.parameters = parameters;
    closure->as.closure.body = body;
    closure->as.closure.env = env;

    closure->comperator = &closure_comperator;
    closure->destructor = &closure_destructor;
    closure->to_string = &closure_to_string;

    return closure;
}

int closure_destructor(object_t *self) {
    object_destroy(self->as.closure.parameters);
    object_destroy(self->as.closure.body);
    object_destroy(self->as.closure.env);

    return 0;
}

int closure_comperator(object_t *self, object_t *other) {
    return self - other;
}

char *closure_to_string(object_t *self) {
    return typed_pointer_to_string("Closure", 7, self);
}
