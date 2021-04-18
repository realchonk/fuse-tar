#ifndef FILE_UTIL_H
#define FILE_UTIL_H
#include <sys/types.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#define my_min(a, b) ((a) < (b) ? (a) : (b))
#define my_max(a, b) ((a) > (b) ? (a) : (b))

ssize_t read_file(const char* filename, void** data, struct stat* st);
size_t parse_octal(const char* str, size_t num);
void error(const char*, ...);
bool starts_with(const char* s, const char* begin);
char* strrrchr(const char* s, char ch);

#define parse_octala(a) parse_octal((a), sizeof(a))

#endif /* FILE_UTIL_H */
