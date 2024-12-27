#ifndef kobayashi_std__types__valueType_h
#define kobayashi_std__types__valueType_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baseType.h"

typedef struct {
    k_type value_type;
    union {
        k_int8      v_int8;
        k_int16     v_int16;
        k_int32     v_int32;
        k_int64     v_int64;
        k_uint8     v_uint8;
        k_uint16    v_uint16;
        k_uint32    v_uint32;
        k_uint64    v_uint64;
        k_float32   v_float;
        k_float64   v_double;
        k_char      v_char;
        k_bool      v_bool;
        k_string    v_string;
        k_ptr       v_pointer;
    } data;
} k_valueType;

typedef struct {
    void *get;
    void *set;
} k_valueType_handler;


/* init function */
k_valueType*         k_valueType_init(k_valueType* value, k_type type);

/* get function */
k_bool              k_valueType_get_bool(k_valueType* value);
k_char              k_valueType_get_char(k_valueType* value);
k_string            k_valueType_get_string(k_valueType* value);

k_int8              k_valueType_get_int8(k_valueType* value);
k_int16             k_valueType_get_int16(k_valueType* value);
k_int32             k_valueType_get_int32(k_valueType* value);
k_int64             k_valueType_get_int64(k_valueType* value);

k_uint8             k_valueType_get_uint8(k_valueType* value);
k_uint16            k_valueType_get_uint16(k_valueType* value);
k_uint32            k_valueType_get_uint32(k_valueType* value);
k_uint64            k_valueType_get_uint64(k_valueType* value);

k_float32           k_valueType_get_float32(k_valueType* value);
k_float64           k_valueType_get_float64(k_valueType* value);

k_ptr               k_valueType_get_ptr(k_valueType* value);

k_type              k_valueType_get_type(k_valueType* value);

/* set function */
void                k_valueType_set_bool(k_valueType* value, k_bool b);
void                k_valueType_set_char(k_valueType* value, k_char c);
void                k_valueType_set_string(k_valueType* value, const k_char* str);

void                k_valueType_set_int8(k_valueType* value, k_int8 i8);
void                k_valueType_set_int16(k_valueType* value, k_int16 i16);
void                k_valueType_set_int32(k_valueType* value, k_int32 i32);
void                k_valueType_set_int64(k_valueType* value, k_int64 i64);

void                k_valueType_set_uint8(k_valueType* value, k_uint8 u8);
void                k_valueType_set_uint16(k_valueType* value, k_uint16 u16);
void                k_valueType_set_uint32(k_valueType* value, k_uint32 u32);
void                k_valueType_set_uint64(k_valueType* value, k_uint64 u64);

void                k_valueType_set_float32(k_valueType* value, k_float32 f32);
void                k_valueType_set_float64(k_valueType* value, k_float64 f64);

void                k_valueType_set_ptr(k_valueType* value, k_ptr ptr);
void                k_valueType_set_type(k_valueType* value, k_type type);

extern const k_valueType_handler k_valueType_handlers[];
#define k_valueType_map_get(type) k_valueType_handlers[type].get
#define k_valueType_get(object,real_type)       \
    ((real_type (*)(k_valueType*))              \
        k_valueType_map_get(real_type##_t))     \
        (object)

#define k_valueType_map_set(type) k_valueType_handlers[type].set
#define k_valueType_set(object,real_type,value) \
    ((void (*)(k_valueType*, real_type))        \
        k_valueType_map_set(real_type##_t))     \
        (object,value)

/* memory safe */
void                k_valueType_release(k_valueType *value);

#endif

