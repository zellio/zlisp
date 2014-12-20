#ifndef __ZL_LANG_TYPE_CHARACTER_H__
#define __ZL_LANG_TYPE_CHARACTER_H__ 1

#include "lang/type/object.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *character_create(char value);

#define is_character(x) (IS_TYPE((x), TYPE_CHARACTER))

int character_comparator(object_t *self, object_t *other);
char *character_to_string(object_t *self);

#ifdef __cplusplus
};
#endif

#endif
