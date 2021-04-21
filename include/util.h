#ifndef FILE_UTIL_H
#define FILE_UTIL_H
#include <sys/types.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#define arraylen(a) (sizeof(a) / sizeof(a[0]))
#define my_min(a, b) ((a) < (b) ? (a) : (b))
#define my_max(a, b) ((a) > (b) ? (a) : (b))

ssize_t read_file(const char* filename, void** data, struct stat* st);
size_t parse_octal(const char* str, size_t num);
void error(const char*, ...);
bool starts_with(const char* s, const char* begin);
bool ends_with(const char* s, const char* end);
char* strrrchr(const char* s, char ch);

struct mmap_file_result {
   struct stat st;
   void* data;
   int fd;
   size_t real_size;
};
int mmap_fd(int fd, struct mmap_file_result*);
int mmap_file(const char* path, struct mmap_file_result*);

#define parse_octala(a) parse_octal((a), sizeof(a))

int decompress_file(const char* infile, const char* outfile);

#endif /* FILE_UTIL_H */
