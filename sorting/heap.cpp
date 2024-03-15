#include "heap.hpp"

#include "../list/heap.hpp"

namespace heap {
template <size_t N> void heap_sort(list::ArrayList<int> &list) {
    auto heap = heap::Heap<N, int>::empty();
    for (size_t i = 0; i < list.getLength(); i++)
        heap.add(list.getEntry(i));

    auto result = list::ArrayList<int>::empty();
    while (!heap.isEmpty()) {
        result.insert(result.getLength(), heap.peek());
        heap.remove();
    }

    for (size_t i = 0; i < result.getLength(); i++)
        list.setEntry(i, result.getEntry(result.getLength() - i - 1));
}
} // namespace heap