#include <stdarg.h>
#include <stdio.h>

#include "utils.h"

void print_repeat(int count, char *format, ...) {
    va_list args;
    va_start(args, format);

    va_list args_copy;

    for (int i = 0; i < count; i++) {
        va_copy(args_copy, args);
        vprintf(format, args_copy);
        va_end(args_copy);
    }

    va_end(args);
}
