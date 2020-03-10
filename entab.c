#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXLEN 1000
#define MAXLINES 5000
#define ALLOCSIZE 10000 /* size of available space */

char* lineptr[MAXLINES];

int readlines(char* lineptr[], int nlines);
void writelines(char* lineptr[], int nlines);
void qsort_(char* lineptr[], int left, int right); //index qsort pg 253 under stdlib.h add to strings
void swap_(char* v[], int i, int j);
char* alloc(int);
int getline_(char*, int);

static char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *allocp = allocbuf;   /* next free position */
FILE* fin;
FILE* fout;

bool openfiles(int argc, const char* argv[], FILE** pfin, FILE** pfout, const char* usage) {
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
  return true;
}

void closefiles(FILE* pfin, FILE* pfout) {
  fclose(pfin);
  fclose(pfout);
}

int main(int argc, const char* argv[]) {
  bool ok = openfiles(argc, argv, &fin, &fout, "Usage: ./lyrics inputfile outputfile");
  if(!ok) { return 1; }

  int nlines;

    if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
      qsort_(lineptr, 0, nlines - 1);
      writelines(lineptr, nlines);
      return 0;
    } else {
      printf("error: input too big to sort\n");
      return 1;
    }

  closefiles(fin, fout);
  return 0;
}

char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
    allocp += n;
    return allocp - n; /* old p */
  } else {
    return 0;
  }
}

int readlines(char *lineptr[], int maxlines) {
  int len, nlines;
  char *p, line[MAXLEN];
  nlines = 0;

  while((len = getline_(line, MAXLEN)) > 0)
    if(nlines >= maxlines || (p = alloc(len)) == NULL)
       return -1;
    else {
       line[len-1] = '\0'; /* delete newline */
       strcpy(p, line);
       lineptr[nlines++] = p;
    }
  return nlines;
}

int getline_(char *s, int lim) {
  int c;
  char *t = s;

  while(--lim > 0 && (c = fgetc(fin)) != EOF && c!='\n')
    *s++ = c;
  if(c == '\n')
    *s++ = c;

  *s = '\0';

  return s-t;
}

void writelines(char *lineptr[],  int nlines) {
  while (nlines-- > 0) {
    printf("%s\n", *lineptr++);
    fprintf(fout, "%s\n", *lineptr);
  }
}

void qsort_(char *v[],  int left, int right) {
  int i, last;
  void swap_(char *v[], int i, int j);

  if (left >= right)   /* do nothing if array contains */
    return;           /* fewer than two elements */

  swap_(v, left, (left + right)/2);
  last = left;

  for (i = left+1; i <= right; i++)
    if (strcmp(v[i], v[left]) < 0)
      swap_(v,  ++last, i);

  swap_(v, left, last);
  qsort_(v, left, last-1);
  qsort_(v, last+1, right);
}

void swap_(char *v[], int i, int j) {
  char *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
