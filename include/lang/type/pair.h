#ifndef __ZL_LANG_TYPE_PAIR_H__
#define __ZL_LANG_TYPE_PAIR_H__ 1

#include "lang/type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *pair_create(object_t *car, object_t *cdr);

#define is_pair(x) (IS_TYPE((x), TYPE_PAIR))

int pair_destructor(object_t *self);
char *pair_to_string(object_t *self);

#define pair_car(x) ((x)->pair.car)
#define pair_cdr(x) ((x)->pair.cdr)

#define pair_caar(x) ((x)->pair.car->pair.car)
#define pair_cadr(x) ((x)->pair.car->pair.cdr)
#define pair_cdar(x) ((x)->pair.cdr->pair.car)
#define pair_cddr(x) ((x)->pair.cdr->pair.cdr)

object_t *pair_set_car(object_t *self, object_t *car);
object_t *pair_set_cdr(object_t *self, object_t *cdr);

#ifdef __cplusplus
};
#endif

#endif
