#include "heap.hpp"

namespace heap {
template <size_t N, class T> void Heap<N, T>::heapify(size_t index) {
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;

    size_t largest = index;
    if (left < size && data[left] > data[largest])
        largest = left;
    if (right < size && data[right] > data[largest])
        largest = right;

    if (largest == index)
        return;

    std::swap(data[index], data[largest]);
    heapify(largest);
}

template <size_t N, class T> Heap<N, T> Heap<N, T>::empty() { return Heap(); }

template <size_t N, class T> bool Heap<N, T>::isEmpty() const {
    return size == 0;
}

template <size_t N, class T> bool Heap<N, T>::isFull() const {
    return size == N;
}

template <size_t N, class T> bool Heap<N, T>::add(const T &newEntry) {
    if (isFull())
        return false;

    data[size++] = newEntry;
    for (size_t i = size / 2; i > 0; i--)
        heapify(i - 1);

    return true;
}

template <size_t N, class T> bool Heap<N, T>::remove() {
    if (isEmpty())
        return false;

    std::swap(data[0], data[--size]);
    heapify(0);

    return true;
}

template <size_t N, class T> T Heap<N, T>::peek() const {
    if (isEmpty())
        throw std::out_of_range("Heap is empty");

    return data[0];
}
} // namespace heap