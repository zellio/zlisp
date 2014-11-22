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

#ifdef __cplusplus
};
#endif

#endif
