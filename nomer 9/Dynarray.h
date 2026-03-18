#pragma once
#include <cstddef>
#include <ostream>

class DynArray {
public:
    explicit DynArray(std::size_t size = 0);
    DynArray(const DynArray& other);
    DynArray& operator=(const DynArray& other);
    ~DynArray();

    std::size_t size() const;

    double& operator[](std::size_t index);
    double  operator[](std::size_t index) const;

    void resize(std::size_t newSize);

    friend std::ostream& operator<<(std::ostream& os, const DynArray& a);

private:
    std::size_t size_;
    double* data_;
};