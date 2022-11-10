#pragma once

template <class T>
class Queue {
   public:
    virtual bool isEmpty() const = 0;
    virtual void enQueue(const T &x) = 0;
    virtual T deQueue() = 0;
    virtual T getHead() const = 0;
    virtual ~Queue() {}
};