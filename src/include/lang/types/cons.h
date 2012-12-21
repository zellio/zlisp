
#ifndef __ZELISP_LANG_TYPE_CONS_H__
#define __ZELISP_LANG_TYPE_CONS_H__ 1


#include "lang/types/top.h"


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif


typedef struct cons cons_t;
struct cons {
    type_e type;
    top_t* car;
    top_t* cdr;
};

top_t* cons_create(top_t* car, top_t* cdr);
int cons_destroy(cons_t* cons);


#ifdef __cplusplus
};
#endif

#endif
