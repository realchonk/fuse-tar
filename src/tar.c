#include <string.h>
#include <errno.h>
#include "util.h"
#include "tar.h"


int tar_find(const char* path, struct tar_header** hdr, size_t* sz) {
   const size_t len_path = strlen(path);
   struct tar_header* ptr = tar_archive;
   while (!memcmp(ptr->tar_ustar, "ustar", 5)) {
      const size_t filesz = parse_octal(ptr->tar_size, sizeof(ptr->tar_size));
      size_t len_fn = strnlen(ptr->tar_filename, sizeof(ptr->tar_filename));
      if (ptr->tar_filename[len_fn - 1] == '/') --len_fn;
      if (len_path == len_fn && !memcmp(path, ptr->tar_filename, len_path)) {
         if (hdr) *hdr = ptr;
         if (sz) *sz = filesz;
         return 0;
      }
      ptr = (void*)((size_t)ptr + ((((filesz + 511) / 512) + 1) * 512));
   }
   errno = ENOENT;
   return -1;
}

struct tar_header* tar_next(struct tar_header* hdr) {
   //if (memcmp(hdr->tar_ustar, "ustar", 5)) return NULL;
   if (!hdr) return NULL;
   const size_t filesz = parse_octal(hdr->tar_size, sizeof(hdr->tar_size));
   hdr = (void*)((size_t)hdr + ((((filesz + 511) / 512) + 1) * 512));
   return !memcmp(hdr->tar_ustar, "ustar", 5) ? hdr : NULL;
}

