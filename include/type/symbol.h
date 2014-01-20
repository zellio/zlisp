#ifndef __ZEME_TYPE_SYMBOL_H__
#define __ZEME_TYPE_SYMBOL_H__ 1

#include "type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *symbol_create(char *value);

#define is_symbol(x) (IS_TYPE((x), SCHEME_TYPE_SYMBOL))

int symbol_destructor(object_t *self);
int symbol_comperator(object_t *self, object_t *other);
char *symbol_to_string(object_t *self);

#ifdef __cplusplus
};
#endif

#endif
