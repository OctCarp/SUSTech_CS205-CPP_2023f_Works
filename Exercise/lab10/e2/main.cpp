#include <iostream>
#include "sales.hpp"

int main() {
    int n;
    double ar[SALES::QUATERS];
    std::cout << "Input n: ";
    std::cin >> n;
    if (n > SALES::QUATERS) {
        std::cout << "n is not correct.\nAborted" << std::endl;
    } else {
        std::cout << "Please input " << n << " double values: ";
        for (int i = 0; i < n; ++i) {
            std::cin >> ar[i];
        }

        
        SALES::Sales s;
        SALES::setSales(s, ar, n);
        SALES::showSales(s, n);
    }

    return 0;
}