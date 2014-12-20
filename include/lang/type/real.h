#ifndef __ZL_LANG_TYPE_REAL_H__
#define __ZL_LANG_TYPE_REAL_H__ 1

#include "lang/type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *real_create(double value);

#define is_real(x) (IS_TYPE((x), TYPE_REAL))

int real_comparator(object_t *self, object_t *other);

#ifdef __cplusplus
};
#endif

#endif
