## Multiply Anything

### Description

In deep learning, operations involving tensors constitute a significant portion of computational expenses. Handling these operations requires flexibility, especially when dealing with variables of different dimensions.

Please write a program that utilizes function overloading to implement multiplication operations between scalars and vectors.

### Input

- A character representing the dimension of variable $A$, followed by the variable  $A$ itself.
- A character representing the dimension of variable $B$, followed by the variable $B$.
- Note: If $A$ or $B$ is a vector, an additional integer input is required to specify its length.

**Note**

- For dimensions, $S$ represents a scalar and $V$ represents a vector.
- When performing vector multiplication, only the dot product should be considered.
- Considering integer is enough.

### Output

- The result of the multiplication operation $A⋅B$.
- Note: print '`Invalid input or mismatched dimensions`' for any invalid operations.
- Format: Output the components of the vector in order, separated by a single space

### Sample Input 1 

```
S 7 S 9
```

### Sample Output 1

```
63
```

### Hint

#### The C++ code template

```CPP
#include <iostream>

// Function for scalar multiplication


// Function for scalar and vector multiplication


// Function for dot product of two vectors



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
```

#### The C code template

```C
#include <stdio.h>
#include <stdlib.h>

// Function for scalar multiplication


// Function for scalar and vector multiplication


// Function for dot product of two vectors


int main() {
    char typeA, typeB;
    int scalarA, scalarB, sizeA, sizeB, i;
    int *vectorA = NULL, *vectorB = NULL;

    scanf(" %c", &typeA);
    if (typeA == 'S') {
        scanf("%d", &scalarA);
    } else if (typeA == 'V') {
        scanf("%d", &sizeA);
        vectorA = (int*)malloc(sizeA * sizeof(int));
        for (i = 0; i < sizeA; ++i) {
            scanf("%d", &vectorA[i]);
        }
    }

    scanf(" %c", &typeB);
    if (typeB == 'S') {
        scanf("%d", &scalarB);
    } else if (typeB == 'V') {
        scanf("%d", &sizeB);
        vectorB = (int*)malloc(sizeB * sizeof(int));
        for (i = 0; i < sizeB; ++i) {
            scanf("%d", &vectorB[i]);
        }
    }

    // Perform multiplication based on types of A and B
    if (typeA == 'S' && typeB == 'S') {
        multiplyScalar(scalarA, scalarB);
    } else if (typeA == 'S' && typeB == 'V') {
        multiplyScalarVector(scalarA, vectorB, sizeB);
    } else if (typeA == 'V' && typeB == 'S') {
        multiplyScalarVector(scalarB, vectorA, sizeA);
    } else if (typeA == 'V' && typeB == 'V' && sizeA == sizeB) {
        multiplyVectorVector(vectorA, vectorB, sizeA);
    } else {
        printf("Invalid input or mismatched dimensions\n");
    }

    // Clean up dynamically allocated memory
    free(vectorA);
    free(vectorB);

    return 0;
}
```