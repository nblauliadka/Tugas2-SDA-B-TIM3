#include "advance_sort.h"
#include "basic_sort.h"
#include <stdio.h>

static void tampil_header(void) {
  printf("============================================================\n");
  printf("  Tugas 2 Praktikum Struktur Data dan Algoritma B\n");
  printf("  Implementasi dan Analisis Algoritma Sorting - Bahasa C\n");
  printf("============================================================\n");
}

int main(void) {
  tampil_header();

  int pilih;
  while (1) {
    printf("\n===== MENU UTAMA =====\n");
    printf("1. Sorting Dasar\n");
    printf("2. Advance Sorting\n");
    printf("3. Keluar\n");
    printf("Pilih menu : ");

    if (scanf("%d", &pilih) != 1) {
      while (getchar() != '\n')
        ;
      printf("  Input tidak valid! Masukkan angka 1-3.\n");
      continue;
    }

    switch (pilih) {
    case 1:
      menu_sorting_dasar();
      break;
    case 2:
      menu_advance_sorting();
      break;
    case 3:
      printf("\nTerima kasih! Program selesai.\n");
      return 0;
    default:
      printf("  Pilihan tidak valid! Masukkan angka 1-3.\n");
    }
  }
}