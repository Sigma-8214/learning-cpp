#include <cstddef>
#include <iostream>

#include "../list/list.hpp"
#include "../unit_tester/tester.hpp"

#include "heap.hpp"
#include "merge.hpp"
#include "radix.hpp"

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

void test_sorting(
    std::function<void(list::ArrayList<int>)> sort, std::string name,
    std::vector<int> rawList
) {
    auto list = list_from_array(rawList);
    sort(list);

    test(name, [&list]() {
        for (auto i = 0; i < list.getLength() - 1; i++)
            if (list.getEntry(i) > list.getEntry(i + 1))
                return Result::fail().context(
                    "List is not sorted: " + stringify_list(list)
                );
        return Result::pass();
    });
}

int main() {
    auto pre_sorted = {1, 2, 3, 4, 5};
    auto rev_sorted = {5, 4, 3, 2, 1};
    auto random_sorted = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    auto big_random_sorted = {27, 14, 11, 5, 2, 9, 3, 1, 0, 8, 6, 4, 7, 10, 13};

    std::cout << "== Merge Sort ==" << std::endl;
    auto merge = [](list::ArrayList<int> list) { merge::merge_sort(list); };
    test_sorting(merge, "Pre Sorted", pre_sorted);
    test_sorting(merge, "Reverse Sorted", rev_sorted);
    test_sorting(merge, "Random", random_sorted);
    test_sorting(merge, "Big Random", big_random_sorted);
    std::cout << std::endl;

    std::cout << "== Radix Sort ==" << std::endl;
    auto radix = [](list::ArrayList<int> list) { radix::radix_sort(list); };
    test_sorting(radix, "Pre Sorted", pre_sorted);
    test_sorting(radix, "Reverse Sorted", rev_sorted);
    test_sorting(radix, "Random", random_sorted);
    test_sorting(radix, "Big Random", big_random_sorted);
    std::cout << std::endl;

    std::cout << "== Heap Sort ==" << std::endl;
    auto heap = [](list::ArrayList<int> list) { heap::heap_sort<15>(list); };
    test_sorting(heap, "Pre Sorted", pre_sorted);
    test_sorting(heap, "Reverse Sorted", rev_sorted);
    test_sorting(heap, "Random", random_sorted);
    test_sorting(heap, "Big Random", big_random_sorted);

    return 0;
}