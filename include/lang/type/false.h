#ifndef __ZL_LANG_TYPE_FALSE_H__
#define __ZL_LANG_TYPE_FALSE_H__ 1

#include "lang/type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *ZLC_FALSE;

object_t *false_create(void);

#define is_false(x) (IS_TYPE((x), TYPE_FALSE))

char *false_to_string(object_t *self);

#ifdef __cplusplus
};
#endif

#endif
