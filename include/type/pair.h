#ifndef __ZEME_TYPE_PAIR_H__
#define __ZEME_TYPE_PAIR_H__ 1

#include "type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *pair_create(object_t *car, object_t *cdr);

#define is_pair(x) (IS_TYPE((x), SCHEME_TYPE_PAIR))

int pair_destructor(object_t *self);
int pair_comperator(object_t *self, object_t *other);
char *pair_to_string(object_t *self);

object_t *pair_car(object_t *self);
object_t *pair_cdr(object_t *self);

object_t *pair_set_car(object_t *self, object_t *val);
object_t *pair_set_cdr(object_t *self, object_t *val);

object_t *pair_caar(object_t *self);
object_t *pair_cadr(object_t *self);
object_t *pair_cdar(object_t *self);
object_t *pair_cddr(object_t *self);

#ifdef __cplusplus
};
#endif

#endif
