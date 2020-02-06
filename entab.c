#include <stdio.h>
#include <string.h>
#include "files.h"

int main(int argc, const char* argv[]) {
  FILE* fin;
  FILE* fout;
  int tab_interval;

  bool ok = openfiles(argc, argv, &fin, &fout, &tab_interval, "Usage: ./entab inputfile outputfile tab_interval");
  if(!ok) { return 1; }

  int c, counter;
  counter = 0;

  // reads input file to replace blanks with tabs and blanks
  while((c = fgetc(fin)) != EOF) {
    if(c != '\t') {
      fputc(c, fout);
      counter++;
    } else {
      int ntabs = counter / tab_interval;
      int nspaces = counter % tab_interval;
      while(ntabs-- > 0) { fputc('\t', fout); }
      while(nspaces-- > 0) { fputc(' ', fout); }
      fputc(c, fout);
    }
  }

  closefiles(fin, fout);
  return 0;
}
