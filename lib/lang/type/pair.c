#include "lang/type/pair.h"

object_t *pair_create(object_t *car, object_t *cdr)
{
    object_t *obj = object_create(TYPE_PAIR);
    if (obj == NULL)
        error("Out of memory error in `pair_create`");

    obj->pair.car = car;
    obj->pair.cdr = cdr;

    obj->destructor = &pair_destructor;
    obj->to_string = &pair_to_string;

    return obj;
}


int pair_destructor(object_t *self)
{
    object_destroy(self->pair.car);
    object_destroy(self->pair.cdr);

    return 0;
}

char *_pair_to_string(object_t *self, uint8_t in_list)
{
    char *str;

    if (in_list) {
        object_t *car = self->pair.car;
        object_t *cdr = self->pair.cdr;

        char *car_str = object_to_string(car);

        if (IS_TYPE(cdr, TYPE_NIL))
            return car_str;

        char *cdr_str;

        size_t size = strlen(car_str) + 2;

        if (IS_TYPE(cdr, TYPE_PAIR)) {
            cdr_str = _pair_to_string(cdr, 1);
            size += strlen(cdr_str);

            str = calloc(size, 1);
            snprintf(str, size, "%s %s", car_str, cdr_str);
        }
        else {
            cdr_str = object_to_string(cdr);
            size += strlen(cdr_str);

            size += 2;
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

object_t *pair_set_car(object_t *self, object_t *car)
{
    self->pair.car = car;
    return self;
}

object_t *pair_set_cdr(object_t *self, object_t *cdr)
{
    self->pair.cdr = cdr;
    return self;
}
