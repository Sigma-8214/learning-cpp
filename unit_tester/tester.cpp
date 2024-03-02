#include <functional>
#include <iostream>
#include <string>

#include "tester.hpp"
#include <optional>

const char RESET[] = "\033[0m";
const char GRAY[] = "\033[90m";
const char GREEN[] = "\033[32m";
const char RED[] = "\033[31m";

namespace tester {
void test(std::string name, std::function<Result()> test) {
    std::cout << GRAY << "[*] Running test: " << RESET << name;
    auto result = test();

    if (result.hasPassed()) {
        std::cout << GREEN << " (passed)" << RESET << std::endl;
    } else {
        std::cout << RED << " (failed)" << RESET << std::endl;
        std::cout << "    " << result.getMessage() << std::endl;
    }
}

Result Result::pass() { return Result(true, {}); }

Result Result::fail() { return Result(false, {}); }

Result Result::assert(bool condition) {
    if (condition)
        return Result::pass();
    else
        return Result::fail();
}

template <typename T> Result Result::assertEq(T expected, T actual) {
    return Result::assert(expected == actual);
}

Result Result::chain(const Result other) {
    if (this->passed == false)
        return *this;
    return other;
}
} // namespace tester