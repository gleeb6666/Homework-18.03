#include "matrix.h"
#include <stdexcept>
#include <iomanip>

void Matrix::allocate(std::size_t rows, std::size_t cols) {
    data_ = new double* [rows];
    for (std::size_t i = 0; i < rows; ++i) {
        data_[i] = new double[cols]();
    }
}

void Matrix::deallocate() {
    for (std::size_t i = 0; i < rows_; ++i) {
        delete[] data_[i];
    }
    delete[] data_;
}

Matrix::Matrix(std::size_t rows, std::size_t cols)
    : rows_(rows), cols_(cols) {
    if (rows == 0 || cols == 0)
        throw std::invalid_argument("Matrix dimensions must be > 0.");
    allocate(rows_, cols_);
}

Matrix::Matrix(const Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
    allocate(rows_, cols_);
    for (std::size_t i = 0; i < rows_; ++i)
        for (std::size_t j = 0; j < cols_; ++j)
            data_[i][j] = other.data_[i][j];
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this;
    deallocate();
    rows_ = other.rows_;
    cols_ = other.cols_;
    allocate(rows_, cols_);
    for (std::size_t i = 0; i < rows_; ++i)
        for (std::size_t j = 0; j < cols_; ++j)
            data_[i][j] = other.data_[i][j];
    return *this;
}

Matrix::~Matrix() {
    deallocate();
}

std::size_t Matrix::rows() const { return rows_; }
std::size_t Matrix::cols() const { return cols_; }

double& Matrix::operator()(std::size_t row, std::size_t col) {
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("Matrix index out of range.");
    return data_[row][col];
}

double Matrix::operator()(std::size_t row, std::size_t col) const {
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("Matrix index out of range.");
    return data_[row][col];
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (std::size_t i = 0; i < m.rows_; ++i) {
        for (std::size_t j = 0; j < m.cols_; ++j) {
            os << std::setw(8) << m.data_[i][j];
        }
        os << "\n";
    }
    return os;
}