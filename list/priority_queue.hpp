#pragma once

#include <cinttypes>

#include "heap.hpp"

namespace priority_queue {
template <size_t N, class T> class PriorityQueue {
    struct Wrapper {
        T value;
        size_t priority;

        bool operator>(const Wrapper &other) const {
            return priority > other.priority;
        }
    };

    heap::Heap<N, Wrapper> heap;

  public:
    static PriorityQueue empty();

    bool isEmpty() const;
    bool isFull() const;

    bool add(const T &newEntry, size_t priority);
    bool remove();
    T peek() const;
    size_t peekPriority() const;
};
} // namespace priority_queue

#include "priority_queue.cpp"