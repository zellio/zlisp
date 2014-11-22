#ifndef __ZL_LANG_TYPE_TRUE_H__
#define __ZL_LANG_TYPE_TRUE_H__ 1

#include "lang/type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *true_create(void);

#define is_true(x) (IS_TYPE((x), TYPE_TRUE))

char *true_to_string(object_t *self);

#ifdef __cplusplus
};
#endif

#endif
