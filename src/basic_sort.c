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

/* Memilih nilai terkecil lalu menempatkannya di posisi yang benar */
void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        if (min_idx != i)
            swap_int(&arr[i], &arr[min_idx]);
    }
}

void menu_sorting_dasar(void) {
    int pilih;

    while (1) {
        printf("\n===== SORTING DASAR =====\n");
        printf("1. Bubble Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Selection Sort\n");
        printf("4. Kembali\n");
        printf("Pilih metode : ");

        if (scanf("%d", &pilih) != 1) {
            while (getchar() != '\n');
            printf("Input tidak valid!\n");
            continue;
        }

        if (pilih == 4) break;

        if (pilih < 1 || pilih > 3) {
            printf("Pilihan tidak valid! Masukkan angka 1-4.\n");
            continue;
        }

         /* Membuat 1000 data integer secara acak */
        int data[MAX_DATA];
        srand((unsigned int)time(NULL));

        for (int i = 0; i < MAX_DATA; i++)
            data[i] = rand() % 10000 + 1;

        printf("\nData SEBELUM shuffle & sorting (%d data pertama dari %d):\n",
               DISPLAY_COUNT, MAX_DATA);
        cetak_pemisah();
        tampil_int(data, MAX_DATA);

        /* Mengacak urutan data */
        shuffle_int(data, MAX_DATA);

        printf("\nData SESUDAH shuffle, SEBELUM sorting (%d data pertama):\n",
               DISPLAY_COUNT);
        cetak_pemisah();
        tampil_int(data, MAX_DATA);

        /* Menghitung waktu proses sorting */
        clock_t start, end;
        const char *nama_algo;

        switch (pilih) {
            case 1:
                nama_algo = "Bubble Sort";
                start = clock();
                bubble_sort(data, MAX_DATA);
                end = clock();
                break;

            case 2:
                nama_algo = "Insertion Sort";
                start = clock();
                insertion_sort(data, MAX_DATA);
                end = clock();
                break;

            case 3:
                nama_algo = "Selection Sort";
                start = clock();
                selection_sort(data, MAX_DATA);
                end = clock();
                break;

            default:
                continue;
        }

        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

        /* Menampilkan hasil pengurutan */
        printf("\nData SETELAH sorting — %s (%d data pertama):\n",
               nama_algo, DISPLAY_COUNT);
        cetak_pemisah();
        tampil_int(data, MAX_DATA);
        cetak_pemisah();
        printf("  Algoritma     : %s\n", nama_algo);
        printf("  Jumlah Data   : %d integer\n", MAX_DATA);
        printf("  Waktu Eksekusi: %.6f detik\n", elapsed);
        cetak_pemisah();
    }
}
