#ifndef kobayashi_std__types__types_h
#define kobayashi_std__types__types_h

#include <stdint.h>
#include <stddef.h>

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

typedef size_t      k_size;

#if defined(__GNUC__) || defined(__clang__)
    typedef __int128    k_int128;
    typedef unsigned __int128 k_uint128;
#elif defined(_MSC_VER)
    // MSVC doesn't support 128bit integer, using int64 to replace.
    typedef __int64     k_int128;
    typedef unsigned __int64 k_uint128;
#endif

typedef float       k_float32;  // 32-bit 浮点数
typedef double      k_float64;  // 64-bit 浮点数

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




#endif
