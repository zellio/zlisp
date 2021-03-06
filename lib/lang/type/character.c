#include "lang/type/character.h"

object_t *character_create(char value)
{
    object_t *obj = object_create(TYPE_CHARACTER);
    if (obj == NULL)
        error("Out of memeory error in `character_create`");

    obj->character = value;

    obj->comparator = &character_comparator;
    obj->to_string = &character_to_string;

    return obj;
}

int character_comparator(object_t *self, object_t *other)
{
    return self->character - other->character;
}

char *character_to_string(object_t *self)
{
    char *str = calloc(4, 1);
    if (str == NULL)
        error("Out of memory error in `character_to_string`");

    snprintf(str, 4, "#\\%c", self->character);
    return str;
}
