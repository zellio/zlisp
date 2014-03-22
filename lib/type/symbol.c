#include "type/symbol.h"

#include <string.h>

uint64_t symbol_hash_fn(char *str) {
    uint64_t hash = 5381L;
    uint64_t c;

    while ((c = (unsigned char)*str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

object_t *symbol_create(char *value) {
    object_t *symbol = object_create(SCHEME_TYPE_SYMBOL);
    if (symbol == NULL)
        error("Out of memory error in `symbol_create`");

    size_t size = strlen(value);

    symbol->as.symbol.value = calloc(size + 1, 1);
    if (symbol->as.symbol.value == NULL)
        error("Memory allocation error in `symbol_create`");

    strncpy(symbol->as.symbol.value, value, size);
    symbol->as.symbol.hash = symbol_hash_fn(value);

    symbol->comperator = &symbol_comperator;
    symbol->destructor = &symbol_destructor;
    symbol->to_string = &symbol_to_string;

    return symbol;
}

int symbol_destructor(object_t *self) {
    if (self->as.symbol.value == NULL)
        return -1;

    free(self->as.symbol.value);

    return 0;
}

int symbol_comperator(object_t *self, object_t *other) {
    return self->as.symbol.hash - other->as.symbol.hash;
}

char *symbol_to_string(object_t *self) {
    size_t length = strlen(self->as.symbol.value);
    char *str = calloc(length + 1, 1);

    strncpy(str, self->as.symbol.value, length);

    return str;
}
