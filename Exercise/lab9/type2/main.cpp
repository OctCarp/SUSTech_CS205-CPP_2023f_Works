#include <iostream>
#include "functions.hpp"

using namespace std;

int main() {
    int a, b;

    cout << "Please input two integers: ";
    cin >> a >> b;

    cout << "Addition result is " << addition(a, b) << endl;
    cout << "Subtraction result is " << subtraction(a, b) << endl;

    return 0;
}

