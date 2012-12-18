

#ifndef __ZELISP_LANG_TYPE_ATOM_H__
#define __ZELISP_LANG_TYPE_ATOM_H__ 1


#include "lang/types/top.h"


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif


typedef struct symbol symbol_t;
struct symbol {
    char* name;
    unsigned long hash;
};

symbol_t* symbol_create(char* name);
int symbol_destroy(symbol_t* symbol);

unsigned long symbol_hash(char* string);
symbol_t* symbol_set_hash(symbol_t* symbol);

int symbol_compare(symbol_t* l, symbol_t* r);
int symbol_compare_string(symbol_t* symbol, char* string);


typedef enum {
    ATOM_T_UNIT = 0x00,
    ATOM_T_SYMBOL = 0x10,
    ATOM_T_NUMBER = 0x20,
    ATOM_T_POINTER = 0x40
} atom_type_e;


#define ATOM_TYPE(x) ((TYPE(x)) & 0xF0)


typedef struct atom atom_t;
struct atom {
    type_e type;
    union {
        symbol_t* as_symbol;
        long as_number;
        void* as_pointer;
    } data;
};

atom_t* atom_create(void);
int atom_destroy(atom_t* atom);

top_t* atom_create_symbol(char* name);
top_t* atom_create_number(long number);
top_t* atom_create_pointer(void* pointer);

int atom_compare(atom_t* l, atom_t* r);
int atom_symbol_compare_string(top_t* sym, char* string);

#ifdef __cplusplus
};
#endif

#endif
