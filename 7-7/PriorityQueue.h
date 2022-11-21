#pragma once
#include <cmath>
#include <iostream>

template <class T>
class PriorityQueue {
   private:
    T *data;
    int currentSize;
    int maxSize;
    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);
    void findMin(T x, int p, int &result, bool &found);

   public:
    PriorityQueue(int capacity = 128) {
        data = new T[capacity];
        maxSize = capacity;
        currentSize = 0;
    }
    PriorityQueue(const T items[], int size);
    ~PriorityQueue() { delete[] data; }
    bool isEmpty() const { return currentSize == 0; }
    void enQueue(const T &x);
    T deQueue();
    T getHead() { return data[1]; }
    int findMin(T x);
    void decreaseKey(int p, T value);
    void print();
};

template <class T>
void PriorityQueue<T>::doubleSpace() {
    T *tmp = data;
    data = new T[maxSize *= 2];
    for (int i = 0; i < currentSize; i++) data[i] = tmp[i];
    delete[] tmp;
}

template <class T>
void PriorityQueue<T>::percolateDown(int hole) {
    int child;
    T tmp = data[hole];
    for (; hole * 2 <= currentSize; hole = child) {
        child = hole * 2;
        if (child + 1 <= currentSize && data[child + 1] < data[child]) child++;
        if (data[child] < tmp)
            data[hole] = data[child];
        else
            break;
    }
    data[hole] = tmp;
}

template <class T>
void PriorityQueue<T>::buildHeap() {
    for (int i = currentSize / 2; i > 0; i--) percolateDown(i);
}

template <class T>
PriorityQueue<T>::PriorityQueue(const T *items, int n)
    : currentSize(n), maxSize(1 << int(log2(n)) + 1) {
    data = new T[maxSize];
    for (int i = 0; i < n; i++) data[i + 1] = items[i];
    buildHeap();
}

template <class T>
void PriorityQueue<T>::enQueue(const T &x) {
    if (currentSize == maxSize - 1) doubleSpace();
    int hole = ++currentSize;
    for (; hole > 1 && x < data[hole / 2]; hole /= 2)
        data[hole] = data[hole / 2];
    data[hole] = x;
}

template <class T>
T PriorityQueue<T>::deQueue() {
    T head = data[1];
    data[1] = data[currentSize--];
    percolateDown(1);
    return head;
}

template <class T>
void PriorityQueue<T>::findMin(T x, int p, int &result, bool &found) {
    if (found) return;
    if (data[p] >= x) {
        if (result == -1)
            result = p;
        else if (data[p] < data[result])
            result = p;
        if (data[p] == x) found = 1;  // if x exists, it must be the result
    }
    if (p * 2 <= currentSize) findMin(x, p * 2, result, found);
    if (p * 2 + 1 <= currentSize) findMin(x, p * 2 + 1, result, found);
}

template <class T>
int PriorityQueue<T>::findMin(T x) {
    int result = -1;
    bool found = 0;
    findMin(x, 1, result, found);  // O(n)
    return result;
}

template <class T>
void PriorityQueue<T>::decreaseKey(int p, T value) {
    T x = data[p] - value;  // percolate up
    for (; p > 1 && x < data[p / 2]; p /= 2) data[p] = data[p / 2];
    data[p] = x;
}

template <class T>
void PriorityQueue<T>::print() {
    for (int i = 1; i <= currentSize; i++) std::cout << data[i] << " ";
    std::cout << std::endl;
}