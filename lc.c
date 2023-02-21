/*
  * Program name: lc
  * Author: ElusiveNULL
  * Comments: I'm giving myself too much credit for writing something this simple, but it's the most complex program I've ever written by far.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argv[1] == NULL) {
    printf("No arguments provided. Try 'lc --help' for more information. Quitting.\n");
    return 0;
  }
  FILE *fd;
  char *filename;
  char bytelevel = ' ';
  int lines;
  float size;
  // Flag booleans
  int hflag = 0;
  // Check for flags
  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i],"--help")==0) {
      printf("\nlc: Count lines and bytes in files\nUsage: lc [OPTIONS] [FILES]\nor: lc [FILES] [OPTIONS]\n\nOptions:\n\t\t--help\t\t\tDisplay help message\n\t-h,\t--human-readable\tDisplay byte sizes in human readable sizes\n");
      return 0;
    }
    if (strcmp(argv[i],"-h")==0 || strcmp(argv[i], "--human-readable")==0) {
      hflag = 1;
    }
  }
  // Loop through arguments
  for (int fcount=1; fcount < argc; ++fcount) {
    if (argv[fcount][0] == '-') {
      continue;
    }
    filename = argv[fcount];
    fd = fopen(filename,"rb");
    // Check if file opened successfully
    if (fd == NULL) {
      printf("%s: File does not exist or cannot be accessed.\n", filename);
      continue;
    }
    // Get file size
    fseek(fd,0L, SEEK_END);
    size = ftell(fd);
    rewind(fd);
    // Get file line count
    lines = 0;
    for (char c = getc(fd); c != EOF; c = getc(fd)) {
      if (c == '\n') {
        lines++;
      }
    }
    // Make bytes human readable
    if (hflag) {
      bytelevel = ' ';
      int loopcheck = 1;
      while (size >= 1024 && loopcheck) {
        size /= 1024;
        switch(bytelevel) {
          case ' ':
            bytelevel = 'k';
            break;
          case 'k':
            bytelevel = 'M';
            break;
          case 'M':
            bytelevel = 'G';
            break;
          case 'G':
            bytelevel = 'T';
            break;
          case 'T':
            size *= 1024;
            loopcheck = 0;
            break;
          default:
            printf("Error: Unable to determine file size. Quitting.\n");
            return 1;
        }
      }
    }
    // Clean up
    rewind(fd);
    fclose(fd);
    if (bytelevel != ' ') {
      printf("%dL\t%0.2f%c\t%s\n",lines, size, bytelevel, filename);
    } else {
      printf("%dL\t%d\t%s\n",lines, (int) size, filename);
    }
  }
  return 0;
}
