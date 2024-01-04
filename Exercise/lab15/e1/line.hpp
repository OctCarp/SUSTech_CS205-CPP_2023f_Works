#ifndef L15E1_LINE_HPP
#define L15E1_LINE_HPP

#include "point.hpp"

namespace l15e1 {
    class Line {
    private:
        Point p1, p2;
        double distance;
    public:
        Line(Point xp1, Point xp2);

        Line(Line &q);

        double getDistance() const;
    };
}

#endif // L15E1_LINE_HPP
