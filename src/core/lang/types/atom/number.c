

#include <stdlib.h>

#include "lang/types/atom/number.h"



number_t* number_create(long value) {
    number_t* number = calloc(1, sizeof(number_t));
    if ( number == NULL )
        return NULL;
    number->value = value;
    return number;
}

int number_destroy(number_t* number) {
    if ( number == NULL )
        return -1;
    free( number );
    return 0;
}

int number_compare(number_t* l, number_t* r) {
    if ( l == NULL || r == NULL )
        return 0;
    return l->value == r->value;
}

top_t* atom_create_number(long number) {
    atom_t* atom = atom_create();
    if ( atom == NULL )
        return NULL;

    atom->type |= ATOM_T_NUMBER;
    atom->data = (void*)number_create(number);

    atom->comparator = &atom_compare_number;
    atom->destructor = &atom_destroy_number;

    return (top_t*)atom;
}

int atom_destroy_number(atom_t* atom) {
    if ( atom == NULL )
        return -1;
    if ( atom->data != NULL )
        number_destroy( (number_t*)atom->data );
    return 0;
}

int atom_compare_number(atom_t* l, atom_t* r) {
    if (l == NULL || r == NULL)
        return 0;
    return number_compare(((number_t*)l->data), ((number_t*)r->data));
}
