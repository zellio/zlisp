

#include <stdlib.h>

#include "lang/types/atom.h"


atom_t* atom_create(void) {
    atom_t* atom = calloc(1, sizeof(atom_t));
    if ( atom == NULL )
        return NULL;
    atom->type = LANG_T_ATOM;
    atom->data = NULL;
    atom->comparator = NULL;
    atom->destructor = NULL;
    return atom;
}

int atom_destroy(atom_t* atom) {
    if ( atom->destructor )
        atom->destructor( atom );
    free( atom );

    return 0;
}

int atom_compare(atom_t* l, atom_t* r) {
    if ( l == NULL || r == NULL )
        return 0;

    if ( l->type != r->type )
        return 0;

    if ( l == r )
        return 1;

    if ( l->comparator )
        return l->comparator( l, r );

    return 0;
}
