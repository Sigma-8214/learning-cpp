#include <cstddef>

#include "../list/list.hpp"

#include "merge.hpp"

namespace merge {
void merge_inner(
    list::ArrayList<int> &list, size_t start, size_t middle, size_t end
) {
    size_t a = start;
    size_t b = middle + 1;

    while (a <= middle && b <= end) {
        if (list.getEntry(a) > list.getEntry(b)) {
            int value = list.getEntry(b);
            for (size_t i = b; i > a; i--)
                list.setEntry(i, list.getEntry(i - 1));
            list.setEntry(a, value);
            middle++;
            b++;
        }
        a++;
    }
}

void merge_sort_inner(
    list::ArrayList<int> &list, std::size_t start, std::size_t end
) {
    if (start >= end)
        return;

    size_t middle = (start + end) / 2;
    merge_sort_inner(list, start, middle);
    merge_sort_inner(list, middle + 1, end);

    merge_inner(list, start, middle, end);
}

void merge_sort(list::ArrayList<int> &list) {
    merge_sort_inner(list, 0, list.getLength() - 1);
}
} // namespace merge