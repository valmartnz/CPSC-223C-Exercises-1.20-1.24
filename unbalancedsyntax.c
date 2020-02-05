#include <stdio.h>
#include <string.h>
#include "files.h"

int main(int argc, const char* argv[]) {
  FILE* fin;
  FILE* fout;
  int n;

  bool ok = openfiles(argc, argv, &fin, &fout, &n, "Usage: ./unbalancedsyntax inputfile outputfile n");
  if(!ok) { return 1; }

  int p, b, cb;
  p = b = cb = 0;

  // reads input file to check if syntax is balanced
  while((c = fgetc(fin)) != EOF) {
    if(c == '(')
      p++;
    if(c == '[')
      b++;
    if(c == '{')
      cb++;
    if(c == ')')
      p--;
    if(c == ']')
      b--;
    if(c == '}')
      cb--:
  }
  if(p > 0 || p < 0)
    printf("Unbalanced paranthesis\n");
  if(b > 0 || b < 0)
    printf("Unbalanced bracket\n");
  if(cb > 0; || cb < 0)
    printf("Unbalanced curly brace\n");

  closefiles(fin, fout);
  return 0;
}
