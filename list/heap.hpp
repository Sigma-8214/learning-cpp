#pragma once

#include <cinttypes>

namespace heap {
template <size_t N, class T> class Heap {
    T data[N];
    size_t size = 0;

    void heapify(size_t index);

  public:
    static Heap empty();

    bool isEmpty() const;
    bool isFull() const;

    bool add(const T &newEntry);
    bool remove();
    T peek() const;
};
} // namespace heap

#include "heap.cpp"