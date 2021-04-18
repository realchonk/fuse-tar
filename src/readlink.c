#include <errno.h>
#include "driver.h"

int tar_readlink(const char* path, char* linkbuf, size_t len_linkbuf) {
   struct tar_header* hdr;
   if (tar_find(path + 1, &hdr, NULL)) return -errno;
   if (hdr->tar_type == '2') {
      const size_t len_linked_name = strnlen(hdr->tar_linked_name, sizeof(hdr->tar_linked_name));
      strncpy(linkbuf, hdr->tar_linked_name, my_min(len_linkbuf - 1, len_linked_name));
   } else {
      const size_t len_filename = strnlen(hdr->tar_filename, sizeof(hdr->tar_filename));
      strncpy(linkbuf, hdr->tar_filename, my_min(len_linkbuf - 1, len_filename));
   }
   return 0;
}
