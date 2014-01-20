#include "type/character.h"

object_t *character_create(char value) {
    object_t *character = object_create(SCHEME_TYPE_CHARACTER);
    if (character == NULL)
        error("Out of memeory error in `create_character`");

    character->as.character.value = value;

    character->comperator = &character_comperator;
    character->destructor = &character_destructor;
    character->to_string = &character_to_string;

    return character;
}

int character_destructor(object_t *self) {
    return object_free(self);
}

int character_comperator(object_t *self, object_t *other) {
    return self->as.character.value - other->as.character.value;
}

char *character_to_string(object_t *self) {
    char *str = calloc(2, 1);
    if (str == NULL)
        error("Out of memory error in `character_to_string`");

    *str = self->as.character.value;
    return str;
}
