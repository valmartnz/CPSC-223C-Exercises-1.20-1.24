#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool openfiles(int argc, const char* argv[], FILE** pfin, FILE** pfout, int* tab_interval, const char* usage) {
  if(argc < 3) {
    fprintf(stderr, "%s\n", usage);
    return false;
  }

  *pfin = fopen(argv[1], "r");
  if(*pfin == NULL) { return false; }
  *pfout = fopen(argv[2], "w");
  if(*pfout == NULL) {
    fclose(*pfout);
    return false;
  }

  if(argc == 4)
    *tab_interval = atoi(argv[3]);
  else
    *tab_interval = 10;

  return true;
}

void closefiles(FILE* pfin, FILE* pfout) {
  fclose(pfin);
  fclose(pfout);
}
