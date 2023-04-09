#pragma once

#define LOG_INFO "\033[1mINFO\033[0m"
#define LOG_ERROR "\x1b[31;1mERROR\033[0m"
#define LOG_WARN "\x1b[33;1mWARN\033[0m"
#define LOG_DEBUG "\x1b[34;1mDEBUG\033[0m"

/* Use this for logging... This will just print out to `stdout`... */
void sendf(char *logtype, char *format, ...);