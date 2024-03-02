#include <stdexcept>
#include <vector>

#include "list.hpp"

namespace list {
template <class T> void ArrayList<T>::resize(size_t size) {
    if (size > capacity) {
        capacity = size;
        auto new_data = new T[capacity];
        for (auto i = 0; i < this->size - 1; i++)
            new_data[i] = data[i];
        delete[] data;
        data = new_data;
    }
}

template <class T> ArrayList<T> ArrayList<T>::empty() {
    auto list = ArrayList();
    list.size = 0;
    list.capacity = 0;
    list.data = nullptr;
    return list;
}

template <class T> bool ArrayList<T>::isEmpty() const { return size == 0; }

template <class T> int ArrayList<T>::getLength() const { return size; };

template <class T> void ArrayList<T>::clear() {
    this->size = 0;
    this->capacity = 0;
    delete[] this->data;
};

template <class T> T ArrayList<T>::getEntry(int position) const {
    if (position >= size)
        throw std::out_of_range("Invalid position");
    return data[position];
}

template <class T>
void ArrayList<T>::setEntry(int position, const T &newEntry) {
    if (position >= size)
        throw std::out_of_range("Invalid position");
    data[position] = newEntry;
}

template <class T>
bool ArrayList<T>::insert(int newPosition, const T &newEntry) {
    if (newPosition > this->size)
        throw std::out_of_range("Invalid position");

    this->size++;
    if (this->size > this->capacity)
        this->resize(std::max(this->capacity * 2, (size_t)1));

    this->data[this->size - 1] = newEntry;
    return true;
}

template <class T> bool ArrayList<T>::remove(int position) {
    if (position >= size)
        throw std::out_of_range("Invalid position");

    for (auto i = position; i < size - 1; i++)
        data[i] = data[i + 1];

    this->size--;
    return true;
}
} // namespace list