#ifndef __ZEME_TYPE_BUILTIN_H__
#define __ZEME_TYPE_BUILTIN_H__ 1

#include "type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *builtin_create(object_t *(*fn)(object_t *arguments, object_t *env));

#define is_builtin(x) (IS_TYPE((x), SCHEME_TYPE_BUILTIN))

int builtin_destructor(object_t *self);
int builtin_comperator(object_t *self, object_t *other);
char *builtin_to_string(object_t *self);

#ifdef __cplusplus
};
#endif

#endif
