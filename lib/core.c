#include "core.h"

// "type/object"

inline object_t *zeme_predicate(int32_t bool) {
    if (bool)
        return true_create();
    return false_create();
}

// "type/boolean"
object_t *zeme_fn_not(object_t *args) {
    return boolean_not(pair_car(args));
}

// "type/character"
object_t *zeme_fn_char_equal_predicate(object_t *args) {
    return zeme_predicate(object_compare(pair_car(args), pair_cadr(args)) == 0);
}

object_t *zeme_fn_char_lt_predicate(object_t *args) {
    return zeme_predicate(object_compare(pair_car(args), pair_cadr(args)) < 0);
}

object_t *zeme_fn_char_gt_predicate(object_t *args) {
    return zeme_predicate(object_compare(pair_car(args), pair_cadr(args)) > 0);
}

object_t *zeme_fn_char_lte_predicate(object_t *args) {
    return zeme_predicate(object_compare(pair_car(args), pair_cadr(args)) <= 0);
}

object_t *zeme_fn_char_gte_predicate(object_t *args) {
    return zeme_predicate(object_compare(pair_car(args), pair_cadr(args)) >= 0);
}

object_t *zeme_fn_char_to_fixnum(object_t *args) {
    return fixnum_create((int64_t)pair_car(args)->as.character.value);
}

// "type/fixnum"
object_t *zeme_fn_fixnum_to_char(object_t *args) {
    return character_create((char)pair_car(args)->as.fixnum.value);
}

object_t *zeme_fn_fixnum_add(object_t *args) {
    return fixnum_add(pair_car(args), pair_cadr(args));
}

object_t *zeme_fn_fixnum_subtract(object_t *args) {
    return fixnum_subtract(pair_car(args), pair_cadr(args));
}

object_t *zeme_fn_fixnum_multiply(object_t *args) {
    return fixnum_multiply(pair_car(args), pair_cadr(args));
}

object_t *zeme_fn_fixnum_quotient(object_t *args) {
    return fixnum_quotient(pair_car(args), pair_cadr(args));
}

object_t *zeme_fn_fixnum_remainder(object_t *args) {
    return fixnum_remainder(pair_car(args), pair_cadr(args));
}

// // object_t *zeme_fn_fixnum_max(object_t *args) {
// }
//
// // object_t *zeme_fn_fixnum_min(object_t *args) {
// }
//
// // object_t *zeme_fn_fixnum_abs(object_t *args) {
// }
//
// // object_t *zeme_fn_fixnum_numerator(object_t *args) {
// }
//
// // object_t *zeme_fn_fixnum_denominator(object_t *args) {
// }
//
// // object_t *zeme_fn_fixnum_gcd(object_t *args) {
// }
//
// // object_t *zeme_fn_fixnum_lcm(object_t *args) {
// }
//
// // object_t *zeme_fn_fixnum_floor(object_t *args) {
// }
//
// // object_t *zeme_fn_fixnum_ceiling(object_t *args) {
// }
//
// // object_t *zeme_fn_fixnum_truncate(object_t *args) {
// }
//
// // object_t *zeme_fn_fixnum_round(object_t *args) {
// }
//
// // object_t *zeme_fn_fixnum_rationalize(object_t *args) {
// }
//
// // object_t *zeme_fn_fixnum_expt(object_t *args) {
// }
//
//
// // "type/symbol"
object_t *zeme_fn_symbol_to_string(object_t* args) {
    return string_create(object_to_string(pair_car(args)));
}

// // "type/pair"
object_t *zeme_fn_cons(object_t* args) {
    return pair_create(pair_car(args), pair_cadr(args));
}
//
object_t *zeme_fn_car(object_t* args) {
    return pair_caar(args);
}

object_t *zeme_fn_cdr(object_t* args) {
    return pair_cdar(args);
}

object_t *zeme_fn_set_car_bang(object_t* args) {
    return pair_set_car(pair_car(args), pair_cadr(args));
}

object_t *zeme_fn_set_cdr_bang(object_t* args) {
    return pair_set_cdr(pair_car(args), pair_cadr(args));
}


// // "type/string"
object_t *zeme_fn_string_to_symbol(object_t* args) {
    return symbol_create(pair_car(args)->as.string.value);
}

// object_t *zeme_fn_make_string(object_t* args) {
// }
//
object_t *zeme_fn_string_length(object_t* args) {
    return fixnum_create(pair_car(args)->as.string.length);
}

object_t *zeme_fn_string_ref(object_t* args) {
    size_t index = pair_cadr(args)->as.fixnum.value;
    return string_get_index(pair_char(args), index);
}

object_t *zeme_fn_string_set_bang(object_t* args) {
}


// // "type/vector"
// object_t *zeme_fn_make_vector(object_t* args) {
// }
//
// object_t *zeme_fn_vector_length(object_t* args) {
// }
//
// object_t *zeme_fn_vector_ref(object_t* args) {
// }
//
// object_t *zeme_fn_vector_set_bang(object_t* args) {
// }


// "type/port"

// "type/builtin"

// "type/closure"
