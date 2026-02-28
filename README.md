# Penentuan Gelombang Pecah

Proyek C++ ini digunakan untuk menghitung parameter dan karakteristik gelombang pecah di pantai, mengintegrasikan alat pencarian rentang data (dari `InterpKit`) dengan rumus perhitungan hidrodinamika gelombang laut.

## Struktur Direktori

Proyek ini menggunakan struktur standar C++ agar lebih profesional dan modular:

```
.
├── CMakeLists.txt        # Skrip konfigurasi build
├── README.md             # Dokumentasi proyek
├── include/              # Direktori header file publik (misal: wave_calc.h)
├── src/                  # Direktori source file (main.cpp, wave_calc.cpp)
└── third_party/          # Dependensi eksternal
    └── InterpKit/        # Modul manipulasi batas tabel & interpolasi (OpenXLSX)
```

## Persyaratan (Prerequisites)

- **CMake**: Versi 3.14 atau di atasnya.
- **Kompilator C++**: Harus mendukung C++23 (contoh: GCC 13+, Clang 16+). Diperlukan untuk `std::print` dll.

## Cara Menggunakan (Build & Run)

1. **Konfigurasi Proyek (Hanya Saat Pertama Kali / Ada File Baru):**
   ```bash
   cmake -B build
   ```

2. **Kompilasi (Setiap Ada Perubahan Kode):**
   ```bash
   cmake --build build
   ```

3. **Menjalankan Program:**
   ```bash
   ./build/gelombang_pecah
   ```

Program akan memuat tabel data secara otomatis dari internal memori (hasil _embed_ resource dari `third_party/InterpKit/data_tabel.xlsx`), melakukan kalkulasi panjang gelombang acuan (L0), rasio kedalaman (d/L0), mencari batasnya, dan menginterpolasikan parameter lanjutan (L, C, d/L, alpha, dst).
