#pragma once

struct Parameter {
    double H0;
    double T;
    double m;
    double alpha_0;
};

// Optimalisasi: Menggunakan pass-by-value (double T) untuk memicu cache/register CPU
double L0_calculation(double T);

double C0_calculation(double L0, double T);

// Perbaikan: Menghilangkan 'H' yang tidak terdefinisi dan menyederhanakan parameter
double d_per_L0_calculation(double d, double L0);
