#ifndef __ZL_LANG_TYPE_PORT_H__
#define __ZL_LANG_TYPE_PORT_H__ 1

#include "lang/type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *port_create(FILE* stream);

#define is_port(x) (IS_TYPE((x), SCHEME_TYPE_PORT))

char *port_to_string(object_t *self);

#ifdef __cplusplus
};
#endif

#endif
