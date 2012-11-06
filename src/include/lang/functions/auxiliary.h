

#ifndef __ZELISP_LANG_FUNCTIONS_PAIRLIS_H__
#define __ZELISP_LANG_FUNCTIONS_PAIRLIS_H__ 1


#include "lang/types.h"


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif


top_t* parlis(top_t* fn, top_t* x, top_t* a);
top_t* assoc(top_t* e, top_t* a);
top_t* null(top_t* sexpr);
top_t* equal(top_t* x, top_t* y);

#ifdef __cplusplus
};
#endif

#endif
