#include <stdio.h>
#include <string.h>
#include "files.h"

int main(int argc, const char* argv[]) {
  FILE* fin;
  FILE* fout;
  int tab_interval;

  bool ok = openfiles(argc, argv, &fin, &fout, &tab_interval, "Usage: ./detab inputfile outputfile tab_interval");
  if(!ok) { return 1; }

  int c, nb, position;
  nb = position = 0;

  // reads input file to remove tabs and replace them with blank spaces
  while((c = fgetc(fin)) != EOF) {
    if(c == '\t') {
      nb = tab_interval - (position % tab_interval);
      while(nb > 0) {
        fputc(' ', fout);
        ++position;
        --nb;
      }
    } else if(c == '\n') {
      fputc(c, fout);
      position = 1;
    } else {
      fputc(c, fout);
      ++position;
    }
  }

  closefiles(fin, fout);
  return 0;
}
