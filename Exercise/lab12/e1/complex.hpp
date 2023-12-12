#include <iostream>

#ifndef COMPLEX_HPP
#define COMPLEX_HPP

class Complex {
private:
    double real;
    double imag;
public:
    Complex() : real(1), imag(1) {
//        std::cout << "Default constructor is invoked.\n";
    }

    Complex(double re, double im) : real(re), imag(im) {
//        std::cout << "Parameter constructor is invoked.\n";
    }

    Complex(const Complex &);

    Complex operator+(const Complex &rhs) const;

    Complex operator+(double n) const;

    friend Complex operator+(double n, const Complex &rhs);

    Complex operator-() const;

    Complex operator-(const Complex &rhs) const;

    Complex operator-(double n) const;

    friend Complex operator-(double lhs, const Complex &rhs);

    Complex operator*(const Complex &rhs) const;

    Complex operator*(double n) const;

    friend Complex operator*(double n, const Complex &rhs);

    Complex operator~() const;

    bool operator==(const Complex &rhs) const;

    bool operator!=(const Complex &rhs) const;

    ~Complex() {
//        std::cout << "Destructor is invoked.\n";
    }

    void Show() const;

    friend std::ostream &operator<<(std::ostream &os, const Complex &c);

    friend std::istream &operator>>(std::istream &is, Complex &c);
};

#endif