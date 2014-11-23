#ifndef __ZL_LANG_TYPE_OBJECT_H__
#define __ZL_LANG_TYPE_OBJECT_H__ 1

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

#define TYPE(x) (((object_t*)(x))->type)
#define IS_TYPE(x, type) (TYPE(x) == (type))

typedef enum {
    TYPE_NIL,
    TYPE_TRUE,
    TYPE_FALSE,
    TYPE_CHARACTER,
    TYPE_FIXNUM,
    TYPE_REAL,
    TYPE_SYMBOL,
    TYPE_PAIR,
    TYPE_STRING,
    TYPE_VECTOR,
    TYPE_PORT,
    TYPE_BUILTIN,
    TYPE_CLOSURE
} object_type;

typedef struct object object_t;
struct object {
    object_type type;

    int (*comperator)(object_t *self, object_t *other);
    int (*destructor)(object_t *self);
    char *(*to_string)(object_t *self);

    union {

        /* TYPE_CHARACTER, */
        char character;

        /* TYPE_FIXNUM, */
        int64_t fixnum;

        /* TYPE_REAL, */
        double real;

        /* TYPE_SYMBOL, */
        struct {
            uint64_t hash;
            char *value;
        } symbol;

        /* TYPE_PAIR, */
        struct {
            object_t *car;
            object_t *cdr;
        } pair;

        /* TYPE_STRING, */
        struct {
            size_t length;
            char *value;
        } string;

        /* TYPE_VECTOR, */
        struct {
            size_t length;
            object_t **value;
        } vector;

        /* TYPE_PORT, */
        struct {
            FILE *value;
        } port;

        /* TYPE_BUILTIN, */
        struct {
            int special;
            object_t *(*fn)(object_t *arguments, object_t *env);
        } builtin;

        /* TYPE_CLOSURE */
        struct {
            object_t *parameters;
            object_t *body;
            object_t *env;
        } closure;
    };
};

void error(char *message);
char *typed_pointer_to_string(char *type, size_t type_length, void *ptr);

object_t *object_alloc(void);
int object_free(object_t *object);

object_t *object_create(object_type type);
int object_destroy(object_t *object);

int object_compare(object_t *object1, object_t *object2);
char *object_to_string(object_t *object);

#ifdef __cplusplus
};
#endif

#endif
