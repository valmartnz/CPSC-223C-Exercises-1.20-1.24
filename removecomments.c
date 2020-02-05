#include <stdio.h>
#include <string.h>
#include "files.h"

int main(int argc, const char* argv[]) {
  FILE* fin;
  FILE* fout;
  int n;

  bool ok = openfiles(argc, argv, &fin, &fout, &n, "Usage: ./removecomments inputfile outputfile n");
  if(!ok) { return 1; }

  int c, nc, position;
  //nb = position = 0;

  // reads input file to remove comments
  while((c = fgetc(fin)) != EOF) {
    if(c == '/') {
      if((nc = fgetc(fin)) == '*') {
        while(c != '*' || nc != '/') {
          c = nc;
          nc = fgetc(fin);
        }
      } else if((nc = fgetc(fin)) == '/') {
        while(c != '/' || nc != '/') {
          c = nc;
          nc = fgetc(fin);
        }
    } else {
      fputc(c, fout);
      fputc(nc, fout);
    }
  } else if(c == '"' || c == '\'') {
    fputc(c, fout);
    while((nc = fgetc(fin)) != c) {
      fputc(nc, fout);
      if(nc == '\\') {
        fputc(fgetc(fin), fout);
      }
    }
    fputc(nc, fout);
  }
}

  closefiles(fin, fout);
  return 0;
}
