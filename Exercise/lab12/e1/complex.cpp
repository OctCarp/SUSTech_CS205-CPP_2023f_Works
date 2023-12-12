#include <iostream>
#include "complex.hpp"

Complex::Complex(const Complex &c) {
    real = c.real;
    imag = c.imag;
//    std::cout << "Copy constructor called.\n";
}

Complex Complex::operator+(const Complex &rhs) const {
    return Complex(this->real + rhs.real, this->imag + rhs.imag);
}

Complex Complex::operator+(double n) const {
    return Complex(this->real + n, this->imag);
}

Complex operator+(double n, const Complex &rhs) {
    return rhs + n;
}

Complex Complex::operator-(const Complex &rhs) const {
    return Complex(this->real - rhs.real, this->imag - rhs.imag);
}

Complex Complex::operator-(double n) const {
    return Complex(this->real - n, this->imag);
}

Complex operator-(double n, const Complex &rhs) {
    return -rhs + n;
}

Complex Complex::operator*(const Complex &rhs) const {
    return Complex(this->real * rhs.real - this->imag * rhs.imag, 
    this->real * rhs.imag + this->imag * rhs.real);
}


Complex Complex::operator*(double n) const {
    return Complex(this->real * n, this->imag * n);
}

Complex operator*(double n, const Complex &rhs) {
    return rhs * n;
}

Complex Complex::operator~() const {
    return Complex(real, -imag);
}

bool Complex::operator==(const Complex &rhs) const {
    return real == rhs.real && imag == rhs.imag;
}

bool Complex::operator!=(const Complex &rhs) const {
    return !(*this == rhs);
}

void Complex::Show() const {
    std::cout << real << (imag >= 0 ? "+" : "") \
 << imag << "i" << std::endl;
}

Complex Complex::operator-() const {
    return Complex(-real, -imag);
}

std::ostream &operator<<(std::ostream &os, const Complex &c) {
    os << c.real << (c.imag >= 0 ? "+" : "") << c.imag << "i";
    return os;
}

std::istream &operator>>(std::istream &is, Complex &c) {
    is >> c.real >> c.imag;
    return is;
}