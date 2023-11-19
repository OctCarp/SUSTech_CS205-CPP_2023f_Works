#include <stdio.h>
#include "swap.h"

int main() {
    int a, b;
    printf("Please input two integers: ");
    scanf("%d%d", &a, &b);

    printf("Before swap: %d, %d\n", a, b);
    swap(&a, &b);
    printf("After swap: %d, %d\n", a, b);

    return 0;
}
