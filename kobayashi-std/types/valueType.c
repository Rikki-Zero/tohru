#include "valueType.h"
#include "baseType.h"

/* init function */
k_valueType* k_valueType_init(k_valueType* value, k_type type) {
    if (value == NULL) {
        value = (k_valueType*)malloc(sizeof(k_valueType));
    }
    value->value_type = type;
    memset(&(value->data), 0, sizeof(value->data));
    return value;
}

/* get functions */
k_bool k_valueType_get_bool(k_valueType* value) {
    assert(value->value_type == k_bool_t);
    return value->data.v_bool;
}

k_char k_valueType_get_char(k_valueType* value) {
    assert(value->value_type == k_char_t);
    return value->data.v_char;
}

k_string k_valueType_get_string(k_valueType* value) {
    assert(value->value_type == k_string_t);
    return value->data.v_string;
}

k_int8 k_valueType_get_int8(k_valueType* value) {
    assert(value->value_type == k_int8_t);
    return value->data.v_int8;
}

k_int16 k_valueType_get_int16(k_valueType* value) {
    assert(value->value_type == k_int16_t);
    return value->data.v_int16;
}

k_int32 k_valueType_get_int32(k_valueType* value) {
    assert(value->value_type == k_int32_t);
    return value->data.v_int32;
}

k_int64 k_valueType_get_int64(k_valueType* value) {
    assert(value->value_type == k_int64_t);
    return value->data.v_int64;
}

k_uint8 k_valueType_get_uint8(k_valueType* value) {
    assert(value->value_type == k_uint8_t);
    return value->data.v_uint8;
}

k_uint16 k_valueType_get_uint16(k_valueType* value) {
    assert(value->value_type == k_uint16_t);
    return value->data.v_uint16;
}

k_uint32 k_valueType_get_uint32(k_valueType* value) {
    assert(value->value_type == k_uint32_t);
    return value->data.v_uint32;
}

k_uint64 k_valueType_get_uint64(k_valueType* value) {
    assert(value->value_type == k_uint64_t);
    return value->data.v_uint64;
}

k_float32 k_valueType_get_float32(k_valueType* value) {
    assert(value->value_type == k_float32_t);
    return value->data.v_float;
}

k_float64 k_valueType_get_float64(k_valueType* value) {
    assert(value->value_type == k_float64_t);
    return value->data.v_double;
}

k_ptr k_valueType_get_ptr(k_valueType* value) {
    assert(value->value_type == k_ptr_t);
    return value->data.v_pointer;
}

k_type k_valueType_get_type(k_valueType* value) {
    return value->value_type;
}

/* set functions */
void k_valueType_set_bool(k_valueType* value, k_bool b) {
    assert(value->value_type == k_bool_t);
    value->data.v_int8 = (k_int8)b;
}

void k_valueType_set_char(k_valueType* value, k_char c) {
    assert(value->value_type == k_char_t);
    value->data.v_char = c;
}

void k_valueType_set_string(k_valueType* value, const k_char* str) {
    assert(value->value_type == k_string_t);
    k_size size = strlen(str) * sizeof(k_char);
    k_char *dup_str = malloc(size);
    memcpy(dup_str, str, size);
    value->data.v_string = dup_str;
}

void k_valueType_set_int8(k_valueType* value, k_int8 i8) {
    assert(value->value_type == k_int8_t);
    value->data.v_int8 = i8;
}

void k_valueType_set_int16(k_valueType* value, k_int16 i16) {
    assert(value->value_type == k_int16_t);
    value->data.v_int16 = i16;
}

void k_valueType_set_int32(k_valueType* value, k_int32 i32) {
    assert(value->value_type == k_int32_t);
    value->data.v_int32 = i32;
}

void k_valueType_set_int64(k_valueType* value, k_int64 i64) {
    assert(value->value_type == k_int64_t);
    value->data.v_int64 = i64;
}

void k_valueType_set_uint8(k_valueType* value, k_uint8 u8) {
    assert(value->value_type == k_uint8_t);
    value->data.v_uint8 = u8;
}

void k_valueType_set_uint16(k_valueType* value, k_uint16 u16) {
    assert(value->value_type == k_uint16_t);
    value->data.v_uint16 = u16;
}

void k_valueType_set_uint32(k_valueType* value, k_uint32 u32) {
    assert(value->value_type == k_uint32_t);
    value->data.v_uint32 = u32;
}

void k_valueType_set_uint64(k_valueType* value, k_uint64 u64) {
    assert(value->value_type == k_uint64_t);
    value->data.v_uint64 = u64;
}

void k_valueType_set_float32(k_valueType* value, k_float32 f32) {
    assert(value->value_type == k_float32_t);
    value->data.v_float = f32;
}

void k_valueType_set_float64(k_valueType* value, k_float64 f64) {
    assert(value->value_type == k_float64_t);
    value->data.v_double = f64;
}

void k_valueType_set_ptr(k_valueType* value, k_ptr ptr) {
    assert(value->value_type == k_ptr_t);
    value->data.v_pointer = ptr;
}

void k_valueType_set_type(k_valueType* value, k_type type) {
    value->value_type = type;
}


const k_valueType_handler k_valueType_handlers[] = {
    [k_bool_t] = {  k_valueType_get_bool,  k_valueType_set_bool },
    [k_char_t] = {  k_valueType_get_char,  k_valueType_set_char },
    [k_int8_t] = {  k_valueType_get_int8,  k_valueType_set_int8 },
    [k_int16_t] = {  k_valueType_get_int16,  k_valueType_set_int16 },
    [k_int32_t] = {  k_valueType_get_int32,  k_valueType_set_int32 },
    [k_int64_t] = {  k_valueType_get_int64,  k_valueType_set_int64 },
    [k_uint8_t] = {  k_valueType_get_uint8,  k_valueType_set_uint8 },
    [k_uint16_t] = {  k_valueType_get_uint16,  k_valueType_set_uint16 },
    [k_uint32_t] = {  k_valueType_get_uint32,  k_valueType_set_uint32 },
    [k_uint64_t] = {  k_valueType_get_uint64,  k_valueType_set_uint64 },
    [k_float32_t] = {  k_valueType_get_float32,  k_valueType_set_float32 },
    [k_float64_t] = {  k_valueType_get_float64,  k_valueType_set_float64 },
    [k_string_t] = {  k_valueType_get_string,  k_valueType_set_string },
    [k_ptr_t] = {  k_valueType_get_ptr,  k_valueType_set_ptr }
};

/* memory safe */
void k_valueType_release(k_valueType *value) {
    assert(value != NULL);

    switch (value->value_type) {
        case k_string_t:
            if (value->data.v_string) {
                free(value->data.v_string);
                value->data.v_string = NULL;
            }
            break;
        case k_ptr_t:
            if (value->data.v_pointer) {
                free(value->data.v_pointer);
                value->data.v_pointer = NULL;
            }
            break;
        default:
            /* It is not necessary to release additional memory for non-pointer types */
            break;
    }

    /* Reset value_type and data state */
    value->value_type = k_undefined_t;
}
