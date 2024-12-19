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

const k_char* k_valueType_get_string(k_valueType* value) {
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
    value->data.v_string = strdup(str);
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
