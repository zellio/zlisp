

#include <stdlib.h>

#include "lang/types/atom/symbol.h"


unsigned long symbol_hash(char* string) {
    unsigned long hash = 5381;
    unsigned int c;

    while ((c = (unsigned char)*string++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

symbol_t* symbol_create(char* name) {
    symbol_t* symbol = calloc(1, sizeof(symbol_t));
    if ( symbol == NULL )
        return NULL;

    char* symbol_name = malloc(sizeof(char) * SYMBOL_SIZE);
    int i;
    for ( i = 0; i < (SYMBOL_SIZE - 1) && name[i]; i++ )
        symbol_name[i] = name[i];
    for ( ; i < SYMBOL_SIZE; i++ )
        symbol_name[i] = '\0';

    symbol->name = symbol_name;
    symbol->hash = symbol_hash(name);

    return symbol;
}

int symbol_destroy(symbol_t* symbol) {
    if ( symbol == NULL )
        return -1;

    if ( symbol->name != NULL )
        free( symbol->name );
    free( symbol );

    return 0;
}

int symbol_compare(symbol_t* l, symbol_t* r) {
    if ( l == NULL || r == NULL )
        return 0;

    if ( l->hash != r->hash )
        return 0;

    return symbol_compare_string( l, r->name );
}

int symbol_compare_string(symbol_t* symbol, char* string) {
    if ( symbol == NULL || string == NULL || symbol->name == NULL )
        return 0;

    int i;
    for ( i = 0; i < (SYMBOL_SIZE - 1) && string[i] != '\0'; i++ )
        if ( symbol->name[i] != string[i] )
            return 0;
    for ( ; i < SYMBOL_SIZE; i++ )
        if ( symbol->name[i] != '\0' )
            return 0;

    return 1;
}

top_t* atom_create_symbol(char* name) {
    atom_t* atom = atom_create();
    if ( atom == NULL )
        return NULL;

    atom->type |= ATOM_T_SYMBOL;
    atom->data = (void*)symbol_create(name);

    atom->comparator = &atom_compare_symbol;
    atom->destructor = &atom_destroy_symbol;

    return (top_t*)atom;
}

int atom_destroy_symbol(atom_t* atom) {
    if ( atom == NULL )
        return -1;
    if ( atom->data != NULL )
        symbol_destroy( (symbol_t*)atom->data );
    return 0;
}

int atom_compare_symbol(atom_t* l, atom_t* r) {
    if (l == NULL || r == NULL)
        return 0;
    return symbol_compare(((symbol_t*)l->data), ((symbol_t*)r->data));
}
