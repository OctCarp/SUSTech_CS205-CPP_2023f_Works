#include <iostream>
#include "functions.hpp"

using namespace std;

int main() {
    int a, b;

    cout << "Please input two integers: ";
    cin >> a >> b;

    cout << "Addtion result is " << addition(a, b) << endl;
    cout << "Subtraction result is " << subtraction(a, b) << endl;
    cout << "Multiplication result is " << multiplication(a, b) << endl;
    cout << "Division result is " << division(a, b) << endl;

    return 0;
}

