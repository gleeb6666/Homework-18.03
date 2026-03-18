#pragma once
#include <cstddef>
#include <ostream>

class Matrix {
public:
    Matrix(std::size_t rows, std::size_t cols);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    ~Matrix();

    std::size_t rows() const;
    std::size_t cols() const;

    double& operator()(std::size_t row, std::size_t col);
    double  operator()(std::size_t row, std::size_t col) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

private:
    std::size_t rows_;
    std::size_t cols_;
    double** data_;

    void allocate(std::size_t rows, std::size_t cols);
    void deallocate();
};