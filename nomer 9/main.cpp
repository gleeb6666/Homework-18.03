#include <iostream>
#include "dynarray.h"

int main() {
    DynArray a(5);
    for (std::size_t i = 0; i < a.size(); ++i)
        a[i] = static_cast<double>(i + 1);

    std::cout << "Original:       " << a << "\n";

    a.resize(3);
    std::cout << "After resize(3): " << a << "\n";

    a.resize(6);
    std::cout << "After resize(6): " << a << "\n";

    return 0;
}
