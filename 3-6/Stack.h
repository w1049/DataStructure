#pragma once

template <class T>
class Stack {
   public:
    virtual bool isEmpty() const = 0;
    virtual void push(const T &x) = 0;
    virtual T pop() = 0;
    virtual T top() const = 0;
    virtual ~Stack() {}
};
