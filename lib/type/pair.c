#include "type/pair.h"

#include <string.h>

object_t *pair_create(object_t *car, object_t *cdr) {
    object_t *pair = object_create(SCHEME_TYPE_PAIR);
    if (pair == NULL)
        error("Out of memory error in `pair_create`");

    pair->as.pair.car = car;
    pair->as.pair.cdr = cdr;

    pair->comperator = &pair_comperator;
    pair->destructor = &pair_destructor;
    pair->to_string = &pair_to_string;

    return pair;
}


int pair_destructor(object_t *self) {
    object_destroy(self->as.pair.car);
    object_destroy(self->as.pair.cdr);

    return 0;
}

int pair_comperator(object_t *self, object_t *other) {
    return self - other;
}

char *_pair_to_string(object_t *self, uint8_t in_list) {
    char *str;

    if (in_list) {
        object_t *car = self->as.pair.car;
        object_t *cdr = self->as.pair.cdr;

        char *car_str = object_to_string(car);

        if (IS_TYPE(cdr, SCHEME_TYPE_NIL))
            return car_str;

        char *cdr_str = object_to_string(cdr);

        size_t size = strlen(car_str) + 1 + strlen(cdr_str) + 1;

        if (IS_TYPE(cdr, SCHEME_TYPE_PAIR)) {
            str = calloc(size, 1);
            snprintf(str, size, "%s %s", car_str, cdr_str);
        }
        else {
            size++;
            str = calloc(size, 1);
            snprintf(str, size, "%s . %s", car_str, cdr_str);
        }

        free(car_str);
        free(cdr_str);

        return str;
    }

    char *temp_str = _pair_to_string(self, 1);
    size_t size = strlen(temp_str) + 3;

    str = calloc(size, 1);
    snprintf(str, size, "(%s)", temp_str);

    free(temp_str);

    return str;
}

char *pair_to_string(object_t *self) {
    return _pair_to_string(self, 0);
}
