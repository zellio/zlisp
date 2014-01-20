#ifndef __ZEME_TYPE_BOOLEAN_H__
#define __ZEME_TYPE_BOOLEAN_H__ 1

#include "type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *true_create(void);
object_t *false_create(void);

#define is_true(x) (IS_TYPE((x), SCHEME_TYPE_TRUE))
#define is_false(x) (IS_TYPE((x), SCHEME_TYPE_FALSE))
#define is_boolean(x) (is_true(x) || is_false(x))

int boolean_destructor(object_t *self);
int boolean_comperator(object_t *self, object_t *other);
char *boolean_to_string(object_t *self);

#ifdef __cplusplus
};
#endif

#endif
