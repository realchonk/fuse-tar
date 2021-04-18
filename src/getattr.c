#include <errno.h>
#include "driver.h"

int tar_getattr(const char* path, struct stat* st) {
   if (!strcmp(path, "/")) {
      st->st_mode = S_IFDIR | 0755;
      st->st_size = 512;
      st->st_nlink = 2;
      st->st_uid = tar_st.st_uid;
      st->st_gid = tar_st.st_gid;
      st->st_atim = tar_st.st_atim;
      st->st_mtim = tar_st.st_mtim;
      st->st_ctim = tar_st.st_ctim;
      struct tar_header* hdr = tar_archive;
      do {
         if (hdr->tar_type == '5' && is_rootent(hdr->tar_filename)) ++st->st_nlink;
      } while ((hdr = tar_next(hdr)) != NULL);
      return 0;
   } else {
      struct tar_header* hdr;
      size_t sz;
      if (tar_find(path + 1, &hdr, &sz)) return -ENOENT;
      st->st_mode = parse_octala(hdr->tar_mode);
      st->st_size = sz;
      st->st_nlink = 1;
      st->st_uid = parse_octala(hdr->tar_uid);
      st->st_gid = parse_octala(hdr->tar_gid);
      st->st_mtime = parse_octala(hdr->tar_mtime);
      switch (hdr->tar_type) {
      case '\0':
      case '0':
      case '1':
         st->st_mode |= S_IFREG;
         st->st_size = sz;
         break;
      case '2':
         st->st_mode |= S_IFLNK;
         break;
      case '3':
         st->st_mode |= S_IFCHR;
         break;
      case '4':
         st->st_mode |= S_IFBLK;
         break;
      case '5': {
         st->st_mode |= S_IFDIR;
         ++st->st_nlink;
         st->st_size = 512;
         struct tar_header* tmp = hdr;
         while ((tmp = tar_next(tmp)) != NULL) {
            if (tmp->tar_type == '5' && is_entry(hdr->tar_filename, tmp->tar_filename))
               ++st->st_nlink;
         }
         
         break;
         }
      case '6':
         st->st_mode |= S_IFIFO;
         break;
      }
      return 0;
   }

}


