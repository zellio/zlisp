

#ifndef __ZELISP_LANG_TYPE_ATOM_SYMBOL_H__
#define __ZELISP_LANG_TYPE_ATOM_SYMBOL_H__ 1


#include "lang/types/top.h"
#include "lang/types/atom.h"


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif


#define SYMBOL_SIZE 31


typedef struct symbol symbol_t;
struct symbol {
    char* name;
    unsigned long hash;
};


unsigned long symbol_hash(char* string);

symbol_t* symbol_create(char* name);
int symbol_destroy(symbol_t* symbol);
int symbol_compare(symbol_t* l, symbol_t* r);
int symbol_compare_string(symbol_t* l, char* string);

top_t* atom_create_symbol(char* name);
int atom_destroy_symbol(atom_t* atom);
int atom_compare_symbol(atom_t* l, atom_t* r);

int atom_symbol_compare_string(top_t* l, char* string);

#ifdef __cplusplus
};
#endif

#endif
