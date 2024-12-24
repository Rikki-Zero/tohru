#ifndef kobayashi_std__types__types_h
#define kobayashi_std__types__types_h

#include <stdint.h>
#include <stddef.h>
#include <assert.h>

typedef int8_t      k_int8;
typedef uint8_t     k_uint8;
typedef int16_t     k_int16;
typedef uint16_t    k_uint16;
typedef int32_t     k_int32;
typedef uint32_t    k_uint32;
typedef int64_t     k_int64;
typedef uint64_t    k_uint64;

typedef void*       k_ptr;

typedef char        k_char;
typedef char*       k_string;

typedef size_t      k_size;

#if defined(__GNUC__) || defined(__clang__)
    typedef __int128    k_int128;
    typedef unsigned __int128 k_uint128;
#elif defined(_MSC_VER)
    // MSVC doesn't support 128bit integer, using int64 to replace.
    typedef __int64     k_int128;
    typedef unsigned __int64 k_uint128;
#endif

typedef float       k_float32;
typedef double      k_float64;

typedef enum {
    False = 0,
    True = 1
} k_bool;


// memory alignment
#ifdef _MSC_VER
    // using __declspec(align) in MSVC
    #define k_ALIGN(x) __declspec(align(x))  
#else
    // using __attribute__((aligned)) in GCC and Clang
    #define k_ALIGN(x) __attribute__((aligned(x)))
#endif

// type list
typedef enum {
    k_int8_t,
    k_uint8_t,
    k_int16_t,
    k_uint16_t,
    k_int32_t,
    k_uint32_t,
    k_int64_t,
    k_uint64_t,
    k_int128_t,
    k_uint128_t,
    k_float32_t,
    k_float64_t,
    k_bool_t,
    k_ptr_t,
    k_char_t,
    k_string_t,
    k_size_t
} k_type;

#endif
