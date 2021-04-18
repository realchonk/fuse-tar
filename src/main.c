#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "driver.h"
#include "util.h"

void* tar_archive = NULL;
struct stat tar_st;

int main(int argc, char* argv[]) {
   int i;

   for (i = 1; i < argc && argv[i][0] == '-'; ++i);
   if ((argc - i) < 2) {
      fputs("Usage: fuse_tar <tar-archive> <mount-point>\n", stderr);
      return 1;
   }

   const char* path = argv[i];
   const ssize_t sz = read_file(path, &tar_archive, &tar_st);
   if (sz < 0) {
      error("failed to read '%s'", path);
      return 1;
   }

   memcpy(&argv[i], &argv[i + 1], (argc - i) * sizeof(char*));
   --argc;

   return fuse_main(argc, argv, &tar_fuse_ops, NULL);
}


