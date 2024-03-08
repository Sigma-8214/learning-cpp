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

template <class T> void ArrayList<T>::swap(int a, int b) {
    if (a >= size || b >= size)
        throw std::out_of_range("Invalid position");

    auto temp = data[a];
    data[a] = data[b];
    data[b] = temp;
}

template <class T> LinkedList<T> LinkedList<T>::empty() {
    auto list = LinkedList();
    list.size = 0;
    list.head = nullptr;
    return list;
}

template <class T> bool LinkedList<T>::isEmpty() const { return size == 0; }

template <class T> int LinkedList<T>::getLength() const { return size; };

template <class T> void LinkedList<T>::clear() {
    auto current = head;
    while (current != nullptr) {
        auto next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    size = 0;
};

template <class T> T LinkedList<T>::getEntry(int position) const {
    if (position >= size)
        throw std::out_of_range("Invalid position");

    auto current = head;
    for (auto i = 0; i < position; i++)
        current = current->next;

    return current->data;
}

template <class T>
void LinkedList<T>::setEntry(int position, const T &newEntry) {
    if (position >= size)
        throw std::out_of_range("Invalid position");

    auto current = head;
    for (auto i = 0; i < position; i++)
        current = current->next;

    current->data = newEntry;
    return;
}

template <class T>
bool LinkedList<T>::insert(int newPosition, const T &newEntry) {
    if (newPosition > size)
        throw std::out_of_range("Invalid position");

    auto new_node = new Node();
    new_node->data = newEntry;

    if (newPosition == 0) {
        new_node->next = head;
        head = new_node;
    } else {
        auto current = head;
        for (auto i = 0; i < newPosition - 1; i++)
            current = current->next;
        new_node->next = current->next;
        current->next = new_node;
    }

    size++;
    return true;
}

template <class T> bool LinkedList<T>::remove(int position) {
    if (position >= size)
        throw std::out_of_range("Invalid position");

    if (position == 0) {
        auto old_head = head;
        head = head->next;
        delete old_head;
    } else {
        auto current = head;
        for (auto i = 0; i < position - 1; i++)
            current = current->next;
        auto old_node = current->next;
        current->next = old_node->next;
        delete old_node;
    }

    size--;
    return true;
}
} // namespace list