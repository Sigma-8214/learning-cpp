#include "stack.hpp"

namespace stack {
template <class T> ArrayStack<T> ArrayStack<T>::empty() {
    auto stack = ArrayStack();
    stack.list = list::ArrayList<T>::empty();
    return stack;
}

template <class T> bool ArrayStack<T>::isEmpty() const {
    return list.isEmpty();
}

template <class T> bool ArrayStack<T>::push(const T &newEntry) {
    return list.insert(list.getLength(), newEntry);
}

template <class T> bool ArrayStack<T>::pop() {
    if (list.isEmpty())
        return false;
    list.remove(list.getLength() - 1);
    return true;
}

template <class T> T ArrayStack<T>::peek() const {
    if (list.isEmpty())
        throw std::out_of_range("Invalid position");
    return list.getEntry(list.getLength() - 1);
}

template <class T> LinkedStack<T> LinkedStack<T>::empty() {
    auto stack = LinkedStack();
    stack.list = list::LinkedList<T>::empty();
    return stack;
}

template <class T> bool LinkedStack<T>::isEmpty() const {
    return list.isEmpty();
}

template <class T> bool LinkedStack<T>::push(const T &newEntry) {
    return list.insert(list.getLength(), newEntry);
}

template <class T> bool LinkedStack<T>::pop() {
    if (list.isEmpty())
        return false;
    list.remove(list.getLength() - 1);
    return true;
}

template <class T> T LinkedStack<T>::peek() const {
    if (list.isEmpty())
        throw std::out_of_range("Invalid position");
    return list.getEntry(list.getLength() - 1);
}
} // namespace stack