#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "driver.h"
#include "util.h"

const char* tar_path = NULL;
void* tar_archive = NULL;
struct stat tar_st;
static struct mmap_file_result mmap_file_result;
static char tempfile[L_tmpnam + 1];
static bool has_tempfile;

int main(int argc, char* argv[]) {
   int i;

   for (i = 1; i < argc && argv[i][0] == '-'; ++i);
   if ((argc - i) < 2) {
      fputs("Usage: fuse_tar <tar-archive> <mount-point>\n", stderr);
      return 1;
   }

   tar_path = argv[i];
   if (ends_with(tar_path, ".tar")) {
      if (mmap_file(tar_path, &mmap_file_result) != 0) {
         fprintf(stderr, "fuse_tar: failed to read '%s': %s\n", tar_path, strerror(errno));
         return 1;
      }
      has_tempfile = false;
   } else {
      // TODO: Replace tmpnam with mkstemp
      if (tmpnam(tempfile) == NULL) {
         fprintf(stderr, "fuse_tar: failed to create temporary file: %s\n", strerror(errno));
         return 1;
      }
      if (decompress_file(tar_path, tempfile) != 0) {
         fprintf(stderr, "fuse_tar: failed to decompress file '%s': %s\n", tar_path, strerror(errno));
         return 1;
      }
      if (mmap_file(tempfile, &mmap_file_result) != 0) {
         fprintf(stderr, "fuse_tar: failed to read '%s': %s\n", tempfile, strerror(errno));
         return 1;
      }
      has_tempfile = true;
      tar_path = tempfile;
   }
   tar_archive = mmap_file_result.data;
   const ssize_t sz = read_file(tar_path, &tar_archive, &tar_st);
   if (sz < 0) {
      error("failed to read '%s'", tar_path);
      return 1;
   }

   memcpy(&argv[i], &argv[i + 1], (argc - i) * sizeof(char*));
   --argc;

   return fuse_main(argc, argv, &tar_fuse_ops, NULL);
}

void tar_destroy(void* priv) {
   (void)priv;
   munmap(mmap_file_result.data, mmap_file_result.real_size);
   close(mmap_file_result.fd);
   remove(tempfile);
}

