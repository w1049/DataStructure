#pragma once

#include <iostream>

#include "List.h"

class IndexOutOfBounds {};

template <class T>
class SinglyLinkedList : public List<T> {
   private:
    struct node {
        T data;
        node *next;
        node(const T &x, node *n = NULL) {
            data = x;
            next = n;
        }
        node() : next(NULL) {}
        ~node() {}
    };
    node *head;
    int currentLength;
    node *move(int i) const;

   public:
    SinglyLinkedList();
    ~SinglyLinkedList() {
        clear();
        delete head;
    }
    void clear();
    int length() const { return currentLength; };
    void insert(int i, const T &x);
    void remove(int i);
    int search(const T &x) const;
    T visit(int i) const;
    void traverse() const;
    void reverse();
};

template <class T>
SinglyLinkedList<T>::SinglyLinkedList() {
    head = new node;
    currentLength = 0;
}
template <class T>
typename SinglyLinkedList<T>::node *SinglyLinkedList<T>::move(int i) const {
    node *p = head;
    while (i-- >= 0) p = p->next;
    return p;
}

template <class T>
void SinglyLinkedList<T>::insert(int i, const T &x) {
    if (i < 0 || i > currentLength) throw IndexOutOfBounds();
    node *p = move(i - 1);
    p->next = new node(x, p->next);
    ++currentLength;
}

template <class T>
void SinglyLinkedList<T>::clear() {
    node *p = head->next, *q;
    head->next = NULL;
    while (p) {
        q = p->next;
        delete p;
        p = q;
    }
    currentLength = 0;
}

template <class T>
void SinglyLinkedList<T>::remove(int i) {
    if (i < 0 || i > currentLength - 1) throw IndexOutOfBounds();
    node *p = move(i - 1);
    node *tmp = p->next;
    p->next = tmp->next;
    delete tmp;
    --currentLength;
}

template <class T>
int SinglyLinkedList<T>::search(const T &x) const {
    node *p = head->next;
    int i = 0;
    while (p && p->data != x) {
        p = p->next;
        ++i;
    }
    if (!p)
        return -1;
    else
        return i;
}

template <class T>
T SinglyLinkedList<T>::visit(int i) const {
    if (i < 0 || i > currentLength - 1) throw IndexOutOfBounds();
    node *p = move(i);
    return p->data;
}

template <class T>
void SinglyLinkedList<T>::traverse() const {
    node *p = head->next;
    while (p) {
        std::cout << p->data << ' ';
        p = p->next;
    }
    std::cout << std::endl;
}

template <class T>
void SinglyLinkedList<T>::reverse() {
    node *p = head->next->next, *pre = head->next, *q;
    // pre 为 i=0, p 为 i=1
    pre->next = NULL; // 第一个变成最后一个
    while (p) {
        head->next = p; // p 暂时当第一个
        q = p->next; // 记录下一个
        p->next = pre; // 逆转
        pre = p; // 记录 pre
        p = q; // 遍历下一个
    }
}
