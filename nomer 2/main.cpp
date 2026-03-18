#include <iostream>
#include "phone.h"

int main() {
    const std::string models[] = { "Pon M10", "Pon M10 Pro", "Pon M10 Pro Max" };

    for (const auto& name : models) {
        Phone* p = PhoneFactory::create(name);
        std::cout << *p << "\n";
        p->call();
        p->photo();
        std::cout << "\n";
        delete p;
    }

    try {
        Phone* p = PhoneFactory::create("Pon X999");
        delete p;
    }
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << "\n";
    }

    return 0;
}
