#pragma once

namespace SALES {
    const int QUATERS = 4;
    struct Sales {
        double sales[QUATERS];
        double average;
        double max;
        double min;
    };

    //copies n items from the array ar to the sales member of s and
    //computes and stores the average, maximum and minimum values
    //of the entered items .
    void setSales(Sales &s, const double ar[], int n = 4);

    // display all information in the sales s
    void showSales(const Sales &s, int n = 4);
}