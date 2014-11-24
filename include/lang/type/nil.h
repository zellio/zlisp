#ifndef __ZL_LANG_TYPE_NIL_H__
#define __ZL_LANG_TYPE_NIL_H__ 1

#include "lang/type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *nil_create(void);

#define is_nil(x) (IS_TYPE((x), TYPE_NIL))

char *nil_to_string(object_t *self);

object_t *ZLC_NIL = &(object_t) {
    .type = TYPE_NIL,
    .comperator = NULL,
    .destructor = NULL,
    .to_string = &nil_to_string
};

#ifdef __cplusplus
};
#endif

#endif
