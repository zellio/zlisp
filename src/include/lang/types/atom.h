

#ifndef __ZELISP_LANG_TYPE_ATOM_H__
#define __ZELISP_LANG_TYPE_ATOM_H__ 1


#include "lang/types/top.h"


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

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
    void* data;
    int (*comparator)(atom_t* l, atom_t* r);
    int (*destructor)(atom_t* atom);
};

atom_t* atom_create(void);
int atom_destroy(atom_t* atom);

int atom_compare(atom_t* l, atom_t* r);


#ifdef __cplusplus
};
#endif

#endif
