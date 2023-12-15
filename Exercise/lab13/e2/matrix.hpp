#ifndef LAB13_MATRIX_HPP
#define LAB13_MATRIX_HPP

#include <iostream>
#include <memory>

class Matrix {
private:
    size_t rows;
    size_t cols;
    size_t *refCount;
    float *data;

public:
    Matrix(size_t rows, size_t cols);

    Matrix(const Matrix &rhs);

    Matrix &operator=(const Matrix &rhs);

    float &operator()(size_t row, size_t col) const;

    const Matrix operator+(const Matrix &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);
};

#endif
