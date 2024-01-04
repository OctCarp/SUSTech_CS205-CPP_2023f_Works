#include "shape.hpp"

#include <iostream>

int main() {
    CCube a_cube(4.0, 5.0, 6.0);
    CSphere c_sphere(7.9);

    CStereoShape *p = &a_cube;
    p->Show();

    p = &c_sphere;
    p->Show();

    int n = CStereoShape::GetNumOfObject();
    std::cout << n << (n < 2 ? " object is" : " objects are") << " created." << std::endl;

    return 0;
}
