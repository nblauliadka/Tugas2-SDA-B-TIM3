#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils.h"
#include "advance_sorting.h"

// Buffer statis supaya malloc tidak berulang 
static char _merge_L[MAX_WORDS / 2 + 2][MAX_WORD_LEN];
static char _merge_R[MAX_WORDS / 2 + 2][MAX_WORD_LEN];

/* Fungsi merge internal: gabungkan arr[left..mid] dan arr[mid+1..right] */
static void merge(char arr[][MAX_WORD_LEN], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    /* Salin ke buffer sementara */
    for (int i = 0; i < n1; i++) strcpy(_merge_L[i], arr[left + i]);
    for (int j = 0; j < n2; j++) strcpy(_merge_R[j], arr[mid + 1 + j]);

    /* Gabungkan kembali ke arr[] secara terurut */
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (strcmp(_merge_L[i], _merge_R[j]) <= 0)
            strcpy(arr[k++], _merge_L[i++]);
        else
            strcpy(arr[k++], _merge_R[j++]);
    }
    while (i < n1) strcpy(arr[k++], _merge_L[i++]);
    while (j < n2) strcpy(arr[k++], _merge_R[j++]);
}