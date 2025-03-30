#ifndef kobayashi_std__container__dynamic_array_h
#define kobayashi_std__container__dynamic_array_h

#include "../types/valueType.h"

typedef struct {
    k_valueType *data;     // 指向存储元素的数组
    size_t size;          // 数组中当前元素的数量
    size_t capacity;      // 数组的容量
} k_dynamicArray;

// 初始化动态数组
k_dynamicArray* k_dynamicArray_init(size_t initialCapacity);

// 向动态数组末尾添加元素
void k_dynamicArray_add(k_dynamicArray *arr, k_valueType value);

// 获取指定索引的元素
k_valueType* k_dynamicArray_get(const k_dynamicArray *arr, size_t index);

// 设置指定索引的元素
void k_dynamicArray_set(k_dynamicArray *arr, size_t index, k_valueType value);

// 获取动态数组的大小
size_t k_dynamicArray_size(const k_dynamicArray *arr);

// 获取动态数组的容量
size_t k_dynamicArray_capacity(const k_dynamicArray *arr);

// 释放动态数组占用的内存
void k_dynamicArray_destroy(k_dynamicArray *arr);

// 移除指定索引的元素
void k_dynamicArray_remove(k_dynamicArray *arr, size_t index);

#endif