#include "functions.hpp"

template<typename T>
T division(T a, T b) {
    if (b == 0) {
        throw "ERROR: division by zero";
    }
    return a / b;
}

template int division<int>(int a, int b);