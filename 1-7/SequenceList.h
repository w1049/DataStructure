#pragma once

#include <iostream>

#include "List.h"

class IllegalSize {};
class IndexOutOfBounds {};

template <class T>
class SequenceList : public List<T> {
   private:
    T *data;
    int currentLength;
    int maxSize;
    void doubleSpace();

   public:
    SequenceList(int initSize = 10);
    ~SequenceList() { delete[] data; }
    void clear() { currentLength = 0; }
    int length() const { return currentLength; };
    void insert(int i, const T &x);
    void remove(int i);
    int search(const T &x) const;
    T visit(int i) const;
    void traverse() const;
    SequenceList<T> operator+(const SequenceList<T> &b) const;
};

template <class T>
SequenceList<T>::SequenceList(int initSize) {
    if (initSize <= 0) throw IllegalSize();
    data = new T[initSize];
    maxSize = initSize;
    currentLength = 0;
}

template <class T>
void SequenceList<T>::insert(int i, const T &x) {
    if (i < 0 || i > currentLength) throw IndexOutOfBounds();
    if (currentLength == maxSize) doubleSpace();
    for (int j = currentLength; j > i; j--) data[j] = data[j - 1];
    data[i] = x;
    ++currentLength;
}

template <class T>
void SequenceList<T>::doubleSpace() {
    T *tmp = data;
    data = new T[maxSize *= 2];
    for (int i = 0; i < currentLength; i++) data[i] = tmp[i];
    delete[] tmp;
}

template <class T>
void SequenceList<T>::remove(int i) {
    if (i < 0 || i > currentLength - 1) throw IndexOutOfBounds();
    for (int j = i; j < currentLength - 1; j++) data[j] = data[j + 1];
    --currentLength;
}

template <class T>
int SequenceList<T>::search(const T &x) const {
    for (int i = 0; i < currentLength; i++)
        if (data[i] == x) return i;
    return -1;
}

template <class T>
T SequenceList<T>::visit(int i) const {
    if (i < 0 || i > currentLength - 1) throw IndexOutOfBounds();
    return data[i];
}

template <class T>
void SequenceList<T>::traverse() const {
    for (int i = 0; i < currentLength; i++) std::cout << data[i] << ' ';
    std::cout << std::endl;
}

template <class T>
SequenceList<T> SequenceList<T>::operator+(const SequenceList<T> &b) const {
    // 初始化大小足够的新表
    SequenceList<T> c = SequenceList<T>(length() + b.length());

    // 从两个表中复制数据
    memcpy(c.data, data, sizeof(T) * length());
    memcpy(c.data + length(), b.data, sizeof(T) * b.length());
    
    // 更新元素数量
    c.currentLength = length() + b.length();
    return c;
}
