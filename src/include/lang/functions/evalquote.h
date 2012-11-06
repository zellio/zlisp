

#ifndef __ZELISP_LANG_FUNCTIONS_EVALQUOTE_H__
#define __ZELISP_LANG_FUNCTIONS_EVALQUOTE_H__ 1


#include "lang/types.h"


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif


top_t* evalquote(top_t* fn, top_t* x);
top_t* apply(top_t* fn, top_t* x, top_t* a);
top_t* eval(top_t* e, top_t* a);
top_t* evlis(top_t* m, top_t* a );
top_t* evcon(top_t* c, top_t* a);


#ifdef __cplusplus
};
#endif

#endif
