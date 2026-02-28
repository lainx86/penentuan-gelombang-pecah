#include <print> // Catatan: Pastikan Anda menggunakan kompilator C++23
#include <cmath>
#include <iostream>
#include "logic.h"
#include "wave_calc.h"



int main() {
    // Contoh parameter input
    Parameter p;
    p.H0 = 3.25;
    p.T = 8.0;
    p.m = 0.03;
    p.alpha_0 = 45.0;
    
    double kedalaman_d = 3.25; // Contoh kedalaman
    
    // 1. Hitung L0
    double L0 = L0_calculation(p.T);
    
    // 2. Hitung d/L0
    double d_L0 = d_per_L0_calculation(kedalaman_d, L0);
    
    std::println("Parameter Input:");
    std::println("T = {} s, d = {} m", p.T, kedalaman_d);
    std::println("L0 = {} m", L0);
    std::println("d/L0 = {}", d_L0);
    
    // 3. Muat Data Tabel Excel (dari embedded data)
    // Walaupun string kosong diteruskan, loadAndCleanData akan menggunakan data embedded.
    auto dt = logic::loadAndCleanData("");
    
    // 4. Cari batas d/L0 untuk d/L0 yang baru dihitung
    auto batas = logic::cariBatasData(dt, "d/L0", d_L0);
    
    if (batas.found) {
        // Ambil nilai x1, x2 (d/L0 batas) dan y1, y2 (d/L batas)
        auto x1Opt = logic::getValueFromRow(batas.bawah, "d/L0");
        auto x2Opt = logic::getValueFromRow(batas.atas, "d/L0");
        auto y1Opt = logic::getValueFromRow(batas.bawah, "d/L");
        auto y2Opt = logic::getValueFromRow(batas.atas, "d/L");
        
        if (x1Opt && x2Opt && y1Opt && y2Opt) {
            double x1 = x1Opt.value();
            double x2 = x2Opt.value();
            double y1 = y1Opt.value();
            double y2 = y2Opt.value();
            
            std::println("\nBatas Ditemukan pada Tabel:");
            std::println("Bawah : d/L0 = {}, d/L = {}", x1, y1);
            std::println("Atas  : d/L0 = {}, d/L = {}", x2, y2);
            
            // 5. Lakukan Interpolasi untuk mencari d/L
            auto interpResult = logic::hitungInterpolasi(x1, x2, y1, y2, d_L0);
            
            if (interpResult.success) {
                std::println("\n{}Hasil Interpolasi:{}", "\033[1;32m", "\033[0m");  // Hijau
                double d_L = interpResult.value;
                std::println("Nilai d/L = {}", d_L);
                
                // --- Perhitungan Lanjutan ---
                
                // - nilai L = d / (d/L)
                double L = kedalaman_d / d_L;
                std::println("L = {} m", L);
                
                // - nilai C = L / T
                double C = L / p.T;
                std::println("C = {} m/s", C);
                
                // Nilai C0
                double C0 = C0_calculation(L0, p.T);
                std::println("C0 = {} m/s", C0);
                
                // - nilai sin alpha = C / C0
                // Hati-hati: asumsikan sin(alpha_0) dikalikan dengan (C/C0) menurut Hukum Snellius? 
                // Di permintaan tertulis "sin alpha = C/C0", tapi biasanya sin(alpha)/C = sin(alpha_0)/C0
                // Mari asumsikan maksud user adalah sin(alpha) = sin(alpha_0) * (C/C0).
                // Kita akan pakai asumsi Hukum Snellius ini.
                
                const double PI = 3.14159265358979323846;
                double alpha_0_rad = p.alpha_0 * PI / 180.0;
                double sin_alpha = std::sin(alpha_0_rad) * (C / C0);
                std::println("sin alpha = {}", sin_alpha);
                
                // - nilai alpha = arc sin (sin alpha)
                double alpha_rad = std::asin(sin_alpha);
                double alpha_deg = alpha_rad * 180.0 / PI;
                std::println("alpha = {} derajat", alpha_deg);
                
                // - nilai Kr = sqrt((cos alpha_0 derajat)/(cos alpha derajat))
                double cos_alpha_0 = std::cos(alpha_0_rad);
                double cos_alpha = std::cos(alpha_rad);
                double Kr = std::sqrt(cos_alpha_0 / cos_alpha);
                std::println("Kr = {}", Kr);
                
                // - nilai H_aksen_0 = H0 * Kr
                double H_aksen_0 = p.H0 * Kr;
                std::println("H'_0 = {} m", H_aksen_0);
                
                // - nilai H_aksen_0 / (g * T^2)
                double g = 9.81;
                double rasio_H0_aksen = H_aksen_0 / (g * std::pow(p.T, 2));
                std::println("H'_0 / (g * T^2) = {}", rasio_H0_aksen);
                
                // --- Interpolasi Grafik 7.17 ---
                std::println("\n--- Interpolasi Grafik 7.17 ---");
                std::println("Berdasarkan nilai H'_0/(g*T^2) = {}, silakan masukkan parameter pembacaan dari grafik:", rasio_H0_aksen);
                
                double x1_grafik, x2_grafik, y1_grafik, y2_grafik;
                std::cout << "Masukkan H'_0/(g*T^2) batas bawah (x1): ";
                std::cin >> x1_grafik;
                std::cout << "Masukkan H'_0/(g*T^2) batas atas (x2) : ";
                std::cin >> x2_grafik;
                std::cout << "Masukkan nilai sumbu Y batas bawah (y1) : ";
                std::cin >> y1_grafik;
                std::cout << "Masukkan nilai sumbu Y batas atas (y2)  : ";
                std::cin >> y2_grafik;
                
                auto interpGrafik = logic::hitungInterpolasi(x1_grafik, x2_grafik, y1_grafik, y2_grafik, rasio_H0_aksen);
                
                if (interpGrafik.success) {
                    std::println("\n{}Hasil Interpolasi Grafik 7.17:{}", "\033[1;33m", "\033[0m");  // Kuning
                    std::println("Nilai Y (hasil grafik) = {}", interpGrafik.value);
                } else {
                    std::println("Error Interpolasi Grafik 7.17: {}", interpGrafik.error);
                }
                
            } else {
                std::println("Error Interpolasi: {}", interpResult.error);
            }
        } else {
            std::println("Error: Gagal mengekstrak kolom 'd/L0' atau 'd/L' dari tabel.");
        }
    } else {
        std::println("Error: Batas data untuk d/L0 = {} tidak ditemukan.", d_L0);
    }
    
    return 0;
}