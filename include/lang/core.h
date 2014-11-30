#ifndef __ZL_LANG_CORE_H__
#define __ZL_LANG_CORE_H__ 1

#include "lang/type.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *zlc_eq(object_t *obj1, object_t *obj2);

object_t *zlc_assoc(object_t *key, object_t *alist);
object_t *zlc_acons(object_t *key, object_t *val, object_t *alist);

#ifdef __cplusplus
};
#endif

#endif
