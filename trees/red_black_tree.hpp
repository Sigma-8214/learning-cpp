#pragma once

#include "binary_search_tree_interface.hpp"

namespace red_black_tree {
enum class Color { Red, Black };

template <class T> struct Node {
    T data;
    Color color;
    Node *parent;
    Node *left;
    Node *right;
};

// ref: https://www.eecs.umich.edu/courses/eecs380/ALG/red_black.html
template <class ItemType>
class RedBlackTree : public BinaryTreeInterface<ItemType> {
    Node<ItemType> *root = nullptr;

    bool addInner(
        Node<ItemType> *&parent, Node<ItemType> *&node, const ItemType &data
    );

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
