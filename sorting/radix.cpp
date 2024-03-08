#include <array>

#include "../list/list.hpp"
#include <iostream>

namespace radix {
int get_digit(int number, int place) { return (number / place) % 10; }

void radix_sort(list::ArrayList<int> &list) {
    auto max = list.getEntry(0);
    for (auto i = 1; i < list.getLength(); i++)
        if (list.getEntry(i) > max)
            max = list.getEntry(i);

    auto temp = list::ArrayList<int>::empty();
    for (auto i = 0; i < list.getLength(); i++)
        temp.insert(i, 0);

    for (uint64_t place = 1; place <= max; place *= 10) {
        auto counts = std::array<int, 10>();

        for (auto i = 0; i < list.getLength(); i++) {
            auto digit = get_digit(list.getEntry(i), place);
            counts[digit]++;
        }

        for (auto i = 1; i < 10; i++)
            counts[i] += counts[i - 1];

        for (auto i = list.getLength() - 1; i >= 0; i--) {
            auto digit = get_digit(list.getEntry(i), place);
            auto index = counts[digit] - 1;
            temp.setEntry(index, list.getEntry(i));
            counts[digit]--;
        }

        for (auto i = 0; i < list.getLength(); i++)
            list.setEntry(i, temp.getEntry(i));
    }
}
} // namespace radix