#include "core.h"

#define ZEME_FN(label, args) object_t *zeme_fn_ ## label(object_t *args)

// "type/object"

// "type/boolean"
ZEME_FN(not, args) {
    return boolean_not(pair_car(args));
}

inline object_t *zeme_predicate(int32_t bool) {
    if (bool)
        return true_create();
    return false_create();
}

// "type/character"
ZEME_FN(char_equal_predicate, args) {
    return zeme_predicate(object_compare(pair_car(args), pair_cadr(args)) == 0);
}

ZEME_FN(char_lt_predicate, args) {
    return zeme_predicate(object_compare(pair_car(args), pair_cadr(args)) < 0);
}

ZEME_FN(char_gt_predicate, args) {
    return zeme_predicate(object_compare(pair_car(args), pair_cadr(args)) > 0);
}

ZEME_FN(char_lte_predicate, args) {
    return zeme_predicate(object_compare(pair_car(args), pair_cadr(args)) <= 0);
}

ZEME_FN(char_gte_predicate, args) {
    return zeme_predicate(object_compare(pair_car(args), pair_cadr(args)) >= 0);
}

ZEME_FN(char_to_fixnum, args) {
    return AS_ZEME_TYPE(fixnum, (int64_t)AS_C_TYPE(character, pair_car(args)));
}

// "type/fixnum"
ZEME_FN(fixnum_to_char, args) {
    return AS_ZEME_TYPE(character, (char)AS_C_TYPE(fixnum, pair_car(args)));
}

ZEME_FN(fixnum_add, args) {
    return fixnum_add(pair_car(args), pair_cadr(args));
}

ZEME_FN(fixnum_subtract, args) {
    return fixnum_subtract(pair_car(args), pair_cadr(args));
}

ZEME_FN(fixnum_multiply, args) {
    return fixnum_multiply(pair_car(args), pair_cadr(args));
}

ZEME_FN(fixnum_quotient, args) {
    return fixnum_quotient(pair_car(args), pair_cadr(args));
}

ZEME_FN(fixnum_remainder, args) {
    return fixnum_remainder(pair_car(args), pair_cadr(args));
}

// object_t *_fixnum_max(object_t *args) {
// }
//
// object_t *_fixnum_min(object_t *args) {
// }
//
// // object_t *_fixnum_abs(object_t *args) {
// }
//
// // object_t *_fixnum_numerator(object_t *args) {
// }
//
// // object_t *_fixnum_denominator(object_t *args) {
// }
//
// // object_t *_fixnum_gcd(object_t *args) {
// }
//
// // object_t *_fixnum_lcm(object_t *args) {
// }
//
// // object_t *_fixnum_floor(object_t *args) {
// }
//
// // object_t *_fixnum_ceiling(object_t *args) {
// }
//
// // object_t *_fixnum_truncate(object_t *args) {
// }
//
// // object_t *_fixnum_round(object_t *args) {
// }
//
// // object_t *_fixnum_rationalize(object_t *args) {
// }
//
// // object_t *_fixnum_expt(object_t *args) {
// }


// "type/symbol"
ZEME_FN(symbol_to_string, args) {
    return AS_ZEME_TYPE(string, AS_C_TYPE(symbol, pair_car(args)));
}

// "type/pair"
ZEME_FN(cons, args) {
    return AZ_ZEME_TYPE(pair, pair_car(args), pair_cadr(args));
}

ZEME_FN(car, args) {
    return pair_caar(args);
}

ZEME_FN(cdr, args) {
    return pair_cdar(args);
}

// object_t *_set_car_bang(object_t* args) {
//     return pair_set_car(pair_car(args), pair_cadr(args));
// }
//
// object_t *_set_cdr_bang(object_t* args) {
//     return pair_set_cdr(pair_car(args), pair_cadr(args));
// }

// "type/string"
ZEME_FN(symbol_to_string, args) {
    return AS_ZEME_TYPE(string, AS_C_TYPE(symbol, pair_car(args)));
}
ZEME_FN(symbol_to_string, args) {
    return AS_ZEME_TYPE(symbol, AS_C_TYPE(string, pair_car(args)));
}

// object_t *_make_string(object_t* args) {
// }
//

ZEME_FN(string_length, args) {
    return AS_ZEME_TYPE(fixnum, ZEME_TYPE_GET(string, length, pair_car(args)));
}

ZEME_FN(string_ref, args) {
    int64_t index = AS_C_TYPE(fixnum, pair_car(args));
    return AS_ZEME_TYPE(character, string_get_index(pair_cadr(args), index));
}

ZEME_FN(string_set_bang, args) {
    object_t *str = pair_car(args);
    int64_t index = AS_C_TYPE(fixnum, pair_cadr(args));
    char character = AS_C_TYPE(character, pair_caddr(args));

    return string_set_index(str, index, character);
}

// // // "type/vector"
// // object_t *_make_vector(object_t* args) {
// // }
// //
// object_t *_vector_length(object_t* args) {
//
// }
// //
// // object_t *_vector_ref(object_t* args) {
// // }
// //
// // object_t *_vector_set_bang(object_t* args) {
// // }
//
//
// // "type/port"
//
// // "type/builtin"
//
// // "type/closure"
//
