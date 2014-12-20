#include "lang/type/symbol.h"

uint64_t symbol_hash_fn(char *str)
{
    uint64_t hash = 5381L;
    uint64_t c;

    while ((c = (unsigned char)*str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

object_t *symbol_create(char *value)
{
    object_t *obj = object_create(TYPE_SYMBOL);
    if (obj == NULL)
        error("Out of memory error in `symbol_create`");

    size_t size = strlen(value);
    obj->symbol.value = strndup(value, size);
    if (obj->symbol.value == NULL)
        error("Memory allocation error in `symbol_create'");

    obj->symbol.hash = symbol_hash_fn(value);

    obj->comparator = &symbol_comparator;
    obj->destructor = &symbol_destructor;
    obj->to_string = &symbol_to_string;

    return obj;
}

int symbol_destructor(object_t *self)
{
    if (self->symbol.value == NULL)
        return -1;

    free(self->symbol.value);

    return 0;
}

int symbol_comparator(object_t *self, object_t *other)
{
    return self->symbol.hash - other->symbol.hash;
}

char *symbol_to_string(object_t *self)
{
    char *str = strdup(self->symbol.value);
    return str;
}
