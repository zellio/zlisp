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
    obj->as.symbol.value = strndup(value, size);
    if (obj->as.symbol.value == NULL)
        error("Memory allocation error in `symbol_create'");

    obj->as.symbol.hash = symbol_hash_fn(value);

    obj->comperator = &symbol_comperator;
    obj->destructor = &symbol_destructor;
    obj->to_string = &symbol_to_string;

    return obj;
}

int symbol_destructor(object_t *self)
{
    if (self->as.symbol.value == NULL)
        return -1;

    free(self->as.symbol.value);

    return 0;
}

int symbol_comperator(object_t *self, object_t *other)
{
    return self->as.symbol.hash - other->as.symbol.hash;
}

char *symbol_to_string(object_t *self)
{
    char *str = strdup(self->as.symbol.value);
    return str;
}
