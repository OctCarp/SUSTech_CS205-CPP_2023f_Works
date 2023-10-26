#include <stdio.h>

typedef struct CandyBar {
    char name[20];
    float weight;
    int calories;
} CandyBar;

int main() {
    CandyBar arr[3];

    printf("Please input three CandyBars' information:\n");
    for (int i = 0; i < 3; ++i) {
        printf("Enter brand name of a Candybar: ");
        gets(arr[i].name);
        printf("Enter weight of a Candybar: ");
        scanf("%f", &arr[i].weight);
        getchar();
        printf("Enter calories (an integer value) of a Candybar: ");
        scanf("%d", &arr[i].calories);
        getchar();
    }
    printf("----------------------------------------------\n");
    printf("Display the CandyBar array contents\n");
    for (int i = 0; i < 3; ++i) {
        printf("Brand name: %s\n", arr[i].name);
        printf("Weight: %.1f\n", arr[i].weight);
        printf("Calories: %d\n", arr[i].calories);
    }
    printf("----------------------------------------------\n");
    int id;
    float max_ca = 0;
    for (int i = 0; i < 3; ++i) {
        float cur = arr[i].calories / arr[i].weight;
        if (cur > max_ca) {
            max_ca = cur;
            id = i;
        }
    }

    printf("The greatest calories per weight is:\n");
    printf("Brand name: %s\n", arr[id].name);
    printf("Calories per weight: %f\n", max_ca);
}