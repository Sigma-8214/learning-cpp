#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> sequential_digits(const uint32_t low, const uint32_t high) {
    auto out = std::vector<int>{};
    for (uint32_t start = 1; start <= 9; start++) {
        uint32_t num = start;
        for (uint32_t next = start + 1; next <= 9; next++) {
            num = num * 10 + next;
            if (num > high)
                break;
            if (num >= low)
                out.push_back(num);
        }
    }

    std::sort(out.begin(), out.end());
    return out;
}

int main() {
    uint32_t low;
    uint32_t high;
    std::cin >> low >> high;

    auto result = sequential_digits(low, high);
    for (const auto &num : result)
        std::cout << num << std::endl;

    return 0;
}