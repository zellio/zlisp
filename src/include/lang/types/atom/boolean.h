

#ifndef __ZELISP_LANG_TYPE_ATOM_BOOLEAN_H__
#define __ZELISP_LANG_TYPE_ATOM_BOOLEAN_H__ 1


#include "lang/types/top.h"
#include "lang/types/atom.h"
#include "lang/types/atom/symbol.h"


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif


#define TRUE (boolean_true())
#define FALSE (boolean_false())
#define C_BOOLEAN(x) ((x)!= FALSE)
#define L_BOOLEAN(x) ((x)) ? TRUE : FALSE


top_t* boolean_true(void);
top_t* boolean_false(void);

int boolean_to_int(top_t* value);
top_t* int_to_boolean(int value);


#ifdef __cplusplus
};
#endif

#endif
