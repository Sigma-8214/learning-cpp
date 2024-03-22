#include "binary_search_tree.hpp"

template <class T> BinarySearchTree<T> BinarySearchTree<T>::empty() {
    return BinarySearchTree();
}

template <class T> bool BinarySearchTree<T>::isEmpty() const {
    return root == nullptr;
}

template <class T> int BinarySearchTree<T>::getHeight() const {
    return getHeightInner(root);
}

template <class T> int getHeightInner(Node<T> *node) {
    if (node == nullptr)
        return 0;
    return 1 +
           std::max(getHeightInner(node->left), getHeightInner(node->right));
}

template <class T> int BinarySearchTree<T>::getNumberOfNodes() const {
    return getNumberOfNodesInner(root);
}

template <class T> int getNumberOfNodesInner(Node<T> *node) {
    if (node == nullptr)
        return 0;
    return 1 + getNumberOfNodesInner(node->left) +
           getNumberOfNodesInner(node->right);
}

template <class T> T BinarySearchTree<T>::getRootData() const {
    if (root == nullptr)
        throw std::invalid_argument("Root node is null.");
    return root->data;
}

template <class T> bool BinarySearchTree<T>::add(const T &newData) {
    return addInner(root, newData);
}

template <class T> bool addInner(Node<T> *&node, const T &newData) {
    if (node == nullptr) {
        node = new Node<T>{newData, nullptr, nullptr};
        return true;
    }
    if (newData < node->data)
        return addInner(node->left, newData);
    if (newData > node->data)
        return addInner(node->right, newData);
    return false;
}

template <class T> bool BinarySearchTree<T>::remove(const T &data) {
    return removeInner(root, data);
}

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
    if (node->left == nullptr)
        return node->data;
    return getMin(node->left);
}

template <class T> void BinarySearchTree<T>::clear() { clearInner(root); }

template <class T> void clearInner(Node<T> *&node) {
    if (node == nullptr)
        return;
    clearInner(node->left);
    clearInner(node->right);
    delete node;
    node = nullptr;
}

template <class T> bool BinarySearchTree<T>::contains(const T &anEntry) const {
    return containsInner(root, anEntry);
}

template <class T> bool containsInner(Node<T> *node, const T &anEntry) {
    if (node == nullptr)
        return false;
    if (anEntry < node->data)
        return containsInner(node->left, anEntry);
    if (anEntry > node->data)
        return containsInner(node->right, anEntry);
    return true;
}

template <class T>
void BinarySearchTree<T>::preorderTraverse(void visit(T &)) const {
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
void BinarySearchTree<T>::inorderTraverse(void visit(T &)) const {
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
void BinarySearchTree<T>::postorderTraverse(void visit(T &)) const {
    postorderTraverseInner(root, visit);
}

template <class T> void postorderTraverseInner(Node<T> *node, void visit(T &)) {
    if (node == nullptr)
        return;
    postorderTraverseInner(node->left, visit);
    postorderTraverseInner(node->right, visit);
    visit(node->data);
}
