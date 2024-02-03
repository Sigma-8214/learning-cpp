#include <iostream>
#include <vector>

std::vector<int> sequential_digits(const uint32_t low, const uint32_t high)
{
    return {};
}

int main()
{
    uint32_t low;
    uint32_t high;
    std::cin >> low >> high;

    auto result = sequential_digits(low, high);
    for (const auto &num : result)
        std::cout << num << std::endl;

    return 0;
}