#ifndef __ZEME_TYPE_NIL_H__
#define __ZEME_TYPE_NIL_H__ 1

#include "type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *nil_create(void);
object_t *false_create(void);

#define is_nil(x) (IS_TYPE((x), SCHEME_TYPE_NIL))

int nil_destructor(object_t *self);
int nil_comperator(object_t *self, object_t *other);
char *nil_to_string(object_t *self);

#ifdef __cplusplus
};
#endif

#endif
