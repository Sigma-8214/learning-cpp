#include <iostream>

#include "../unit_tester/tester.hpp"

#include "binary_search_tree.hpp"

using namespace tester;

int main() {
    test("test", []() {
        auto tree = BinarySearchTree<int>::empty();
        tree.add(5);
        tree.add(3);
        tree.add(7);
        tree.add(2);

        if (!tree.contains(3))
            return Result::fail().message("contains 3 failed");

        std::cout << std::endl;

        tree.preorderTraverse([](int &data) { std::cout << data << " "; });
        std::cout << std::endl;

        tree.remove(3);

        tree.preorderTraverse([](int &data) { std::cout << data << " "; });
        std::cout << std::endl;

        if (tree.getNumberOfNodes() != 3)
            return Result::fail().message("getNumberOfNodes failed");

        if (tree.getHeight() != 2)
            return Result::fail().message("getHeight failed");

        tree.clear();
        if (!tree.isEmpty())
            return Result::fail().message("clear failed");

        return Result::pass();
    });
    return 0;
}