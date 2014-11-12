#ifndef __ZEME_TYPES_H__
#define __ZEME_TYPES_H__ 1

#include "type/object.h"
#include "type/nil.h"
#include "type/boolean.h"
#include "type/character.h"
#include "type/fixnum.h"
#include "type/symbol.h"
#include "type/pair.h"
#include "type/string.h"
#include "type/vector.h"
#include "type/port.h"
#include "type/builtin.h"
#include "type/closure.h"

#define ZEME_TYPE_GET(type, field, object) (object->as.type.field)
#define AS_ZEME_TYPE(type, ...) (type ## _create(__VA_ARGS__))
#define AS_C_TYPE(type, object) ZEME_TYPE_GET(type, value, object)

#endif
