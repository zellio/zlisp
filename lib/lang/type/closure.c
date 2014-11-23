#include "lang/type/closure.h"

object_t *closure_create(object_t *params, object_t *body, object_t *env)
{
    object_t *obj = object_create(TYPE_CLOSURE);
    if (obj == NULL)
        error("Out of memory error in `pair_create`");

    obj->closure.parameters = params;
    obj->closure.body = body;
    obj->closure.env = env;

    obj->destructor = &closure_destructor;
    obj->to_string = &closure_to_string;

    return obj;
}

int closure_destructor(object_t *self)
{
    object_destroy(self->closure.parameters);
    object_destroy(self->closure.body);
    object_destroy(self->closure.env);

    return 0;
}

char *closure_to_string(object_t *self)
{
    return typed_pointer_to_string("Closure", 7, self);
}
