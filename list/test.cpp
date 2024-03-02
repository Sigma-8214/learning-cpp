#include "../unit_tester/tester.hpp"

#include "list.hpp"

using namespace tester;

int main() {
    auto array = list::ArrayList<int>::empty();

    test("ArrayList Init", [&array]() {
        return Result::assert(array.getLength() == 0)
            .chain(Result::assert(array.isEmpty()));
    });

    array.insert(0, 1234);

    test("ArrayList Insert", [&array]() {
        return Result::assert(array.getLength() == 1)
            .chain(Result::assert(!array.isEmpty()))
            .chain(Result::assert(array.getEntry(0) == 1234));
    });

    array.insert(1, 5678);

    test("ArrayList Insert Again", [&array]() {
        return Result::assert(array.getLength() == 2)
            .chain(Result::assert(!array.isEmpty()))
            .chain(Result::assert(array.getEntry(0) == 1234))
            .chain(Result::assert(array.getEntry(1) == 5678));
    });

    array.setEntry(0, 4321);

    test("ArrayList Set Entry", [&array]() {
        return Result::assert(array.getLength() == 2)
            .chain(Result::assert(!array.isEmpty()))
            .chain(Result::assert(array.getEntry(0) == 4321))
            .chain(Result::assert(array.getEntry(1) == 5678));
    });

    array.remove(0);

    test("ArrayList Remove", [&array]() {
        return Result::assert(array.getLength() == 1)
            .chain(Result::assert(!array.isEmpty()))
            .chain(Result::assert(array.getEntry(0) == 5678));
    });

    return 0;
}