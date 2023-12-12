#include <iostream>
#include <iomanip>
#include "rectangle.hpp"

using std::cout;
using std::setw;
using std::left;
using std::right;
using std::endl;

int Rectangle::countOfObject = 0;

Rectangle::Rectangle() {
    width = 1;
    height = 1;
    ++countOfObject;
}

Rectangle::Rectangle(double w, double h) : width(w), height(h) {
    ++countOfObject;
}

double Rectangle::getWidth()const {
    return width;
}

double Rectangle::getHeight()const {
    return height;
}

void Rectangle::setWidth(double w) {
    width = w;
}

void Rectangle::setHeight(double h) {
    height = h;
}

double Rectangle::getArea() const {
    return width * height;
}

double Rectangle::getPerimeter()const {
    return (width + height) * 2;
}

void Rectangle::display() const {
    cout << setw(5) << "" << "Rectangle " << getCount() << endl;
    cout << "--------------------" << endl;
    cout << setw(10) << left << "Width:" << setw(5) << right << getWidth() << endl;
    cout << setw(10) << left << "Height:" << setw(5) << right << getHeight() << endl;
    cout << setw(10) << left << "Perimeter:" << setw(5) << right << getPerimeter() << endl;
    cout << setw(10) << left << "Area:" << setw(5) << right << getArea() << endl;

}

int Rectangle::getCount() {
    return countOfObject;
}