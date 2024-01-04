#include <cmath>
#include <iostream>

#include "line.hpp"

namespace l15e1 {
    Line::Line(Point xp1, Point xp2) : p1(xp1), p2(xp2) {
        double dx = p1.getX() - p2.getX();
        double dy = p1.getY() - p2.getY();
        distance = std::sqrt(dx * dx + dy * dy);
    }

    Line::Line(Line &q) : p1(q.p1), p2(q.p2), distance(q.distance) {
        std::cout << "calling the copy constructor of Line" << std::endl;
    }

    double Line::getDistance() const {
        return distance;
    }
}