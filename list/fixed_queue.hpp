#pragma once

#include <cinttypes>

namespace fixed_queue {
template <size_t N, class T> class FixedQueue {
    T data[N];
    size_t head = 0;
    size_t tail = 0;
    size_t size = 0;

  public:
    static FixedQueue empty();

    bool isEmpty() const;
    bool isFull() const;

    bool enqueue(const T &newEntry);
    bool dequeue();
    T peek() const;
};
} // namespace fixed_queue

#include "fixed_queue.cpp"