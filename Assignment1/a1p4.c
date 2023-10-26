#include <stdio.h>
#include <math.h>

#define uint unsigned int
#define MAX_SIZE 35
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

int n;
double as[MAX_SIZE];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lf", &as[i]);
    }

    double res_m = -1.0;

    for (uint i = 1; i < (uint) 1 << n; ++i) {
        double a_sum = 0;
        for (int j = 0; j < n; ++j) {
            if ((i >> j) & 1) {
                a_sum += as[j];
            }
        }

        res_m = fmax(res_m, sin(a_sum * M_PI / 180));
    }

    printf("%.2f\n", res_m);

    return 0;
}
