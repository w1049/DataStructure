#pragma once
#include <iostream>

#include "LinkedQueue.h"

using std::cin;
using std::cout;
using std::endl;

template <class T>
class BinaryTree {
   private:
    struct Node {
        T data;
        Node *left, *right;
        Node() : left(nullptr), right(nullptr) {}
        Node(T item, Node *L = nullptr, Node *R = nullptr)
            : data(item), left(L), right(R) {}
        ~Node() {}
    };
    Node *root;

   public:
    BinaryTree() : root(nullptr) {}
    BinaryTree(const T &value) { root = new Node(value); }
    ~BinaryTree() { clear(); }
    void clear() { clear(root); }
    bool isEmpty() const { return root == nullptr; }
    T Root(T flag) const;
    T lchild(T x, T flag) const;
    T rchild(T x, T flag) const;
    void delLeft(T x);
    void delRight(T x);
    void preOrder() const;
    void postOrder() const;
    void midOrder() const;
    void levelOrder() const;
    void createTree(T flag);
    bool isComplete() const;

   private:
    Node *find(T x, Node *t) const;
    void clear(Node *&t);
    void preOrder(Node *t) const;
    void postOrder(Node *t) const;
    void midOrder(Node *t) const;
};

template <class T>
T BinaryTree<T>::Root(T flag) const {
    if (root == nullptr)
        return flag;
    else
        return root->data;
}

template <class T>
void BinaryTree<T>::clear(BinaryTree<T>::Node *&t) {
    if (t == nullptr) return;
    clear(t->left);
    clear(t->right);
    delete t;
    t = nullptr;
}

template <class T>
void BinaryTree<T>::preOrder() const {
    if (root != nullptr) {
        cout << "PreOrder: ";
        preOrder(root);
        cout << endl;
    }
}

template <class T>
void BinaryTree<T>::midOrder() const {
    if (root != nullptr) {
        cout << "MidOrder: ";
        midOrder(root);
        cout << endl;
    }
}

template <class T>
void BinaryTree<T>::postOrder() const {
    if (root != nullptr) {
        cout << "PostOrder: ";
        postOrder(root);
        cout << endl;
    }
}

template <class T>
void BinaryTree<T>::preOrder(BinaryTree<T>::Node *t) const {
    if (t != nullptr) {
        cout << t->data << ' ';
        preOrder(t->left);
        preOrder(t->right);
    }
}

template <class T>
void BinaryTree<T>::midOrder(BinaryTree<T>::Node *t) const {
    if (t != nullptr) {
        midOrder(t->left);
        cout << t->data << ' ';
        midOrder(t->right);
    }
}

template <class T>
void BinaryTree<T>::postOrder(BinaryTree<T>::Node *t) const {
    if (t != nullptr) {
        postOrder(t->left);
        postOrder(t->right);
        cout << t->data << ' ';
    }
}

template <class T>
void BinaryTree<T>::levelOrder() const {
    LinkedQueue<Node *> q;
    Node *tmp;
    cout << "LevelOrder: ";
    q.enQueue(root);

    while (!q.isEmpty()) {
        tmp = q.deQueue();
        cout << tmp->data << ' ';
        if (tmp->left) q.enQueue(tmp->left);
        if (tmp->right) q.enQueue(tmp->right);
    }
    cout << endl;
}

template <class T>
typename BinaryTree<T>::Node *BinaryTree<T>::find(T x,
                                               BinaryTree<T>::Node *t) const {
    Node *tmp;
    if (t == nullptr) return nullptr;
    if (t->data == x) return t;
    if (tmp = find(x, t->left))
        return tmp;
    else
        return find(x, t->right);
}

template <class T>
void BinaryTree<T>::delLeft(T x) {
    Node *tmp = find(x, root);
    if (tmp == nullptr) return;
    clear(tmp->left);
}

template <class T>
void BinaryTree<T>::delRight(T x) {
    Node *tmp = find(x, root);
    if (tmp == nullptr) return;
    clear(tmp->right);
}

template <class T>
T BinaryTree<T>::lchild(T x, T flag) const {
    Node *tmp = find(x, root);
    if (tmp == nullptr || tmp->left == nullptr) return flag;
    return tmp->left->data;
}

template <class T>
T BinaryTree<T>::rchild(T x, T flag) const {
    Node *tmp = find(x, root);
    if (tmp == nullptr || tmp->right == nullptr) return flag;
    return tmp->right->data;
}

template <class T>
void BinaryTree<T>::createTree(T flag) {
    LinkedQueue<Node *> q;
    Node *tmp;
    T x, ldata, rdata;
    cout << "Input the root: ";
    cin >> x;
    root = new Node(x);
    q.enQueue(root);
    while (!q.isEmpty()) {
        tmp = q.deQueue();
        cout << "Input the two sons of " << tmp->data << ", or " << flag
                  << " for null: ";
        cin >> ldata >> rdata;
        if (ldata != flag) q.enQueue(tmp->left = new Node(ldata));
        if (rdata != flag) q.enQueue(tmp->right = new Node(rdata));
    }
    cout << "Create completed!" << endl;
}

template <class T>
bool BinaryTree<T>::isComplete() const {
    LinkedQueue<Node *> q;
    Node *tmp;
    q.enQueue(root);
    bool flag = 0; // found node with degree <= 1
    // level order
    while (!q.isEmpty()) {
        tmp = q.deQueue();
        if (flag) { // rest nodes must be leaves
            if (!tmp->left && !tmp->right) continue;
            else return 0;
        }

        if (tmp->left && tmp->right) // degree = 2
            q.enQueue(tmp->left), q.enQueue(tmp->right);
        else if (!tmp->left && tmp->right) return 0; // no left child
        else if (tmp->left && !tmp->right || !tmp->left && !tmp->right)
            flag = 1; // degree <= 1, rest nodes must be leaves
    }
    return 1;
}
