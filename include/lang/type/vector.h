#ifndef __ZL_LANG_TYPE_VECTOR_H__
#define __ZL_LANG_TYPE_VECTOR_H__ 1

#include "lang/type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *vector_create(size_t length);

#define is_vector(x) (IS_TYPE((x), TYPE_VECTOR))

int vector_destructor(object_t *self);
char *vector_to_string(object_t *self);

#ifdef __cplusplus
};
#endif

#endif
