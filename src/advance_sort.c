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

// untuk menyimpan kata yang asli dan yang untuk di shuffle
static char g_words[MAX_WORDS][MAX_WORD_LEN];
static char g_work [MAX_WORDS][MAX_WORD_LEN];   
static int  g_word_count = 0;                   

void menu_advance_sorting(void) {
    // muat dataset
    if (g_word_count == 0) {
        printf("\n  Memuat dataset kata dari '%s' ...\n", DATASET_FILE);
        g_word_count = load_words(DATASET_FILE, g_words, MAX_WORDS);
        if (g_word_count == 0) return;  
        printf("  Berhasil memuat %d kata.\n", g_word_count);
    }

    int pilih;
    while (1) {
        printf("\n===== ADVANCE SORTING =====\n");
        printf("1. Merge Sort\n");
        printf("2. Quick Sort\n");
        printf("3. Shell Sort\n");
        printf("4. Kembali\n");
        printf("Pilih metode : ");

        if (scanf("%d", &pilih) != 1) {
            while (getchar() != '\n');
            printf("  Input tidak valid!\n");
            continue;
        }

        if (pilih == 4) break;
        if (pilih < 1 || pilih > 3) {
            printf("  Pilihan tidak valid! Masukkan angka 1-4.\n");
            continue;
        }

        // Salin data asli ke buffer kerja (untuk di shuffle)
        for (int i = 0; i < g_word_count; i++)
            strcpy(g_work[i], g_words[i]);

        printf("\nData SEBELUM shuffle & sorting (%d kata pertama dari %d):\n", DISPLAY_COUNT, g_word_count);
        cetak_pemisah();
        tampil_str(g_work, g_word_count);

        // shuffle dimulai
        srand((unsigned int)time(NULL));
        shuffle_str(g_work, g_word_count);

        printf("\nData SESUDAH shuffle, SEBELUM sorting (%d kata pertama):\n", DISPLAY_COUNT);
        cetak_pemisah();
        tampil_str(g_work, g_word_count);

        // mengukur waktu (start)
        clock_t     start, end;
        const char *nama_algo;

        switch (pilih) {
            case 1:
                nama_algo = "Merge Sort";
                start = clock();
                merge_sort(g_work, 0, g_word_count - 1);
                end = clock();
                break;
            case 2:
                nama_algo = "Quick Sort";
                start = clock();
                quick_sort(g_work, 0, g_word_count - 1);
                end = clock();
                break;
            case 3:
                nama_algo = "Shell Sort";
                start = clock();
                shell_sort(g_work, g_word_count);
                end = clock();
                break;
            default:
                continue;
        }

        // mengukur waktu (end)
        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

        printf("\nData SETELAH sorting — %s (%d kata pertama):\n", nama_algo, DISPLAY_COUNT);
        cetak_pemisah();
        tampil_str(g_work, g_word_count);
        cetak_pemisah();
        printf("  Algoritma     : %s\n", nama_algo);
        printf("  Jumlah Data   : %d kata\n", g_word_count);
        printf("  Waktu Eksekusi: %.6f detik\n", elapsed);
        cetak_pemisah();
    }
}
