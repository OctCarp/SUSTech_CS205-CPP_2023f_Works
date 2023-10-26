#include <stdio.h>

int main() {
    char a;
    int b;
    double c;
    printf("Please input a character:\n");
    scanf("%s", &a);
    printf("Please input a integer:\n");
    scanf("%d", &b);
    printf("Please input a float:\n");
    scanf("%lf", &c);
    printf("The varaibles you entered were:\n");
    printf("The character is: %c\nThe integer is: %d\nThe float is %.6f\n", a, b, c);

    return 0;
}