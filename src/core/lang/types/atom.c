

#include "lang/types/atom.h"
#include <stdlib.h>


symbol_t* symbol_create(char* name) {
    symbol_t* symbol = calloc(1, sizeof(symbol_t));
    if ( symbol == NULL )
        return NULL;
    char* symbol_name = malloc(sizeof(char) * 31);

    int i;
    for ( i = 0; i < 30 && name[i]; i++ )
        symbol_name[i] = name[i];
    for ( ; i < 31; i++ )
        symbol_name[i] = '\0';

    symbol->name = symbol_name;
    return symbol;
}


int symbol_destroy(symbol_t* symbol) {
    if ( symbol == NULL )
        return 0;

    if ( symbol->name )
        free( symbol->name );
    free( symbol );

    return 0;
}

unsigned long symbol_hash(char* string) {
    unsigned long hash = 5381;
    unsigned int c;

    while ((c = (unsigned char)*string++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

symbol_t* symbol_set_hash(symbol_t* symbol) {
    if ( symbol == NULL )
        return symbol;
    symbol->hash = symbol_hash( symbol->name );
    return symbol;
}

int symbol_compare(symbol_t* l, symbol_t* r) {
    if ( l == NULL || r == NULL )
        return 0;

    if ( l->hash != r->hash )
        return 0;

    for ( int i = 0; i < 30; i++ )
        if ( l->name[i] != r->name[i] )
            return 0;
    return 1;
}

int symbol_compare_string(symbol_t* symbol, char* string) {
    if ( symbol == NULL || string == NULL )
        return 0;

    int i;
    for ( i = 0; i < 30 && string[i]; i++ )
        if ( symbol->name[i] != string[i] )
            return 0;
    for ( ; i < 31; i++ )
        if ( symbol->name[i] != '\0' )
            return 0;

    return 1;
}

atom_t* atom_create(void) {
    atom_t* atom = calloc(1, sizeof(atom_t));
    if ( atom == NULL )
        return NULL;
    atom->type = LANG_T_ATOM;
    atom->data.as_pointer = NULL;
    return atom;
}

int atom_destroy(atom_t* atom) {
    if ( atom == NULL )
        return -1;
    switch ( atom->type & 0xF0 ) {
    case ATOM_T_UNIT:
    case ATOM_T_NUMBER:
    case ATOM_T_POINTER:
        free( atom );
        break;
    case ATOM_T_SYMBOL:
        symbol_destroy( atom->data.as_symbol );
        free( atom );
        break;
    default:
        break;
    }
    return 0;
}

top_t* atom_create_symbol(char* name) {
    atom_t* atom = atom_create();
    atom->type |= ATOM_T_SYMBOL;
    atom->data.as_symbol = symbol_create( name );
    return (top_t*)atom;
}

top_t* atom_create_number(long number) {
    atom_t* atom = atom_create();
    atom->type |= ATOM_T_NUMBER;
    atom->data.as_number = number;
    return (top_t*)atom;
}
top_t* atom_create_pointer(void* pointer) {
    atom_t* atom = atom_create();
    atom->type |= ATOM_T_POINTER;
    atom->data.as_pointer = pointer;
    return (top_t*)atom;
}

int atom_compare(atom_t* l, atom_t* r) {
    if ( l == NULL || r == NULL )
        return 0;

    if ( l->type != r->type )
        return 0;

    switch ( l->type & 0xF0 ) {
    case ATOM_T_UNIT:
        return 1;
    case ATOM_T_SYMBOL:
        return symbol_compare( l->data.as_symbol, r->data.as_symbol );
    case ATOM_T_NUMBER:
        return l->data.as_number == r->data.as_number;
    case ATOM_T_POINTER:
        return l->data.as_pointer == r->data.as_pointer;
    default:
        return 0;
    }
}

int atom_symbol_compare_string(top_t* sym, char* string) {
    return symbol_compare_string( ((atom_t*)sym)->data.as_symbol, string );
}
