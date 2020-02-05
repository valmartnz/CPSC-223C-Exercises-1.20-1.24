#include <stdio.h>
#include <string.h>
#include "files.h"

#define MAXLINE 1000

char line[MAXLINE];
int gline(void);

int main(int argc, const char* argv[]) {
  FILE* fin;
  FILE* fout;
  int tab_interval;

  bool ok = openfiles(argc, argv, &fin, &fout, &tab_interval, "Usage: ./detab inputfile outputfile tab_interval");
  if(!ok) { return 1; }

  int c, t, nb, length, position;

  closefiles(fin, fout);
  return 0;
}
