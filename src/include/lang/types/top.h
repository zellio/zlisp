

#ifndef __ZELISP_LANG_TYPE_TOP_H__
#define __ZELISP_LANG_TYPE_TOP_H__ 1


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif


typedef enum {
    LANG_T_NONE = 0x00,
    LANG_T_TOP  = 0x01,
    LANG_T_ATOM = 0x02,
    LANG_T_CONS = 0x04
} type_e;


typedef struct top top_t;
struct top {
    type_e type;
};


top_t* top_create(void);
int top_destroy(top_t* top);

//


#ifdef __cplusplus
};
#endif

#endif
