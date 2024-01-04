#ifndef LAB14_SHAPE_HPP
#define LAB14_SHAPE_HPP

class CStereoShape {
protected:
    static int numberOfObject;

public:
    CStereoShape();

    virtual double GetArea() const;

    virtual double GetVolume() const;

    virtual void Show() const;

    static int GetNumOfObject();
};

class CCube : public CStereoShape {
private:
    double length;
    double width;
    double height;

public:
    CCube();

    CCube(double length, double width, double height);

    CCube(const CCube &cube);

    double GetArea() const override;

    double GetVolume() const override;

    void Show() const override;
};

class CSphere : public CStereoShape {
private:
    double radius;

public:
    CSphere();

    CSphere(double radius);

    CSphere(const CSphere &sphere);

    double GetArea() const override;

    double GetVolume() const override;

    void Show() const override;
};

#endif //LAB14_SHAPE_HPP
