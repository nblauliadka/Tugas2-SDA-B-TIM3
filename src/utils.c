#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

/* Tukar dua nilai integer */
void swap_int(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

/* Tukar dua string (array of char) */
void swap_str(char a[], char b[]) {
  char tmp[MAX_WORD_LEN];
  strcpy(tmp, a);
  strcpy(a, b);
  strcpy(b, tmp);
}