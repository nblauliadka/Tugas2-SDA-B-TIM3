#ifndef UTILS_H
#define UTILS_H

#define MAX_DATA 1000
#define MAX_WORDS 450000
#define MAX_WORD_LEN 64
#define DISPLAY_COUNT 10
#define DATASET_FILE "words.txt"

void swap_int(int *a, int *b);
void swap_str(char a[], char b[]);

void shuffle_int(int arr[], int n);
void shuffle_str(char arr[][MAX_WORD_LEN], int n);

#endif