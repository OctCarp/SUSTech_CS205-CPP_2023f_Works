#include <iostream>
#include <algorithm>
#include "sales.hpp"

void SALES::setSales(Sales &s, const double ar[], int n) {
    double max = ar[0], min = ar[0];
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        s.sales[i] = ar[i];
        max = std::max(ar[i], max);
        min = std::min(ar[i], min);
        sum += ar[i];
    }
    s.average = sum / n;
    s.max = max;
    s.min = min;
}

void SALES::showSales(const Sales &s, int n) {
    std::cout << "Sales: ";
    for (int i = 0; i < n; ++i) {
        std::cout << s.sales[0] << " ";
    }
    std::cout << '\n' << "Average: " << s.average << '\n';
    std::cout << "Max: " << s.max << '\n';
    std::cout << "Min: " << s.min << std::endl;
}
