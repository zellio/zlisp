#ifndef __ZL_LANG_TYPE_BUILTIN_H__
#define __ZL_LANG_TYPE_BUILTIN_H__ 1

#include "lang/type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *builtin_create(object_t *(*fn)(object_t *args, object_t *env));
object_t *builtin_create_s(object_t *(*fn)(object_t *args, object_t *env));

#define is_builtin(x) (IS_TYPE((x), TYPE_BUILTIN))

char *builtin_to_string(object_t *self);

#ifdef __cplusplus
};
#endif

#endif
