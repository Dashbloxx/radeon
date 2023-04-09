#pragma once

#define LOG_INFO "\033[1mINFO\033[0m"
#define LOG_ERROR "\033[1mERROR\033[0m"
#define LOG_WARN "\033[1mWARN\033[0m"

/* Use this for logging... This will just print out to `stdout`... */
void sendf(char *logtype, char *format, ...);