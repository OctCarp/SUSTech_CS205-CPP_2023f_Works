#include "matrix.hpp"

#include <array>

Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols), refCount(new size_t(1)),
                                           data(new float[cols * rows]) {}

Matrix::Matrix(const Matrix &rhs) : rows(rhs.rows), cols(rhs.cols), refCount(rhs.refCount),
                                    data(rhs.data) { ++*refCount; }

Matrix &Matrix::operator=(const Matrix &rhs) {
    ++*rhs.refCount;
    if (--*refCount == 0) {
        delete refCount;
        delete[] data;
    }

    rows = rhs.rows;
    cols = rhs.cols;
    refCount = rhs.refCount;
    data = rhs.data;

    return *this;
}

float &Matrix::operator()(size_t row, size_t col) const {
    return data[row * cols + col];
}

const Matrix Matrix::operator+(const Matrix &rhs) const {
    if (rows == rhs.rows && cols == rhs.cols) {
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows * cols; ++i) {
            result.data[i] = data[i] + rhs.data[i];
        }
        return result;
    } else {
        std::cerr << "Matrix dimensions do not match for addition" << std::endl;
        return Matrix(0, 0);
    }
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    for (size_t i = 0; i < matrix.rows; ++i) {
        for (size_t j = 0; j < matrix.cols; ++j) {
            os << matrix.data[i * matrix.cols + j] << " ";
        }
        os << std::endl;
    }
    return os;
}
