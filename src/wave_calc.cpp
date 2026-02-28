#include "wave_calc.h"
#include <cmath>

double L0_calculation(double T) {
    const double val = 1.56;
    double L0 = val * std::pow(T, 2);
    return L0;
}

double C0_calculation(double L0, double T) {
    return L0 * T; 
}

double d_per_L0_calculation(double d, double L0) {
    return d / L0;
}
