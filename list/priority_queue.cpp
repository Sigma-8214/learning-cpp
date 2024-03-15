#include "priority_queue.hpp"

namespace priority_queue {
template <size_t N, class T> PriorityQueue<N, T> PriorityQueue<N, T>::empty() {
    return PriorityQueue();
}

template <size_t N, class T> bool PriorityQueue<N, T>::isEmpty() const {
    return heap.isEmpty();
}

template <size_t N, class T> bool PriorityQueue<N, T>::isFull() const {
    return heap.isFull();
}

template <size_t N, class T>
bool PriorityQueue<N, T>::add(const T &newEntry, size_t priority) {
    Wrapper wrapper = {newEntry, priority};
    return heap.add(wrapper);
}

template <size_t N, class T> bool PriorityQueue<N, T>::remove() {
    return heap.remove();
}

template <size_t N, class T> T PriorityQueue<N, T>::peek() const {
    return heap.peek().value;
}

template <size_t N, class T> size_t PriorityQueue<N, T>::peekPriority() const {
    return heap.peek().priority;
}
} // namespace priority_queue
