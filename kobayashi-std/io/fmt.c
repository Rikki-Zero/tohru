#include "fmt.h"

int k_fmt_validate_format(const char *format, int param_count) {
    const char *ptr = format;

    while (*ptr) {
        if (*ptr == '{') {
            ptr++;  // skip '{'
            int index = -1;

            // if it is a number, parse this index 
            if (isdigit(*ptr)) {
                index = 0;
                while (isdigit(*ptr)) {
                    index = index * 10 + (*ptr - '0');
                    ptr++;
                }
            }

            if (*ptr == '}' && index >= 0) {
                // check if the index exceeds the number of arguments
                if (index >= param_count) {
                    return -1;
                }
                ptr++; // skip '}'
            } else {
                return -1;
            }
        } else {
            ptr++;
        }
    }

    return 0;
}

int k_fmt(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // check the number of passed arguments
    const char *ptr = format;
    int param_count = 0;
    while (va_arg(args, k_valueType *)) {
        param_count++;
    }
    va_end(args);


    va_start(args, format);
    ptr = format;
    int auto_index = 0; // auto-increment the index

    while (*ptr) {
        if (*ptr == '{') {
            ptr++; // skip '{'

            int index = -1;
            if (isdigit(*ptr)) {
                index = 0;
                while (isdigit(*ptr)) {
                    index = index * 10 + (*ptr - '0');
                    ptr++;
                }
            } else {
                index = auto_index++;
            }

            if (*ptr == '}' && index >= 0) {
                ptr++;

                if (index >= param_count) {
                    va_end(args);
                    return -1;
                }

                va_list temp_args;
                va_copy(temp_args, args);
                for (int i = 0; i < index; i++) {
                    va_arg(temp_args, k_valueType *);
                }
                k_valueType *value = va_arg(temp_args, k_valueType *);
                va_end(temp_args);

                switch (value->value_type) {
                    case k_int8_t:
                        printf("%d", (int)k_valueType_get_int8(value));
                        break;
                    case k_int16_t:
                        printf("%d", (int)k_valueType_get_int16(value));
                        break;
                    case k_int32_t:
                        printf("%d", k_valueType_get_int32(value));
                        break;
                    case k_int64_t:
                        printf("%lld", (long long)k_valueType_get_int64(value));
                        break;
                    case k_uint8_t:
                        printf("%u", (unsigned int)k_valueType_get_uint8(value));
                        break;
                    case k_uint16_t:
                        printf("%u", (unsigned int)k_valueType_get_uint16(value));
                        break;
                    case k_uint32_t:
                        printf("%u", k_valueType_get_uint32(value));
                        break;
                    case k_uint64_t:
                        printf("%llu", (unsigned long long)k_valueType_get_uint64(value));
                        break;
                    case k_float32_t:
                        printf("%f", k_valueType_get_float32(value));
                        break;
                    case k_float64_t:
                        printf("%lf", k_valueType_get_float64(value));
                        break;
                    case k_char_t:
                        printf("%c", k_valueType_get_char(value));
                        break;
                    case k_string_t:
                        printf("%s", k_valueType_get_string(value));
                        break;
                    case k_bool_t:
                        printf("%s", k_valueType_get_bool(value) ? "true" : "false");
                        break;
                    case k_ptr_t:
                        printf("%p", k_valueType_get_ptr(value));
                        break;
                    default:
                        printf("<unsupported type>");
                }
            } else {
                va_end(args);
                return -1;
            }
        } else {
            putchar(*ptr);
            ptr++;
        }
    }

    va_end(args);
    return 0;
}