#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils.h"
#include "advance_sorting.h"

// Buffer statis supaya malloc tidak berulang 
static char _merge_L[MAX_WORDS / 2 + 2][MAX_WORD_LEN];
static char _merge_R[MAX_WORDS / 2 + 2][MAX_WORD_LEN];

// Fungsi merge internal: mengabungkan arr[left..mid] dan arr[mid+1..right]
static void merge(char arr[][MAX_WORD_LEN], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Salin ke buffer sementara
    for (int i = 0; i < n1; i++) strcpy(_merge_L[i], arr[left + i]);
    for (int j = 0; j < n2; j++) strcpy(_merge_R[j], arr[mid + 1 + j]);

    // Gabungkan kembali ke arr[] dengan terurut
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

void merge_sort(char arr[][MAX_WORD_LEN], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; 
        // recursive
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// untuk memilih pivot dengan mengambil nilai yang ditengah
static void median_of_three(char arr[][MAX_WORD_LEN], int low, int high) {
    int mid = low + (high - low) / 2;

    if (strcmp(arr[low],  arr[mid])  > 0) swap_str(arr[low],  arr[mid]);
    if (strcmp(arr[low],  arr[high]) > 0) swap_str(arr[low],  arr[high]);
    if (strcmp(arr[mid],  arr[high]) > 0) swap_str(arr[mid],  arr[high]);

    swap_str(arr[mid], arr[high]);
}

// return indexs terakhir pivot
static int partition(char arr[][MAX_WORD_LEN], int low, int high) {
    median_of_three(arr, low, high);

    char pivot[MAX_WORD_LEN];
    strcpy(pivot, arr[high]);

    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (strcmp(arr[j], pivot) <= 0) {
            i++;
            swap_str(arr[i], arr[j]);
        }
    }
    swap_str(arr[i + 1], arr[high]);
    return i + 1;
}

void quick_sort(char arr[][MAX_WORD_LEN], int low, int high) {
    while (low < high) {
        int pi = partition(arr, low, high);

        /* Rekursi pada partisi yang lebih kecil */
        if (pi - low < high - pi) {
            quick_sort(arr, low, pi - 1);
            // partisi kanan
            low = pi + 1;
        } else {
            quick_sort(arr, pi + 1, high);
            // partisi kiri
            high = pi - 1;
        }
    }
}

void shell_sort(char arr[][MAX_WORD_LEN], int n) {
    // Hitung gap awal terbesar dalam urutan 
    int gap = 1;
    while (gap < n / 3)
        gap = 3 * gap + 1;

    // Insertion sort supaya gap nya makin sedikit
    while (gap >= 1) {
        for (int i = gap; i < n; i++) {
            char temp[MAX_WORD_LEN];
            strcpy(temp, arr[i]);

            int j = i;
            while (j >= gap && strcmp(arr[j - gap], temp) > 0) {
                strcpy(arr[j], arr[j - gap]);
                j -= gap;
            }
            strcpy(arr[j], temp);
        }
        gap /= 3;
    }
}