#pragma once

#include "Queue.h"

class NoSuchElement {};

template <class T>
class LinkedQueue : public Queue<T> {
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
    node *front, *rear;

   public:
    LinkedQueue() { front = rear = nullptr; }
    ~LinkedQueue();
    bool isEmpty() const { return front == nullptr; }
    void enQueue(const T &x);
    T deQueue();
    T getHead() const;
    void clear();
};

template <class T>
void LinkedQueue<T>::enQueue(const T &x) {
    if (rear == nullptr)
        front = rear = new node(x);
    else {
        rear->next = new node(x);
        rear = rear->next;
    }
}

template <class T>
T LinkedQueue<T>::deQueue() {
    if (front == nullptr) throw NoSuchElement();
    node *tmp = front;
    T value = tmp->data;
    front = front->next;
    if (front == nullptr) rear = nullptr;
    delete tmp;
    return value;
}

template <class T>
T LinkedQueue<T>::getHead() const {
    if (front == nullptr) throw NoSuchElement();
    return front->data;
}

template <class T>
void LinkedQueue<T>::clear() {
    node *tmp;
    while (front != nullptr) {
        tmp = front;
        front = front->next;
        delete tmp;
    }
    rear = nullptr;
}

template <class T>
LinkedQueue<T>::~LinkedQueue() {
    clear();
}
