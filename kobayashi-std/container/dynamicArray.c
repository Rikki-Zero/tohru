#include "dynamicArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

k_dynamicArray* k_dynamicArray_init(size_t initialCapacity) {
    k_dynamicArray *arr = (k_dynamicArray*)malloc(sizeof(k_dynamicArray));
    if (arr == NULL) {
        perror("Failed to allocate memory for dynamic array");
        exit(EXIT_FAILURE);
    }

    arr->size = 0;
    arr->capacity = initialCapacity > 0 ? initialCapacity : 1; // ensure initial capacity is at least 1
    arr->data = (k_valueType*)malloc(sizeof(k_valueType) * arr->capacity);
    if (arr->data == NULL) {
        perror("Failed to allocate memory for dynamic array data");
        free(arr);
        exit(EXIT_FAILURE);
    }
    return arr;
}

static void k_dynamicArray_resize(k_dynamicArray *arr, size_t newCapacity) {
    if (newCapacity < arr->size) {
        fprintf(stderr, "Warning: Trying to resize to a capacity smaller than current size.\n");
        return;
    }
    k_valueType *newData = (k_valueType*)realloc(arr->data, sizeof(k_valueType) * newCapacity);
    if (newData == NULL) {
        perror("Failed to reallocate memory for dynamic array");
        exit(EXIT_FAILURE);
    }
    arr->data = newData;
    arr->capacity = newCapacity;
}

void k_dynamicArray_add(k_dynamicArray *arr, k_valueType value) {
    if (arr->size == arr->capacity) {
        k_dynamicArray_resize(arr, arr->capacity * 2); // double the capacity
    }
    arr->data[arr->size++] = value; // directly copy the k_valueType struct
}

k_valueType* k_dynamicArray_get(const k_dynamicArray *arr, size_t index) {
    if (index >= arr->size) {
        fprintf(stderr, "Error: Index out of bounds.\n");
        return NULL;
    }
    return &arr->data[index];
}

void k_dynamicArray_set(k_dynamicArray *arr, size_t index, k_valueType value) {
    if (index >= arr->size) {
        fprintf(stderr, "Error: Index out of bounds.\n");
        return;
    }

    // release old string or pointer type memory
    if (arr->data[index].value_type == k_string_t && arr->data[index].data.v_string != NULL) {
        free(arr->data[index].data.v_string);
    } else if (arr->data[index].value_type == k_ptr_t && arr->data[index].data.v_pointer != NULL) {
        free(arr->data[index].data.v_pointer);
    }
    arr->data[index] = value;
}

size_t k_dynamicArray_size(const k_dynamicArray *arr) {
    return arr->size;
}

size_t k_dynamicArray_capacity(const k_dynamicArray *arr) {
    return arr->capacity;
}

void k_dynamicArray_destroy(k_dynamicArray *arr) {
    if (arr) {
        for (size_t i = 0; i < arr->size; i++) {
            k_valueType_release(&arr->data[i]);
        }
        free(arr->data);
        free(arr);
    }
}

void k_dynamicArray_remove(k_dynamicArray *arr, size_t index) {
    if (index >= arr->size) {
        fprintf(stderr, "Error: Index out of bounds for removal.\n");
        return;
    }

    k_valueType_release(&arr->data[index]);

    // move subsequent elements forward
    for (size_t i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }

    arr->size--;
}