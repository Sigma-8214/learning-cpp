#include <iostream>
#include <string>

#include "tester.hpp"

using namespace tester;

int main() {
    test("Test 1", []() { return Result::pass(); });
    test("Test 2", []() { return Result::fail("This test failed"); });

    return 0;
}