#pragma once
#include <cmath>
#include <cstring>
#include <iostream>

template <class T>
class Set {
   private:
    T *data;
    int currentSize;
    int maxSize;
    void doubleSpace();

   public:
    Set(int capacity = 128) {
        data = new T[maxSize = capacity];
        currentSize = 0;
    }
    Set(const Set &s);
    ~Set() { delete[] data; }
    bool insert(T x);
    bool erase(T x);
    bool count(T x) const;
    void print() const;

    Set &operator=(const Set &s);
    Set operator+(const Set &s) const;
    Set operator-(const Set &s) const;
    Set operator*(const Set &s) const;
};

template <class T>
void Set<T>::doubleSpace() {
    T *tmp = data;
    data = new T[maxSize *= 2];
    memcpy(data, tmp, sizeof(T) * currentSize);
    delete[] tmp;
}

template <class T>
Set<T>::Set(const Set<T> &s) {
    data = new T[maxSize = s.maxSize];
    currentSize = s.currentSize;
    memcpy(data, s.data, sizeof(T) * currentSize);
}

template <class T>
Set<T> &Set<T>::operator=(const Set<T> &s) {
    delete[] data;
    data = new T[maxSize = s.maxSize];
    currentSize = s.currentSize;
    memcpy(data, s.data, sizeof(T) * currentSize);
    return *this;
}

template <class T>
bool Set<T>::count(T x) const {
    for (int i = 0; i < currentSize; i++)
        if (data[i] == x) return 1;
    return 0;
}

template <class T>
bool Set<T>::insert(T x) {
    if (count(x)) return 0;
    if (currentSize == maxSize) doubleSpace();
    data[currentSize++] = x;
    return 1;
}

template <class T>
bool Set<T>::erase(T x) {
    for (int i = 0; i < currentSize; i++)
        if (data[i] == x) {
            for (; i < currentSize - 1; i++) data[i] = data[i + 1];
            return 1;
        }
    return 0;
}

template <class T>
void Set<T>::print() const {
    for (int i = 0; i < currentSize; i++) std::cout << data[i] << ' ';
    std::cout << std::endl;
}

template <class T>
Set<T> Set<T>::operator+(const Set<T> &s) const { // Union
    Set<T> result(*this);
    // No need to check, insert() will check
    for (int i = 0; i < s.currentSize; i++) result.insert(s.data[i]);
    return result;
}

template <class T>
Set<T> Set<T>::operator-(const Set<T> &s) const { // Difference
    Set<T> result(currentSize); // no larger than current size
    for (int i = 0; i < currentSize; i++)
        if (!s.count(data[i])) result.insert(data[i]);
    return result;
}

template <class T>
Set<T> Set<T>::operator*(const Set<T> &s) const { // Intersection
    Set<T> result(std::min(currentSize, s.currentSize)); // smaller than any set
    for (int i = 0; i < currentSize; i++)
        if (s.count(data[i])) result.insert(data[i]);
    return result;
}
