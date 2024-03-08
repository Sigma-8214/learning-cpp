#include "sorted_list.hpp"

namespace list {
template <class T> SortedLinkedList<T> SortedLinkedList<T>::empty() {
    auto list = SortedLinkedList();
    list.size = 0;
    list.head = nullptr;
    return list;
}

template <class T> bool SortedLinkedList<T>::isEmpty() const {
    return size == 0;
}

template <class T> int SortedLinkedList<T>::getLength() const { return size; }

template <class T> void SortedLinkedList<T>::clear() {
    auto current = head;
    while (current != nullptr) {
        auto next = current->next;
        delete current;
        current = next;
    }
    size = 0;
    head = nullptr;

    return;
}

template <class T> void SortedLinkedList<T>::insert(const T &newEntry) {
    auto newNode = new Node();
    newNode->data = newEntry;

    if (head == nullptr || head->data > newEntry) {
        newNode->next = head;
        head = newNode;
        size++;
        return;
    }

    auto current = head;
    while (current->next != nullptr && current->next->data < newEntry)
        current = current->next;

    newNode->next = current->next;
    current->next = newNode;
    size++;
}

template <class T> void SortedLinkedList<T>::remove(size_t position) {
    if (position >= size)
        throw std::out_of_range("Invalid position");

    if (position == 0) {
        auto temp = head;
        head = head->next;
        delete temp;
        size--;
        return;
    }

    auto current = head;
    for (auto i = 0; i < position - 1; i++)
        current = current->next;

    auto temp = current->next;
    current->next = temp->next;
    delete temp;
    size--;
}

template <class T> T SortedLinkedList<T>::getEntry(size_t position) const {
    if (position >= size)
        throw std::out_of_range("Invalid position");

    auto current = head;
    for (auto i = 0; i < position; i++)
        current = current->next;

    return current->data;
}
} // namespace list