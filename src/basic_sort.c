#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "basic_sorting.h"

/* Mengurutkan data dengan membandingkan elemen yang bersebelahan */
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap_int(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }

        if (!swapped) break;
    }
}

/* Menyisipkan setiap elemen ke posisi yang sesuai */
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}
