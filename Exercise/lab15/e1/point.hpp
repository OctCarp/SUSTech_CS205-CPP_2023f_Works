#ifndef L15E1_POINT_HPP
#define L15E1_POINT_HPP

namespace l15e1 {
    class Point {
    private:
        double x, y;
    public:
        Point(double newX, double newY);

        double getX() const;

        double getY() const;
    };
}

#endif // L15E1_POINT_HPP
