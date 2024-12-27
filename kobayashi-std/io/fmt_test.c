#include "fmt.h"

int main() {
    k_valueType v1, v2, v3;
    k_valueType_init(&v1, k_int32_t);
    k_valueType_set_int32(&v1, 42);

    k_valueType_init(&v2, k_string_t);
    k_valueType_set_string(&v2, "Hello, World!");

    k_valueType_init(&v3, k_bool_t);
    k_valueType_set_bool(&v3, True);

    // 正确格式
    int result = k_fmt("Integer: {0}, String: {1}, Boolean: {2}\n", &v1, &v2, &v3);
    if (result == -1) {
        printf("\nError: Invalid format string!\n");
    }

    // 错误格式
    result = k_fmt("Integer: {0}, Invalid: {2}\n", &v1, &v2, &v3);
    if (result == -1) {
        printf("\nError: Invalid format string!\n");
    }

    return 0;
}
