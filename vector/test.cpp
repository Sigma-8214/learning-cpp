#include <iostream>

#include "../unit_tester/tester.hpp"
#include "vector.hpp"

using namespace vector;
using namespace tester;

int main() {
    auto vec = Vector<3>::from({1.0, 10.0, 5.0});
    auto vec2 = Vector<3>::from({2.0, 20.0, 5.0});

    test("Add Vectors", [&vec, &vec2]() {
        return Result::assert(Vector<3>::from({3.0, 30.0, 10.0}) == vec + vec2);
    });

    test("Subtract Vectors", [&vec, &vec2]() {
        return Result::assert(
            Vector<3>::from({-1.0, -10.0, 0.0}) == vec - vec2
        );
    });

    test("Scaler Multiplication", [&vec]() {
        return Result::assert(Vector<3>::from({3.0, 30.0, 15.0}) == 3.0 * vec);
    });

    test("Cross Product", [&vec, &vec2]() {
        return Result::assert(
            Vector<3>::from({-50.0, 5.0, 0.0}) == vec.cross(vec2)
        );
    });

    return 0;
}