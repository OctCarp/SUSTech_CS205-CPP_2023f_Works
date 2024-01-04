#include "point.hpp"

namespace l15e1 {

    Point::Point(double newX, double newY) : x(newX), y(newY) {}

    double Point::getX() const {
        return x;
    }

    double Point::getY() const {
        return y;
    }
}