

#ifndef __ZELISP_LANG_TYPE_ATOM_NUMBER_H__
#define __ZELISP_LANG_TYPE_ATOM_NUMBER_H__ 1


#include "lang/types/top.h"
#include "lang/types/atom.h"


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

typedef struct number number_t;
struct number {
    long value;
};


number_t* number_create(long value);
int number_destroy(number_t* number);
int number_compare(number_t* l, number_t* r);

top_t* atom_create_number(long number);
int atom_destroy_number(atom_t* atom);
int atom_compare_number(atom_t* l, atom_t* r);


#ifdef __cplusplus
};
#endif

#endif
