#pragma once

#include "binary_search_tree_interface.hpp"

namespace red_black_tree {
template <class T> struct Node {
    T data;
    bool color; // 0 for black, 1 for red
    Node *left;
    Node *right;
};

template <class ItemType>
class RedBlackTree : public BinaryTreeInterface<ItemType> {
    Node<ItemType> *root = nullptr;

  public:
    static RedBlackTree<ItemType> empty();

    bool isEmpty() const;
    int getHeight() const;
    int getNumberOfNodes() const;

    ItemType getRootData() const;

    bool add(const ItemType &newData);
    bool remove(const ItemType &data);
    void clear();

    bool contains(const ItemType &anEntry) const;

    void preorderTraverse(void visit(ItemType &)) const;
    void inorderTraverse(void visit(ItemType &)) const;
    void postorderTraverse(void visit(ItemType &)) const;
};
} // namespace red_black_tree

#include "red_black_tree.cpp"