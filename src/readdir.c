#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "driver.h"

int tar_readdir(const char* path, void* buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info* fi) {
   (void)offset;
   (void)fi;
   struct tar_header* hdr;
   if (!strcmp(path, "/")) {
      filler(buffer, ".", NULL, 0);
      filler(buffer, "..", NULL, 0);
      hdr = tar_archive;
      do {
         if (!is_rootent(hdr->tar_filename)) continue;
         if (hdr->tar_type == '5') {
            const size_t len_name = strnlen(hdr->tar_filename, sizeof(hdr->tar_filename));
            char* name = malloc(len_name);
            if (!name) return -ENOMEM;
            memcpy(name, hdr->tar_filename, len_name - 1);
            name[len_name - 1] = '\0';
            puts(name);
            filler(buffer, name, NULL, 0);
         } else filler(buffer, hdr->tar_filename, NULL, 0);
      } while ((hdr = tar_next(hdr)) != NULL);
      return 0;
   }
   if (tar_find(path + 1, &hdr, NULL)) return -errno;
   else if (hdr->tar_type != '5') return -ENOTDIR;
   filler(buffer, ".", NULL, 0);
   filler(buffer, "..", NULL, 0);
   
   struct tar_header* tmp = tar_archive;
   do {
      if (tmp != hdr && is_entry(hdr->tar_filename, tmp->tar_filename)) {
         if (tmp->tar_type == '5') {
            const char* begin = strrrchr(strrchr(tmp->tar_filename, '/') - 1, '/') + 1;
            const size_t len_str = strlen(begin) - 1;
            char* str = malloc(len_str + 1);
            memcpy(str, begin, len_str);
            str[len_str] = '\0';
            filler(buffer, str, NULL, 0);
         } else filler(buffer, strrchr(tmp->tar_filename, '/') + 1, NULL, 0);
      }
   } while ((tmp = tar_next(tmp)) != NULL);

   return 0;
}
