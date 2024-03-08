#include <iostream>

#include "../unit_tester/tester.hpp"

#include "list.hpp"
#include "sorted_list.hpp"
#include "stack.hpp"

using namespace tester;

template <class List> void test_list(std::string name, List array) {
    std::cout << "== " << name << " ==" << std::endl;

    test("Init", [&array]() {
        return Result::assert(array.getLength() == 0)
            .chain(Result::assert(array.isEmpty()));
    });

    array.insert(0, 1234);
    test("Insert", [&array]() {
        return Result::assert(array.getLength() == 1)
            .chain(Result::assert(!array.isEmpty()))
            .chain(Result::assert(array.getEntry(0) == 1234));
    });

    array.insert(1, 5678);
    test("Insert Again", [&array]() {
        return Result::assert(array.getLength() == 2)
            .chain(Result::assert(!array.isEmpty()))
            .chain(Result::assert(array.getEntry(0) == 1234))
            .chain(Result::assert(array.getEntry(1) == 5678));
    });

    array.setEntry(0, 4321);
    test("Set Entry", [&array]() {
        return Result::assert(array.getLength() == 2)
            .chain(Result::assert(!array.isEmpty()))
            .chain(Result::assert(array.getEntry(0) == 4321))
            .chain(Result::assert(array.getEntry(1) == 5678));
    });

    array.remove(0);
    test("Remove", [&array]() {
        return Result::assert(array.getLength() == 1)
            .chain(Result::assert(!array.isEmpty()))
            .chain(Result::assert(array.getEntry(0) == 5678));
    });

    array.clear();
    test("Clear", [&array]() {
        return Result::assert(array.getLength() == 0)
            .chain(Result::assert(array.isEmpty()));
    });

    std::cout << std::endl;
}

template <class Stack> void test_stack(std::string name, Stack stack) {
    std::cout << "== " << name << " ==" << std::endl;

    test("Init", [&stack]() { return Result::assert(stack.isEmpty()); });

    stack.push(1234);
    test("Push", [&stack]() {
        return Result::assert(!stack.isEmpty())
            .chain(Result::assert(stack.peek() == 1234));
    });

    stack.push(5678);
    test("Push Again", [&stack]() {
        return Result::assert(!stack.isEmpty())
            .chain(Result::assert(stack.peek() == 5678));
    });

    stack.pop();
    test("Pop", [&stack]() {
        return Result::assert(!stack.isEmpty())
            .chain(Result::assert(stack.peek() == 1234));
    });

    stack.pop();
    test("Pop Again", [&stack]() { return Result::assert(stack.isEmpty()); });

    std::cout << std::endl;
}

void test_sorted_list() {
    std::cout << "== Sorted List ==" << std::endl;

    auto list = list::SortedLinkedList<int>::empty();

    test("Init", [&list]() { return Result::assert(list.isEmpty()); });

    list.insert(1234);

    test("Insert", [&list]() {
        return Result::assert(!list.isEmpty())
            .chain(Result::assert(list.getEntry(0) == 1234));
    });

    list.insert(5678);

    test("Insert Again", [&list]() {
        return Result::assert(!list.isEmpty())
            .chain(Result::assert(list.getEntry(0) == 1234))
            .chain(Result::assert(list.getEntry(1) == 5678));
    });

    list.insert(4321);

    test("Insert Again", [&list]() {
        return Result::assert(!list.isEmpty())
            .chain(Result::assert(list.getEntry(0) == 1234))
            .chain(Result::assert(list.getEntry(1) == 4321))
            .chain(Result::assert(list.getEntry(2) == 5678));
    });
}

int main() {
    test_list("Array List", list::ArrayList<int>::empty());
    test_list("Linked List", list::LinkedList<int>::empty());

    test_stack("Array Stack", stack::ArrayStack<int>::empty());
    test_stack("Linked Stack", stack::LinkedStack<int>::empty());

    test_sorted_list();
    return 0;
}
