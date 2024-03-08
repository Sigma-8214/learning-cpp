#include <cstddef>
#include <iostream>

#include "../list/list.hpp"
#include "../unit_tester/tester.hpp"

#include "merge.hpp"

using namespace tester;

std::string stringify_list(list::ArrayList<int> list) {
    std::string result = "[";
    for (std::size_t i = 0; i < list.getLength(); i++) {
        result += std::to_string(list.getEntry(i));
        if (i < list.getLength() - 1)
            result += ", ";
    }
    result += "]";
    return result;
}

list::ArrayList<int> list_from_array(std::vector<int> arr) {
    auto list = list::ArrayList<int>::empty();
    for (auto i = 0; i < arr.size(); i++)
        list.insert(i, arr[i]);
    return list;
}

void test_sorting(std::string name, list::ArrayList<int> list) {
    test("Merge Sort: " + name, [&list]() {
        merge::merge_sort(list);

        for (auto i = 0; i < list.getLength() - 1; i++)
            if (list.getEntry(i) > list.getEntry(i + 1))
                return Result::fail().context(
                    "List is not sorted: " + stringify_list(list)
                );
        return Result::pass();
    });
}

int main() {
    test_sorting("Pre Sorted", list_from_array({1, 2, 3, 4, 5}));
    test_sorting("Reverse Sorted", list_from_array({5, 4, 3, 2, 1}));
    test_sorting("Random", list_from_array({3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5}));

    return 0;
}