#ifndef __ZEME_TYPE_CLOSURE_H__
#define __ZEME_TYPE_CLOSURE_H__ 1

#include "type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *closure_create(object_t *parameters, object_t *body, object_t *env);

#define is_closure(x) (IS_TYPE((x), SCHEME_TYPE_CLOSURE))

int closure_destructor(object_t *self);
int closure_comperator(object_t *self, object_t *other);
char *closure_to_string(object_t *self);

#ifdef __cplusplus
};
#endif

#endif
