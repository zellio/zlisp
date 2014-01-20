#ifndef __ZEME_TYPE_FIXNUM_H__
#define __ZEME_TYPE_FIXNUM_H__ 1

#include "type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *fixnum_create(int64_t value);

#define is_fixnum(x) (IS_TYPE((x), SCHEME_TYPE_FIXNUM))

int fixnum_destructor(object_t *self);
int fixnum_comperator(object_t *self, object_t *other);
char *fixnum_to_string(object_t *self);

#ifdef __cplusplus
};
#endif

#endif
