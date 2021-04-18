#ifndef FILE_TAR_H
#define FILE_TAR_H
#include <sys/stat.h>
#include <stddef.h>

struct tar_header {
   char tar_filename[100];
   char tar_mode[8];
   char tar_uid[8];
   char tar_gid[8];
   char tar_size[12];
   char tar_mtime[12];
   char tar_chksum[8];
   char tar_type;
   char tar_linked_name[100];
   char tar_ustar[6];
   char tar_ustar_ver[2];
   char tar_uname[32];
   char tar_gname[32];
   char tar_major[8];
   char tar_minor[8];
   char tar_prefix[155];
   char tar_padding[12];
};

extern void* tar_archive;
extern struct stat tar_st;

int tar_find(const char* path, struct tar_header** hdr, size_t* sz);
struct tar_header* tar_next(struct tar_header*);


#endif /* FILE_TAR_H */
