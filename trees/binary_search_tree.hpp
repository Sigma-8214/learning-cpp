#pragma once

#include "binary_search_tree_interface.hpp"

namespace tree {
template <class T> struct Node {
    T data;
    Node *left;
    Node *right;
};

template <class ItemType>
class BinarySearchTree : public BinaryTreeInterface<ItemType> {
    Node<ItemType> *root = nullptr;

  public:
    static BinarySearchTree<ItemType> empty();

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
} // namespace tree

#include "binary_search_tree.cpp"
