#include <stdio.h>
#include <string.h>
#include "files.h"

int main(int argc, const char* argv[]) {
  FILE* fin;
  FILE* fout;
  int n;

  bool ok = openfiles(argc, argv, &fin, &fout, &n, "Usage: ./unbalancedsyntax inputfile outputfile n");
  if(!ok) { return 1; }

  int c, p, b, cb;
  p = b = cb = 0;
  int dq, sq, comment;
  dq = sq = comment = 1;

  // reads input file to check if syntax is balanced
  while((c = fgetc(fin)) != EOF) {
    if(c == '(')
      p++;
    if(c == '[')
      b++;
    if(c == '{')
      cb++;
    if(c == '"')
      dq *= -1;
    if(c == '\'')
      sq *= -1;
    if(c == '/') {
      if((c = fgetc(fin)) == '*'){
        comment *= -1;
      }
    }
    if(c == '*') {
      if((c = fgetc(fin)) == '/'){
        comment *= -1;
      }
    }
    if(c == ')')
      p--;
    if(c == ']')
      b--;
    if(c == '}')
      cb--;
  }
  if(p != 0)
    printf("Unmatched paranthesis\n");
  if(b != 0)
    printf("Unmatched bracket\n");
  if(cb != 0)
    printf("Unmatched curly brace\n");
  if(dq != 1)
    printf("Unmatched double quote\n");
  if(sq != 1)
    printf("Unmatched single quote\n");
  if(comment != 1)
    printf("Unmatched comment\n");

  closefiles(fin, fout);
  return 0;
}
