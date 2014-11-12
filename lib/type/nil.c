#include "type/nil.h"

object_t *nil_create(void) {
    static object_t *nil = NULL;

    if (nil == NULL) {

        nil = object_create(SCHEME_TYPE_NIL);
        if (nil == NULL)
            error("Out of memeory error in `create_nil`");

        nil->comperator = &nil_comperator;
        nil->destructor = &nil_destructor;
        nil->to_string = &nil_to_string;
    }

    return nil;
}

int nil_destructor(object_t *self) {
    (void)self;
    return 0;
}

int nil_comperator(object_t *self, object_t *other) {
    return (uint64_t)(self - other);
}

static char *NIL_STR = "nil";

char *nil_to_string(object_t *self) {
    (void)self;
    char *str = calloc(4, 1);
    int i = 4;
    while (i--) str[i] = NIL_STR[i];
    return str;
}
