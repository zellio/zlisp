#ifndef __ZEME_TYPE_PORT_H__
#define __ZEME_TYPE_PORT_H__ 1

#include "type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *port_create(FILE* stream);

#define is_port(x) (IS_TYPE((x), SCHEME_TYPE_PORT))

int port_destructor(object_t *self);
int port_comperator(object_t *self, object_t *other);
char *port_to_string(object_t *self);

#ifdef __cplusplus
};
#endif

#endif
