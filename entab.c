#include <stdio.h>
#include <string.h>
#include "files.h"

int main(int argc, const char* argv[]) {
  FILE* fin;
  FILE* fout;
  int tab_interval;

  bool ok = openfiles(argc, argv, &fin, &fout, &tab_interval, "Usage: ./entab inputfile outputfile tab_interval");
  if(!ok) { return 1; }

  int c, nb, nt, position;
  nt = nb = 0;
  position = 1;

  // reads input file to replace blanks with tabs and blanks
  while((c = fgetc(fin)) != EOF) {
    if(c == ' ') {
      if((position % tab_interval) != 0)
        ++nb;
      else {
        nb = 0;
        ++nt;
      }
    } else{
      while(nt > 0) {
        fputc('\t', fout);
        --nt;
      }
      if(c == '\t') {
        nb = 0;
      } else {
        while (nb > 0) {
          fputc(' ', fout);
          --nb;
        }
      }
      fputc(c, fout);
      if(c == '\n')
        position = 0;
      else if(c == '\t')
        position = position + (tab_interval - (position - 1) % tab_interval) - 1;
    }
  }

  closefiles(fin, fout);
  return 0;
}
