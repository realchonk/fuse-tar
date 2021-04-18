#include <stdlib.h>
#include "driver.h"
#include "tar.h"

static void tar_destroy(void* priv) {
   (void)priv;
   free(tar_archive);
}

struct fuse_operations tar_fuse_ops = {
   .getattr = tar_getattr,
   .readdir = tar_readdir,
   .access = tar_access,
   .read = tar_read,
   .readlink = tar_readlink,

   .mknod = tar_mknod,
   .mkdir = tar_mkdir,
   .unlink = tar_unlink,
   .rmdir = tar_unlink,
   .symlink = tar_symlink,
   .link = tar_symlink,
   .rename = tar_symlink,
   .chmod = tar_chmod,
   .chown = tar_chown,
   .truncate = tar_truncate,
   .write = tar_write,
   .create = tar_create,
   .fallocate = tar_fallocate,

   .destroy = tar_destroy,
};

