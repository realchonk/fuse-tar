#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "driver.h"

// TODO: implememt permission checking

int tar_access(const char* path, int mode) {
   return 0;
   if (!strcmp(path, "/")) return access(tar_path, mode);
   struct tar_header* hdr;
   if (tar_find(path + 1, &hdr, NULL)) return -errno;
   if (mode == F_OK) return 0;
   printf("uid=%u\n", (unsigned)geteuid());
   if ((mode & R_OK) == R_OK) {
      
   }
   return 0;
}
