#ifndef __ZEME_TYPE_STRING_H__
#define __ZEME_TYPE_STRING_H__ 1

#include "type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *string_create(char *value);

#define is_string(x) (IS_TYPE((x), SCHEME_TYPE_STRING))

int string_destructor(object_t *self);
int string_comperator(object_t *self, object_t *other);
char *string_to_string(object_t *self);

char string_get_index(object_t *self, size_t index);
object_t *string_set_index(object_t *self, size_t index, char character);

#ifdef __cplusplus
};
#endif

#endif
