#ifndef FILE_DRIVER_H
#define FILE_DRIVER_H
#define FUSE_USE_VERSION 29
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <fuse.h>
#include "util.h"
#include "tar.h"

inline static bool is_rootent(const char* path) {
   const char* s = strchr(path, '/');
   return !s || !s[1];
}
inline static bool is_entry(const char* dir, const char* ent) {
   const size_t len_dir = strlen(dir);
   size_t len_ent = strlen(ent);
   if (len_dir >= len_ent) return false;
   if (ent[len_ent - 1] == '/') --len_ent;
   const char* end_ent = strrrchr(ent + len_ent - 1, '/') + 1;
   const size_t len_end = end_ent - ent;
   if (len_end != len_dir) return false;
   return !memcmp(dir, ent, len_end);
}

extern struct fuse_operations tar_fuse_ops;

int tar_getattr(const char*, struct stat*);
int tar_readdir(const char*, void*, fuse_fill_dir_t, off_t, struct fuse_file_info*);
int tar_access(const char*, int);
int tar_read(const char*, char*, size_t, off_t, struct fuse_file_info*);
int tar_readlink(const char*, char*, size_t);
int tar_open(const char*, struct fuse_file_info*);
int tar_opendir(const char*, struct fuse_file_info*);
void tar_destroy(void*);

// stubs
int tar_mknod(const char* path, mode_t mode, dev_t dev);
int tar_mkdir(const char* path, mode_t mode);
int tar_unlink(const char* path);
int tar_symlink(const char* p1, const char* p2);
int tar_rename(const char* p1, const char* p2, unsigned flags);
int tar_chmod(const char* path, mode_t mode);
int tar_create(const char* path, mode_t mode, struct fuse_file_info* fi);
int tar_chown(const char* path, uid_t uid, gid_t gid);
int tar_truncate(const char* path, off_t off);
int tar_write(const char* path, const char* data, size_t num, off_t off, struct fuse_file_info* fi);
int tar_fallocate(const char* path, int i, off_t o1, off_t o2, struct fuse_file_info* fi);
int tar_setxattr(const char* path, const char* name, const char* value, size_t len_value, int flags);
int tar_getxattr(const char* path, const char* name, char* value, size_t len_value);
int tar_listxattr(const char* path, char* list, size_t len_list);
int tar_removexattr(const char* path, const char* name);
int tar_release(const char* path, struct fuse_file_info* fi);

#endif /* FILE_DRIVER_H */
