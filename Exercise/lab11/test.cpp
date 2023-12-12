#include <iostream>
#include "rectangle.hpp"

int main() {
    Rectangle r1;
    r1.display();

    Rectangle r2(4, 35.2);
    r2.display();

    std::cout << "The number of rectangles is: " << Rectangle::getCount() << std::endl;
}