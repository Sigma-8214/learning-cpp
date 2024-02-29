#pragma once

#include <functional>
#include <optional>
#include <string>

namespace tester {
class Result {
    bool passed;
    std::optional<std::string> msg;

  public:
    Result(bool passed, std::optional<std::string> msg)
        : passed(passed), msg(msg) {}

    bool hasPassed() { return passed; }
    std::string getMessage() { return msg.value(); }

    Result message(std::string msg) {
        this->msg = msg;
        return *this;
    }

    static Result pass();
    static Result fail();
    static Result assert(bool condition);
    template <typename T> static Result assertEq(T expected, T actual);
};

void test(std::string name, std::function<Result()> test);

} // namespace tester