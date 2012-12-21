

#ifndef __ZELISP_LANG_TYPES_H__
#define __ZELISP_LANG_TYPES_H__ 1


#include "lang/types/top.h"
#include "lang/types/atom.h"
#include "lang/types/atom/boolean.h"
#include "lang/types/atom/number.h"
#include "lang/types/atom/symbol.h"
#include "lang/types/cons.h"


#define TYPE(x) ((x)?(((top_t*)(x))->type):0x00)
#define LANG_TYPE(x) (TYPE(x) & 0x0F)


#endif
