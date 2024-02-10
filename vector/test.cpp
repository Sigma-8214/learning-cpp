#include <iostream>

#include "vector.hpp"

using namespace vector;

int main() {
    auto vec = Vector<3>::from({1.0, 10.0, 5.0});
    auto vec2 = Vector<3>::from({2.0, 20.0, 5.0});

    std::cout << vec.to_string() << std::endl;
    std::cout << vec2.to_string() << std::endl;
    std::cout << std::endl;

    std::cout << "Add: " << (vec + vec2).to_string() << std::endl;
    std::cout << "Sub: " << (vec - vec2).to_string() << std::endl;
    std::cout << "Cross: " << vec.cross(vec2).to_string() << std::endl;

    return 0;
}