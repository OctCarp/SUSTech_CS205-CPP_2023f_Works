#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

int main() {
    double ori;
    char type;
    scanf("%lf%s", &ori, &type);
    printf("%.2f\n", type == 'd' ? ori * M_PI / 180 : ori * 180 / M_PI);

    return 0;
}
