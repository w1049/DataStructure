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

   private:
    void midOrder(node *t) const;
    void clear(node *&t);
};

template <class T>
void BinarySearchTree<T>::midOrder() const {
    midOrder(root);
}

template <class T>
bool BinarySearchTree<T>::find(const T &x) const {
    node *t = root;
    while (t) {
        if (x < t->data)
            t = t->left;
        else if (t->data < x)
            t = t->right;
        else
            return 1;
    }
    return 0;
}

template <class T>
bool BinarySearchTree<T>::insert(const T &x) {
    node **t = &root;
    while (*t) {
        if (x < (*t)->data)
            t = &((*t)->left);
        else if ((*t)->data < x)
            t = &((*t)->right);
        else
            return 0;
    }
    *t = new node(x);
    return 1;
}

template <class T>
void BinarySearchTree<T>::remove(const T &x) {
    node **t = &root;
    const T *px = &x;
    while (*t) {
        if (*px < (*t)->data)
            t = &((*t)->left);
        else if ((*t)->data < *px)
            t = &((*t)->right);
        else if ((*t)->left && (*t)->right) {
            node *tmp = (*t)->right;
            while (tmp->left) tmp = tmp->left;
            (*t)->data = tmp->data;
            px = &(*t)->data, t = &((*t)->right);
        } else {
            node *old = *t;
            *t = (*t)->left ? (*t)->left : (*t)->right;
            delete old;
        }
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
