#ifndef __ZL_LANG_TYPE_CLOSURE_H__
#define __ZL_LANG_TYPE_CLOSURE_H__ 1

#include "lang/type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *closure_create(object_t *params, object_t *body, object_t *env);

#define is_closure(x) (IS_TYPE((x), TYPE_CLOSURE))

int closure_destructor(object_t *self);
char *closure_to_string(object_t *self);

#ifdef __cplusplus
};
#endif

#endif
