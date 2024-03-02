#pragma once

#include "list.hpp"
namespace stack {
template <class T> class Stack {
  public:
    /** Sees whether this stack is empty.
    @return True if the stack is empty, or false if not. */
    virtual bool isEmpty() const = 0;

    /** Adds a new entry to the top of this stack.
    @post If the operation was successful, newEntry is at the top of the stack.
    @param newEntry The object to be added as a new entry.
    @return True if the addition is successful or false if not. */
    virtual bool push(const T &newEntry) = 0;

    /** Removes the top of this stack.
    @post If the operation was successful, the top of the stack
    has been removed.
    @return True if the removal is successful or false if not. */
    virtual bool pop() = 0;

    /** Returns the top of this stack.
    @pre The stack is not empty.
    @post The top of the stack has been returned, and
    the stack is unchanged.
    @return The top of the stack. */
    virtual T peek() const = 0;
};

template <class T> class ArrayStack : public Stack<T> {
    list::ArrayList<T> list;

  public:
    static ArrayStack empty();

    bool isEmpty() const;
    bool push(const T &newEntry);
    bool pop();
    T peek() const;
};

template <class T> class LinkedStack : public Stack<T> {
    list::LinkedList<T> list;

  public:
    static LinkedStack empty();

    bool isEmpty() const;
    bool push(const T &newEntry);
    bool pop();
    T peek() const;
};
} // namespace stack

#include "stack.cpp"