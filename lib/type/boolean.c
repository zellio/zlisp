#include "type/boolean.h"

object_t *boolean_create(void) {
    object_t *boolean = object_alloc();
    if (boolean == NULL)
        error("Out of memory error in `boolean_create`");

    boolean->comperator = &boolean_comperator;
    boolean->destructor = &boolean_destructor;
    boolean->to_string = &boolean_to_string;

    return boolean;
}

object_t *true_create(void) {
    static object_t *true;
    if (true == NULL) {
        true = boolean_create();
        true->type = SCHEME_TYPE_TRUE;
    }

    return true;
}

object_t *false_create(void) {
    static object_t *false;
    if (false == NULL) {
        false = boolean_create();
        false->type = SCHEME_TYPE_FALSE;
    }

    return false;
}

int boolean_destructor(object_t *self) {
    (void)self;
    return 0;
}

int boolean_comperator(object_t *self, object_t *other) {
    if (is_true(self)) {
        if (is_true(other)) {
            return 0;
        }
        return 1;
    }
    else {
        if (is_true(other)) {
            return -1;
        }
        return 0;
    }
}

static char *TRUE_STR = "true";
static char *FALSE_STR = "false";

char *boolean_to_string(object_t *self) {
    if (is_false(self))
        return FALSE_STR;
    return TRUE_STR;
}

object_t *boolean_not(object_t *self) {
    if (is_false(self))
        return true_create();
    return false_create();
}
