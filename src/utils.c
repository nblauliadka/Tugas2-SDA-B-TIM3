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

/* Shuffle array integer */
void shuffle_int(int arr[], int n) {
  for (int i = n - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    swap_int(&arr[i], &arr[j]);
  }
}

/* Shuffle array string */
void shuffle_str(char arr[][MAX_WORD_LEN], int n) {
  for (int i = n - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    swap_str(arr[i], arr[j]);
  }
}