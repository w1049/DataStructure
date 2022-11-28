#pragma once

#include <iostream>

template <class T>
class BinarySearchTree {
   private:
    struct node {
        T data;
        node *left;
        node *right;
        node(const T &x, node *lt = nullptr, node *rt = nullptr)
            : data(x), left(lt), right(rt) {}
        ~node() {}
    };
    node *root;

   public:
    BinarySearchTree(node *t = nullptr) : root(t) {}
    ~BinarySearchTree() { clear(root); }
    bool find(const T &x) const;
    bool insert(const T &x);
    void remove(const T &x);
    void midOrder() const;
    void removeSmaller(const T &x) { removeSmaller(x, root); }
    void removeGreater(const T &x) { removeGreater(x, root); }
    void removeRange(const T &l, const T &r);

   private:
    bool find(const T &x, node *t) const;
    bool insert(const T &x, node *&t);
    void remove(const T &x, node *&t);
    void midOrder(node *t) const;
    void clear(node *&t);

    void removeSmaller(const T &x, node *&t);  // remove all nodes < x
    void removeGreater(const T &x, node *&t);  // remove all nodes > x
    void removeRange(const T &l, const T &r,
                     node *&t);  // remove nodes in [l, r]
};

template <class T>
bool BinarySearchTree<T>::find(const T &x) const {
    return find(x, root);
}

template <class T>
bool BinarySearchTree<T>::insert(const T &x) {
    return insert(x, root);
}

template <class T>
void BinarySearchTree<T>::remove(const T &x) {
    remove(x, root);
}

template <class T>
void BinarySearchTree<T>::midOrder() const {
    midOrder(root);
}

template <class T>
bool BinarySearchTree<T>::find(const T &x, node *t) const {
    if (!t)
        return 0;
    else if (x < t->data)
        return find(x, t->left);
    else if (t->data < x)
        return find(x, t->right);
    else
        return 1;
}

template <class T>
bool BinarySearchTree<T>::insert(const T &x, node *&t) {
    if (!t) {
        t = new node(x);
        return 1;
    } else if (x < t->data)
        return insert(x, t->left);
    else if (t->data < x)
        return insert(x, t->right);
    else
        return 0;
}

template <class T>
void BinarySearchTree<T>::remove(const T &x, node *&t) {
    if (!t) return;
    if (x < t->data)
        remove(x, t->left);
    else if (t->data < x)
        remove(x, t->right);
    else if (t->left && t->right) {
        node *tmp = t->right;
        while (tmp->left) tmp = tmp->left;
        t->data = tmp->data;
        remove(t->data, t->right);
    } else {
        node *old = t;
        t = t->left ? t->left : t->right;
        delete old;
    }
}

template <class T>
void BinarySearchTree<T>::midOrder(node *t) const {
    if (!t) return;
    midOrder(t->left);
    std::cout << t->data << " ";
    midOrder(t->right);
}

template <class T>
void BinarySearchTree<T>::clear(node *&t) {
    if (!t) return;
    clear(t->left);
    clear(t->right);
    delete t;
    t = nullptr;
}

template <class T>
void BinarySearchTree<T>::removeSmaller(const T &x, node *&t) {
    if (!t)
        return;
    else if (x < t->data)
        removeSmaller(x, t->left);
    else if (t->data < x) {
        clear(t->left);              // remove left tree
        removeSmaller(x, t->right);  // remove in right tree
        remove(t->data, t);          // remove itself
    } else
        clear(t->left);  // remove left tree
}

template <class T>
void BinarySearchTree<T>::removeGreater(const T &x, node *&t) {
    if (!t)
        return;
    else if (t->data < x)
        removeGreater(x, t->right);
    else if (x < t->data) {
        clear(t->right);            // remove right tree
        removeGreater(x, t->left);  // remove in left tree
        remove(t->data, t);         // remove itself
    } else
        clear(t->right);  // remove right tree
}

template <class T>
void BinarySearchTree<T>::removeRange(const T &l, const T &r) {
    if (l == r)
        remove(l, root);
    else
        removeRange(l, r, root);
}

template <class T>
void BinarySearchTree<T>::removeRange(const T &l, const T &r, node *&t) {
    // let N be the nodes to be removed
    if (!t)
        return;
    else if (t->data < l)
        removeRange(l, r, t->right);  // t < l, N in right of t
    else if (r < t->data)             // t > r, N in left of t
        removeRange(l, r, t->left);
    else if (t->data == l) {         // left is safe
        removeSmaller(r, t->right);  // N in right, N < r
        remove(r, t);
        remove(t->data, t);
    } else if (t->data == r) {  // right is safe
        removeGreater(l, t);    // N in left, N > l
        remove(l, t);
        remove(t->data, t);
    } else {  // t is in N
        removeRange(l, r, t->left);
        removeRange(l, r, t->right);
        remove(t->data, t);
    }
}