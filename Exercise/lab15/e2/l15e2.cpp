#include <iostream>

#include "pair.hpp"

int main() {
    Pair<std::string, int> one("Tom", 19);
    Pair<std::string, int> two("Alice", 20);

    if (one < two)
        std::cout << one;
    else
        std::cout << two;

    return 0;
}