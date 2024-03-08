#include <cstddef>

#include "../list/list.hpp"
#include "../unit_tester/tester.hpp"
#include <iostream>

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

void merge_inner(
    list::ArrayList<int> &list, size_t start, size_t middle, size_t end
) {
    size_t a = start;
    size_t b = middle + 1;

    list::ArrayList<int> merged = list::ArrayList<int>::empty();

    while (a <= middle && b <= end) {
        if (list.getEntry(a) <= list.getEntry(b))
            merged.insert(merged.getLength(), list.getEntry(a++));
        else
            merged.insert(merged.getLength(), list.getEntry(b++));
    }

    while (a <= middle)
        merged.insert(merged.getLength(), list.getEntry(a++));

    while (b <= end)
        merged.insert(merged.getLength(), list.getEntry(b++));

    for (size_t i = start; i <= end; i++)
        list.setEntry(i, merged.getEntry(i - start));
}

void merge_sort_inner(
    list::ArrayList<int> &list, std::size_t start, std::size_t end
) {
    if (start >= end)
        return;

    size_t middle = (start + end) / 2;
    merge_sort_inner(list, start, middle);
    merge_sort_inner(list, middle + 1, end);

    return merge_inner(list, start, middle, end);
}

void merge_sort(list::ArrayList<int> &list) {
    merge_sort_inner(list, 0, list.getLength() - 1);
}

list::ArrayList<int> list_from_array(std::vector<int> arr) {
    auto list = list::ArrayList<int>::empty();
    for (auto i = 0; i < arr.size(); i++)
        list.insert(i, arr[i]);
    return list;
}

void test_sorting(std::string name, list::ArrayList<int> list) {
    test("Merge Sort: " + name, [&list]() {
        merge_sort(list);

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