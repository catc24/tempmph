#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double k_b = 1.38064852e-23; // Boltzmann constant in J/K
double m = 1.66053906660e-27; // mass of hydrogen atom in kg
double mph_per_mps = 2.236936; // conversion factor from meters per second to miles per hour

double velocity(double temp) {
    double v_rms = sqrt(3 * k_b * temp / m);
    return v_rms * mph_per_mps;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <temperature>\n", argv[0]);
        return 1;
    }

    double temp = atof(argv[1]);
    double vel = velocity(temp);
    printf("%.2f\n", vel);

    return 0;
}
