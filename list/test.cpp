#include <iostream>

#include "../unit_tester/tester.hpp"

#include "list.hpp"

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

int main() {
    test_list("Array List", list::ArrayList<int>::empty());
    test_list("Linked List", list::LinkedList<int>::empty());
    return 0;
}
