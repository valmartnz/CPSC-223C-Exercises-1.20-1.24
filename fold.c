#include<stdio.h>
#include<stdbool.h>
#include "files.h"

#define MAXLINE 50

char line[MAXLINE];
int expandtab(int pos, int tab_interval, FILE* fout);
void printline(int pos, FILE* fout);
int addblank(int pos);
int newpos(int pos);

int main(int argc, const char* argv[]) {
  FILE* fin;
  FILE* fout;
  int tab_interval;

  bool ok = openfiles(argc, argv, &fin, &fout, &tab_interval, "Usage: ./fold inputfile outputfile tab_interval");
  if(!ok) { return 1; }
    
  int position,c;
  position = 0;

    while((c=fgetc(fin))!=EOF) {
      line[position] = c;

      if( c == '\t')
        position = expandtab(position, tab_interval, fout);
      if( c == '\n') {
        printline(position, fout);
          position = 0;
      } else if( ++position >= MAXLINE ) {
          position = addblank(position);
          printline(position, fout);
          position = newpos(position);
        }
    }
    return 0;
}

int expandtab(int pos, int tab_interval, FILE* fout) {
    line[pos] = ' ';

    for(++pos; (pos < MAXLINE)&&((pos % tab_interval)!= 0); ++pos)
    line[pos] = ' ';

    if(pos >= MAXLINE) {
      printline(pos, fout);
      return 0;
    }
    else
        return pos;
}

void printline(int position, FILE* fout) {
    int i;
    for(i = 0; i < position; ++i){
        fputc(line[i], fout);
    }
    if(position > 0) {
        fputc('\n', fout);
    }
}

int getblank(int pos) {
  if(pos > 0)
    while( line[pos] != ' ')
       --pos;
  if(pos == 0)
    return MAXLINE;
  else
    return pos + 1;
}
int newposition( int pos) {
  int i,j;

  if(pos <= 0 || pos >= MAXLINE)
    return 0;
  else {
    i = 0;
    for(j=pos;j < MAXLINE; ++j,++i)
       line[i] = line[j];  
  }
    return i;
}
