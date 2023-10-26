#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

int n;
double rad;

double taylor(int start) {
    double item = start ? rad : 1.0;

    double res = item;
    for (int i = start + 2; i <= n; i += 2) {
        item *= -(rad / (i - 1)) * (rad / i);
        res += item;
    }

    return res;
}

int main() {
    double x;
    char type;
    scanf("%lf%d%s", &x, &n, &type);
    rad = type == 'r' ? x : x * M_PI / 180;

    printf("%.2f\n%.2f\n", taylor(1), taylor(0));

    return 0;
}
