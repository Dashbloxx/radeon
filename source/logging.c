#include <stdio.h>
#include <stdarg.h>

#include "logging.h"

void sendf(char *logtype, char *format, ...) {
    va_list args;
    va_start(args, format);

    printf("[%s]: ", logtype);
    vprintf(format, args);

    va_end(args);
}