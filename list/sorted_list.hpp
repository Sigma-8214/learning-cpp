#pragma once

namespace list {
template <class T> class SortedLinkedList {

    struct Node {
        T data;
        Node *next;
    };

    Node *head;
    size_t size;

  public:
    static SortedLinkedList empty();

    bool isEmpty() const;
    int getLength() const;
    void clear();
    void insert(const T &newEntry);
    void remove(size_t position);
    T getEntry(size_t position) const;
};
} // namespace list

#include "sorted_list.cpp"