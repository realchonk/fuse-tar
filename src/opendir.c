#include <errno.h>
#include "driver.h"

// TODO: implement permission checking

int tar_opendir(const char* path, struct fuse_file_info* fi) {
   (void)fi;
   struct tar_header* hdr;
   if (tar_find(path + 1, &hdr, NULL)) return -errno;
   else if (hdr->tar_type != '5') return -ENOTDIR;

   return 0;
}
