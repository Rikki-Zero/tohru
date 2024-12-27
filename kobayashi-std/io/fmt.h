#ifndef kobayashi_std__io__fmt_h
#define kobayashi_std__io__fmt_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <assert.h>
#include "../types/valueType.h"

int k_fmt_validate_format(const char *format, int param_count);
int k_fmt(const char *format, ...);

#endif