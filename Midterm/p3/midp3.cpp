#include <iostream>

using namespace std;

void multiply(int sa, int sb) {
    printf("%d ", sa * sb);
}

void multiply(int s, int *v, int sz) {
    for (int i = 0; i < sz; ++i) {
        printf("%d ", s * v[i]);
    }
}

void multiply(int *v1, int *v2, int sz) {
    int res = 0;
    for (int i = 0; i < sz; ++i) {
        res += v1[i] * v2[i];
    }
    printf("%d ", res);
}


int main() {
    char typeA, typeB;
    int scalarA, scalarB, sizeA, sizeB;
    int *vectorA = nullptr, *vectorB = nullptr;


    std::cin >> typeA;
    if (typeA == 'S') {
        std::cin >> scalarA;
    } else if (typeA == 'V') {
        std::cin >> sizeA;
        vectorA = new int[sizeA];
        for (int i = 0; i < sizeA; ++i) {
            std::cin >> vectorA[i];
        }
    }

    std::cin >> typeB;
    if (typeB == 'S') {
        std::cin >> scalarB;
    } else if (typeB == 'V') {
        std::cin >> sizeB;
        vectorB = new int[sizeB];
        for (int i = 0; i < sizeB; ++i) {
            std::cin >> vectorB[i];
        }
    }

    // Perform multiplication based on types of A and B
    if (typeA == 'S' && typeB == 'S') {
        multiply(scalarA, scalarB);
    } else if (typeA == 'S' && typeB == 'V') {
        multiply(scalarA, vectorB, sizeB);
    } else if (typeA == 'V' && typeB == 'S') {
        multiply(scalarB, vectorA, sizeA);
    } else if (typeA == 'V' && typeB == 'V' && sizeA == sizeB) {
        multiply(vectorA, vectorB, sizeA);
    } else {
        std::cout << "Invalid input or mismatched dimensions" << std::endl;
    }

    // Clean up dynamically allocated memory
    delete[] vectorA;
    delete[] vectorB;

    return 0;
}
