#include <unistd.h>
#include <errno.h>
#include "driver.h"

int tar_access(const char* path, int mode) {
   struct tar_header* hdr;
   if (tar_find(path + 1, &hdr, NULL)) return -errno;
   if (mode == F_OK) return 0;
   return 0;
}
