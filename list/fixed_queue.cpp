#include "fixed_queue.hpp"

namespace fixed_queue {
template <size_t N, class T> FixedQueue<N, T> FixedQueue<N, T>::empty() {
    return FixedQueue();
}

template <size_t N, class T> bool FixedQueue<N, T>::isEmpty() const {
    return size == 0;
}

template <size_t N, class T> bool FixedQueue<N, T>::isFull() const {
    return size == N;
}

template <size_t N, class T> bool FixedQueue<N, T>::enqueue(const T &newEntry) {
    if (isFull())
        return false;

    data[tail++] = newEntry;
    tail %= N;
    size++;
    return true;
}

template <size_t N, class T> bool FixedQueue<N, T>::dequeue() {
    if (isEmpty())
        return false;

    head++;
    head %= N;
    size--;
    return true;
}

template <size_t N, class T> T FixedQueue<N, T>::peek() const {
    return data[head];
}
} // namespace fixed_queue