#include "matrix.hpp"

using namespace std;

int main() {
    Matrix a(3, 4);
    Matrix b(3, 4);
    a(1, 2) = 3;
    b(2, 3) = 4;
    Matrix c = a + b;

    cout << "a is:\n" << a;
    cout << "b is:\n" << b;
    cout << "c is:\n" << c;

    Matrix d = a;
    cout << "Before assignment, d is:\n" << d;
    d = b;
    cout << "After assignment, d is:\n" << d;

    return 0;
}
