#include <cmath>
#include <iostream>

#include "shape.hpp"

int CStereoShape::numberOfObject = 0;

CStereoShape::CStereoShape() {
    ++numberOfObject;
}

double CStereoShape::GetArea() const {
    std::cout << "CStereoShape::GetArea()" << std::endl;
    return 0.0;
}

double CStereoShape::GetVolume() const {
    std::cout << "CStereoShape::GetVolume()" << std::endl;
    return 0.0;
}

void CStereoShape::Show() const {
    std::cout << "CStereoShape::Show()" << std::endl;
}

int CStereoShape::GetNumOfObject() {
    return numberOfObject;
}

CCube::CCube() : CStereoShape(), length(0.0), width(0.0), height(0.0) {}

CCube::CCube(double l, double w, double h) : CStereoShape(), length(l), width(w), height(h) {}

CCube::CCube(const CCube &cube) : CStereoShape(), length(cube.length), width(cube.width), height(cube.height) {}

double CCube::GetArea() const {
    return 2 * (length * width + length * height + width * height);
}

double CCube::GetVolume() const {
    return length * width * height;
}

void CCube::Show() const {
    std::cout << "Cube length: " << length << "  width: " << width << \
    "  height: " << height << std::endl;
    std::cout << "Cube area: " << GetArea() << "  volume: " << GetVolume() << std::endl;
}

CSphere::CSphere() : CStereoShape(), radius(0.0) {}

CSphere::CSphere(double r) : CStereoShape(), radius(r) {}

CSphere::CSphere(const CSphere &sphere) : CStereoShape(), radius(sphere.radius) {}

double CSphere::GetArea() const {
    return 4 * M_PI * pow(radius, 2);
}

double CSphere::GetVolume() const {
    return (4.0 / 3.0) * M_PI * pow(radius, 3);
}

void CSphere::Show() const {
    std::cout << "Sphere radius: " << radius << \
    "  area: " << GetArea() << "  volume: " << GetVolume() << std::endl;
}
