#include <stdio.h>
#include <string.h>
#include "files.h"

int main(int argc, const char* argv[]) {
  FILE* fin;
  FILE* fout;
  int n;

  bool ok = openfiles(argc, argv, &fin, &fout, &tab_interval, "Usage: ./detab inputfile outputfile n");
  if(!ok) { return 1; }

  int c, nc, position;
  nb = position = 0;

  // reads input file to remove comments
  while((c = fgetc(fin)) != EOF) {
    if(c == '/') {
      if((nc = fgetc(fin)) == '*') {
        while(c != '*' || nc != '/') {
          c = nc;
          nc = fgetc(fin);
        }
      } else if((nc = fgetc(fin)) == '/') {
        while(c != '*' || nc != '/') {
          c = nc;
          nc = fgetc(fin);
        }
    } // 
  }

  closefiles(fin, fout);
  return 0;
}
