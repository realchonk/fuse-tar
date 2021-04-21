#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "util.h"

static int invoke_decomp(const char* decomp, const char* infile, const char* outfile) {
   char* str;
   // TODO: Find alternative for asprintf
   if (asprintf(&str, "%s -c -d %s > %s", decomp, infile, outfile) <= 0) {
      errno = ENOMEM;
      return -1;
   }
   puts(str);
   const int ec = system(str);
   free(str);
   return ec;
}

struct decomp_pair {
   const char* ending;
   const char* program;
};

static struct decomp_pair decomps[] = {
   { ".gz", "gzip"   },
   { ".xz", "xz"     },
   { ".bz2","bzip2"  },
   { ".lz4","lz4"    },
   { ".zst","zstd"   },
};

int decompress_file(const char* infile, const char* outfile) {
   for (size_t i = 0; i < arraylen(decomps); ++i) {
      if (ends_with(infile, decomps[i].ending)) {
         errno = 0;
         const int r = invoke_decomp(decomps[i].program, infile, outfile);
         if (r && !errno) errno = ENOENT;
         return r;
      }
   }
   errno = EINVAL;
   return -1;
}


