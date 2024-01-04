#include <iostream>
#include "point.hpp"
#include "line.hpp"

using namespace l15e1;

inline void show_point(const Point &point, std::string name) {
    std::cout << "test point " << name << ": ";
    std::cout << "x = " << point.getX() << ", y = " << point.getY();
    std::cout << std::endl;
}

inline void show_line(const Line &line, std::string name) {
    std::cout << name << ": " << line.getDistance() << std::endl;
}

int main() {
    Point a(8, 9);
    Point b(1, -1);
    show_point(a, "a");
    show_point(b, "b");

    Line line1(a, b);
    show_line(line1, "line1");

    Line line2(line1);
    show_line(line2, "line2");

    return 0;
}