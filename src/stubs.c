#include <errno.h>
#include "driver.h"

int tar_mknod(const char* path, mode_t mode, dev_t dev) {
   (void)path;
   (void)mode;
   (void)dev;
   return -EROFS;
}
int tar_mkdir(const char* path, mode_t mode) {
   (void)path;
   (void)mode;
   return -EROFS;
}
int tar_unlink(const char* path) {
   (void)path;
   return -EROFS;
}
int tar_symlink(const char* p1, const char* p2) {
   (void)p1;
   (void)p2;
   return -EROFS;
}
int tar_rename(const char* p1, const char* p2, unsigned flags) {
   (void)p1;
   (void)p2;
   (void)flags;
   return -EROFS;
}
int tar_chmod(const char* path, mode_t mode) {
   (void)path;
   (void)mode;
   return -EROFS;
}
int tar_create(const char* path, mode_t mode, struct fuse_file_info* fi) {
   (void)path;
   (void)mode;
   (void)fi;
   return -EROFS;
}
int tar_chown(const char* path, uid_t uid, gid_t gid) {
   (void)path;
   (void)uid;
   (void)gid;
   return -EROFS;
}
int tar_truncate(const char* path, off_t off) {
   (void)path;
   (void)off;
   return -EROFS;
}
int tar_write(const char* path, const char* data, size_t num, off_t off, struct fuse_file_info* fi) {
   (void)path;
   (void)data;
   (void)num;
   (void)off;
   (void)fi;
   return -EROFS;
}
int tar_fallocate(const char* path, int i, off_t o1, off_t o2, struct fuse_file_info* fi) {
   (void)path;
   (void)i;
   (void)o1;
   (void)o2;
   (void)fi;
   return -EROFS;
}
int tar_setxattr(const char* path, const char* name, const char* value, size_t len_value, int flags) {
   (void)path;
   (void)name;
   (void)value;
   (void)len_value;
   (void)flags;
   return -ENOTSUP;
}
int tar_getxattr(const char* path, const char* name, char* value, size_t len_value) {
   (void)path;
   (void)name;
   (void)value;
   (void)len_value;
   return -ENOTSUP;
}
int tar_listxattr(const char* path, char* list, size_t len_list) {
   (void)path;
   (void)list;
   (void)len_list;
   return -ENOTSUP;
}
int tar_removexattr(const char* path, const char* name) {
   (void)path;
   (void)name;
   return -ENOTSUP;
}

