#pragma once

#include "Stack.h"

class NoSuchElement {};

template <class T>
class LinkedStack : public Stack<T> {
   private:
    struct node {
        T data;
        node *next;
        node(const T &x, node *n = nullptr) {
            data = x;
            next = n;
        }
        node() : next(nullptr) {}
        ~node() {}
    };
    node *topElem;

   public:
    LinkedStack() { topElem = nullptr; }
    ~LinkedStack();
    bool isEmpty() const { return topElem == nullptr; }
    void push(const T &x);
    T pop();
    T top() const;
    void clear();
};

template <class T>
void LinkedStack<T>::push(const T &x) {
    node *tmp = new node(x, topElem);
    topElem = tmp;
}

template <class T>
T LinkedStack<T>::pop() {
    if (topElem == nullptr) throw NoSuchElement();
    node *tmp = topElem;
    T value = tmp->data;
    topElem = topElem->next;
    delete tmp;
    return value;
}

template <class T>
T LinkedStack<T>::top() const {
    if (topElem == nullptr) throw NoSuchElement();
    return topElem->data;
}

template <class T>
void LinkedStack<T>::clear() {
    node *tmp;
    while (topElem != nullptr) {
        tmp = topElem;
        topElem = topElem->next;
        delete tmp;
    }
}

template <class T>
LinkedStack<T>::~LinkedStack() {
    clear();
}
