#include <functional>
#include <optional>
#include <string>

namespace tester {
class Result {
    bool passed;
    std::optional<std::string> message;

  public:
    Result(bool passed, std::optional<std::string> message)
        : passed(passed), message(message) {}

    bool hasPassed() { return passed; }
    std::string getMessage() { return message.value(); }

    static Result pass();
    static Result fail(std::string message);
    static Result assert(bool condition, std::string message);
    template <typename T>
    static Result assertEq(T expected, T actual, std::string message);
};

void test(std::string name, std::function<Result()> test);

} // namespace tester