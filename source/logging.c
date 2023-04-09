#include <stdio.h>
#include <stdarg.h>

#include "logging.h"

void sendf(char *logtype, char *format, ...) {
    va_list arglist;
    va_start(arglist, format);
    
    printf("[%s]: ", logtype);

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++;

            if (format[i] == 'd') {
                int value = va_arg(arglist, int);
                printf("%d", value);
            } else if (format[i] == 's') {
                char *str = va_arg(arglist, char*);
                printf("%s", str);
            }
        } else {
            putchar(format[i]);
        }
    }

    va_end(arglist);
}