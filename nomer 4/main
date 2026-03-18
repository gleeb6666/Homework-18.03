#include <iostream>
#include "matrix.h"

int main() {
    Matrix a(2, 3);
    a(0, 0) = 1; a(0, 1) = 2; a(0, 2) = 3;
    a(1, 0) = 4; a(1, 1) = 5; a(1, 2) = 6;

    std::cout << "Matrix a (" << a.rows() << "x" << a.cols() << "):\n" << a << "\n";

    Matrix b(a);
    b(0, 0) = 99;

    std::cout << "Matrix b (copy of a, b(0,0)=99):\n" << b << "\n";
    std::cout << "Matrix a (unchanged):\n" << a << "\n";

    Matrix c(2, 3);
    c = a;
    std::cout << "Matrix c (assigned from a):\n" << c << "\n";

    try {
        a(5, 5);
    }
    catch (const std::out_of_range& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }

    return 0;
}
