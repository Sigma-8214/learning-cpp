#include "red_black_tree.hpp"

namespace red_black_tree {
template <class ItemType>
RedBlackTree<ItemType> RedBlackTree<ItemType>::empty() {
    return RedBlackTree<ItemType>();
}

template <class ItemType> bool RedBlackTree<ItemType>::isEmpty() const {
    return root == nullptr;
}

template <class ItemType> int RedBlackTree<ItemType>::getHeight() const {
    return getHeightInner(root);
}

template <class ItemType> int getHeightInner(Node<ItemType> *node) {
    if (node == nullptr)
        return 0;
    return 1 +
           std::max(getHeightInner(node->left), getHeightInner(node->right));
}

template <class ItemType> int RedBlackTree<ItemType>::getNumberOfNodes() const {
    return getNumberOfNodesInner(root);
}

template <class ItemType> int getNumberOfNodesInner(Node<ItemType> *node) {
    if (node == nullptr)
        return 0;
    return 1 + getNumberOfNodesInner(node->left) +
           getNumberOfNodesInner(node->right);
}

template <class ItemType> ItemType RedBlackTree<ItemType>::getRootData() const {
    return root->data;
}

template <class ItemType>
bool RedBlackTree<ItemType>::add(const ItemType &newData) {
    return addInner(root, root, newData);
}

template <class ItemType>
bool RedBlackTree<ItemType>::addInner(
    Node<ItemType> *&parent, Node<ItemType> *&node, const ItemType &newData
) {
    if (node == nullptr) {
        node =
            new Node<ItemType>{newData, Color::Red, parent, nullptr, nullptr};
        return true;
    }

    if (newData == node->data)
        return false;

    if (newData < node->data)
        addInner(node, node->left, newData);
    if (newData > node->data)
        addInner(node, node->right, newData);

    while (node != root && node->parent->color == Color::Red) {
        if (node->parent == node->parent->parent->left) {
            Node<ItemType> *uncle = node->parent->parent->right;
            if (uncle->color == Color::Red) {
                node->parent->color = Color::Black;
                uncle->color = Color::Black;
                node->parent->parent->color = Color::Red;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(root, node);
                }
                node->parent->color = Color::Black;
                node->parent->parent->color = Color::Red;
                rightRotate(root, node->parent->parent);
            }
        } else {
            Node<ItemType> *uncle = node->parent->parent->left;
            if (uncle->color == Color::Red) {
                node->parent->color = Color::Black;
                uncle->color = Color::Black;
                node->parent->parent->color = Color::Red;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(root, node);
                }
                node->parent->color = Color::Black;
                node->parent->parent->color = Color::Red;
                leftRotate(root, node->parent->parent);
            }
        }
    }

    root->color = Color::Black;
    return true;
}

template <class ItemType>
void leftRotate(Node<ItemType> *&root, Node<ItemType> *&node) {
    Node<ItemType> *right = node->right;
    node->right = right->left;
    if (right->left != nullptr)
        right->left->parent = node;
    right->parent = node->parent;
    if (node->parent == nullptr)
        root = right;
    else if (node == node->parent->left)
        node->parent->left = right;
    else
        node->parent->right = right;
    right->left = node;
    node->parent = right;
}

template <class ItemType>
void rightRotate(Node<ItemType> *&root, Node<ItemType> *&node) {
    Node<ItemType> *left = node->left;
    node->left = left->right;
    if (left->right != nullptr)
        left->right->parent = node;
    left->parent = node->parent;
    if (node->parent == nullptr)
        root = left;
    else if (node == node->parent->right)
        node->parent->right = left;
    else
        node->parent->left = left;
    left->right = node;
    node->parent = left;
}

template <class ItemType>
bool RedBlackTree<ItemType>::remove(const ItemType &data) {
    return removeInner(root, data);
}

// todo: implement red-black tree deletion
template <class T> bool removeInner(Node<T> *&node, const T &data) {
    if (node == nullptr)
        return false;

    if (data < node->data)
        return removeInner(node->left, data);
    if (data > node->data)
        return removeInner(node->right, data);

    if (node->left == nullptr && node->right == nullptr) {
        delete node;
        node = nullptr;
        return true;
    }

    if (node->left == nullptr) {
        Node<T> *temp = node;
        node = node->right;
        delete temp;
        return true;
    }

    if (node->right == nullptr) {
        Node<T> *temp = node;
        node = node->left;
        delete temp;
        return true;
    }

    node->data = getMin(node->right);
    return removeInner(node->right, node->data);
}

template <class T> T getMin(Node<T> *node) {
    while (node->left != nullptr)
        node = node->left;
    return node->data;
}

template <class ItemType> void RedBlackTree<ItemType>::clear() {
    clearInner(root);
    root = nullptr;
}

template <class ItemType> void clearInner(Node<ItemType> *node) {
    if (node == nullptr)
        return;
    clearInner(node->left);
    clearInner(node->right);
    delete node;
}

template <class ItemType>
bool RedBlackTree<ItemType>::contains(const ItemType &anEntry) const {
    return containsInner(root, anEntry);
}

template <class ItemType>
bool containsInner(Node<ItemType> *node, const ItemType &anEntry) {
    if (node == nullptr)
        return false;
    if (node->data < anEntry)
        return containsInner(node->right, anEntry);
    if (node->data > anEntry)
        return containsInner(node->left, anEntry);
    return true;
}

template <class T>
void RedBlackTree<T>::preorderTraverse(void visit(T &)) const {
    preorderTraverseInner(root, visit);
}

template <class T> void preorderTraverseInner(Node<T> *node, void visit(T &)) {
    if (node == nullptr)
        return;
    visit(node->data);
    preorderTraverseInner(node->left, visit);
    preorderTraverseInner(node->right, visit);
}

template <class T>
void RedBlackTree<T>::inorderTraverse(void visit(T &)) const {
    inorderTraverseInner(root, visit);
}

template <class T> void inorderTraverseInner(Node<T> *node, void visit(T &)) {
    if (node == nullptr)
        return;
    inorderTraverseInner(node->left, visit);
    visit(node->data);
    inorderTraverseInner(node->right, visit);
}

template <class T>
void RedBlackTree<T>::postorderTraverse(void visit(T &)) const {
    postorderTraverseInner(root, visit);
}

template <class T> void postorderTraverseInner(Node<T> *node, void visit(T &)) {
    if (node == nullptr)
        return;
    postorderTraverseInner(node->left, visit);
    postorderTraverseInner(node->right, visit);
    visit(node->data);
}
} // namespace red_black_tree