#include "dynarray.h"
#include <stdexcept>
#include <algorithm>

DynArray::DynArray(std::size_t size)
    : size_(size), data_(size > 0 ? new double[size]() : nullptr) {
}

DynArray::DynArray(const DynArray& other)
    : size_(other.size_), data_(other.size_ > 0 ? new double[other.size_] : nullptr) {
    std::copy(other.data_, other.data_ + size_, data_);
}

DynArray& DynArray::operator=(const DynArray& other) {
    if (this == &other) return *this;
    delete[] data_;
    size_ = other.size_;
    data_ = size_ > 0 ? new double[size_] : nullptr;
    std::copy(other.data_, other.data_ + size_, data_);
    return *this;
}

DynArray::~DynArray() {
    delete[] data_;
}

std::size_t DynArray::size() const { return size_; }

double& DynArray::operator[](std::size_t index) {
    if (index >= size_) throw std::out_of_range("DynArray index out of range.");
    return data_[index];
}

double DynArray::operator[](std::size_t index) const {
    if (index >= size_) throw std::out_of_range("DynArray index out of range.");
    return data_[index];
}

void DynArray::resize(std::size_t newSize) {
    double* newData = newSize > 0 ? new double[newSize]() : nullptr;
    std::size_t copyCount = std::min(size_, newSize);
    std::copy(data_, data_ + copyCount, newData);
    delete[] data_;
    data_ = newData;
    size_ = newSize;
}

std::ostream& operator<<(std::ostream& os, const DynArray& a) {
    os << "[";
    for (std::size_t i = 0; i < a.size_; ++i) {
        if (i > 0) os << ", ";
        os << a.data_[i];
    }
    os << "]";
    return os;
}