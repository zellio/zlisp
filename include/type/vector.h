#ifndef __ZEME_TYPE_VECTOR_H__
#define __ZEME_TYPE_VECTOR_H__ 1

#include "type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *vector_create(size_t length);

#define is_vector(x) (IS_TYPE((x), SCHEME_TYPE_VECTOR))

int vector_destructor(object_t *self);
int vector_comperator(object_t *self, object_t *other);
char *vector_to_vector(object_t *self);

#ifdef __cplusplus
};
#endif

#endif
