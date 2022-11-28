#pragma once

#include <iostream>

template <class T>
class BinarySearchTree {
   private:
    struct node {
        T data;
        node *left;
        node *right;
        int size;  // number of all children +1
        node(const T &x, node *lt = nullptr, node *rt = nullptr)
            : data(x), left(lt), right(rt), size(1) {}
        int lsize() { return left ? left->size : 0; }
        int rsize() { return left ? left->size : 0; }
        void upd() {
            size = (left ? left->size : 0) + (right ? right->size : 0) + 1;
        }
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
    T kth(int k) const { return kth(k, root); }

   private:
    bool find(const T &x, node *t) const;
    bool insert(const T &x, node *&t);
    void remove(const T &x, node *&t);
    void midOrder(node *t) const;
    void clear(node *&t);
    T kth(int k, node *t) const;
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
    bool f = 0;
    if (!t) {
        t = new node(x);
        return 1;
    } else if (x < t->data) {
        f = insert(x, t->left);
        t->upd();
        return f;
    } else if (t->data < x) {
        f = insert(x, t->right);
        t->upd();
        return f;
    } else
        return 0;
}

template <class T>
void BinarySearchTree<T>::remove(const T &x, node *&t) {
    if (!t) return;
    if (x < t->data) {
        remove(x, t->left);
    } else if (t->data < x) {
        remove(x, t->right);
    } else if (t->left && t->right) {
        node *tmp = t->right;
        while (tmp->left) tmp = tmp->left;
        t->data = tmp->data;
        remove(t->data, t->right);
    } else {
        node *old = t;
        t = t->left ? t->left : t->right;
        delete old;
    }
    t->upd();
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

class ValueError {};

template <class T>
T BinarySearchTree<T>::kth(int k, node *t) const {
    if (k < 1 || k > t->size) throw ValueError();
    if (k == t->lsize() + 1) return t->data;
    else if (k <= t->lsize()) return kth(k, t->left);
    else return kth(k - t->lsize() - 1, t->right);
}