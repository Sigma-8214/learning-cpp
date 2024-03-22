#include <iostream>
#include <memory>

#include "../unit_tester/tester.hpp"

#include "binary_search_tree.hpp"
#include "binary_search_tree_interface.hpp"
#include "red_black_tree.hpp"

using namespace tester;

void test_tree(
    std::string name, std::unique_ptr<BinaryTreeInterface<int>> tree
) {
    test("Test: " + name, [&tree]() {
        auto to_add = {5, 3, 7, 2};

        for (auto &data : to_add)
            tree->add(data);

        if (!tree->contains(2))
            return Result::fail().message("contains(3) failed");

        std::cout << std::endl;

        tree->preorderTraverse([](int &data) { std::cout << data << " "; });
        std::cout << std::endl;

        tree->remove(3);

        tree->preorderTraverse([](int &data) { std::cout << data << " "; });
        std::cout << std::endl;

        if (tree->getNumberOfNodes() != 3)
            return Result::fail().message("getNumberOfNodes() failed");

        tree->clear();
        if (!tree->isEmpty())
            return Result::fail().message("clear() failed");

        return Result::pass();
    });
}

int main() {
    test_tree("Binary Tree", std::make_unique<tree::BinarySearchTree<int>>());
    test_tree(
        "Red Black Tree", std::make_unique<red_black_tree::RedBlackTree<int>>()
    );
    return 0;
}