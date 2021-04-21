#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include "util.h"

ssize_t read_file(const char* filename, void** data, struct stat* to_st) {
   if (!filename || !data) {
      errno = EINVAL;
      return -1;
   }
   const int fd = open(filename, O_RDONLY);
   if (fd < 0) return -1;
   struct stat st;
   if (fstat(fd, &st) != 0) return -1;
   if (to_st) *to_st = st;
   if ((st.st_mode & S_IFMT) != S_IFREG) {
      errno = ENOENT;
      close(fd);
      return -1;
   }
   
   void* buffer = malloc(st.st_size);
   if (!buffer) return close(fd), -1;

   const ssize_t num = read(fd, buffer, st.st_size);
   close(fd);

   *data = buffer;

   return num;
}

size_t parse_octal(const char* str, size_t num) {
   size_t val = 0;
   for (size_t i = 0; i < num && isdigit(str[i]); ++i)
      val = val * 8 + (str[i] - '0');
   return val;
}

void error(const char* fmt, ...) {
   va_list ap;
   va_start(ap, fmt);

   fputs("fuse_tar: ", stderr);
   vfprintf(stderr, fmt, ap);
   fprintf(stderr, ": %s\n", strerror(errno));

   va_end(ap);
}

bool starts_with(const char* s, const char* b) {
   const size_t len_s = strlen(s);
   const size_t len_b = strlen(b);
   return len_s >= len_b ? !memcmp(s, b, len_b) : false;
}
bool ends_with(const char* s, const char* e) {
   const size_t len_s = strlen(s);
   const size_t len_e = strlen(e);
   return len_s >= len_e ? !memcmp(s + (len_s - len_e), e, len_e) : false;
}

char* strrrchr(const char* s, char ch) {
   while (*s != ch) --s;
   return (char*)s;
}


static size_t resizeto_pagesize(size_t num) {
   const long page_size = sysconf(_SC_PAGE_SIZE);
   return (num - (num % page_size)) + page_size;
}
int mmap_fd(int fd, struct mmap_file_result* result) {
   int tmp;
   struct stat st;
   if (fstat(fd, &st) != 0) return tmp = errno, close(fd), errno = tmp, -1;
   const size_t size = resizeto_pagesize(st.st_size);
   void* ptr = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);   
   if (!ptr) return tmp = errno, close(fd), errno = tmp, -1;
   result->data = ptr;
   result->st = st;
   result->fd = fd;
   result->real_size = size;
   return 0;
}
int mmap_file(const char* path, struct mmap_file_result* result) {
   int fd = open(path, O_RDONLY);
   if (fd < 0) return -1;
   return mmap_fd(fd, result);
}

