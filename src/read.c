#include <errno.h>
#include "driver.h"

int tar_read(const char* path, char* buffer, size_t num, off_t off, struct fuse_file_info* fi) {
   (void)fi;
   struct tar_header* hdr;
   size_t sz;
   if (tar_find(path + 1, &hdr, &sz)) return -errno;
   size_t rd;
   if ((size_t)off >= sz) rd = 0;
   else if ((off + num) >= sz) rd = sz - off;
   else rd = num;
   memcpy(buffer, (const void*)(hdr + 1), rd);
   memset(buffer + rd, 0, num - rd);
   return rd;
}

