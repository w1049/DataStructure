#pragma once

#include "BinaryTree.h"

template <class T>
class Tree : public BinaryTree<T> {
    typedef typename BinaryTree<T>::Node Node;

   public:
    void createTree(T flag);
    void preOrder() const;
    void postOrder() const;
    void levelOrder() const;
};

template <class T>
void Tree<T>::createTree(T flag) {
    LinkedQueue<Node *> q;
    Node *f, *son;  // father, the last son
    T data;
    cout << "Input the root: ";
    cin >> data;
    BinaryTree<T>::root = new Node(data);
    q.enQueue(BinaryTree<T>::root);
    while (!q.isEmpty()) {
        f = q.deQueue();
        cout << "Input the sons of " << f->data << ", end with " << flag
             << ": ";
        cin >> data;  // the first son
        if (data != flag)
            q.enQueue(f->left = new Node(data));
        else
            continue;
        son = f->left;
        while (cin >> data && data != flag) {  // other sons
            q.enQueue(son->right = new Node(data));
            son = son->right;  // move the "last son" pointer
        }
    }
    cout << "Create completed!" << endl;
}

template <class T>
void Tree<T>::preOrder() const {
    BinaryTree<T>::preOrder();  // same as preOrder of BinaryTree
}

template <class T>
void Tree<T>::postOrder() const {
    if (BinaryTree<T>::root != nullptr) {
        cout << "PostOrder: ";
        BinaryTree<T>::midOrder(BinaryTree<T>::root);
        cout << endl;
    }  // same as midOrder of BinaryTree
}

template <class T>
void Tree<T>::levelOrder() const {
    LinkedQueue<Node *> q;
    Node *p, *tmp;
    cout << "LevelOrder: ";
    q.enQueue(BinaryTree<T>::root);

    while (!q.isEmpty()) {
        p = q.deQueue();
        cout << p->data << ' ';
        if (p->left) {
            q.enQueue(tmp = p->left);  // enQueue itself
            while (tmp->right)         // and all sibilings
                q.enQueue(tmp = tmp->right);
        }
    }
    cout << endl;
}