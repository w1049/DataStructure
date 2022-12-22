#include <iostream>
using namespace std;

#include "PriorityQueue.h"

template<class T>
T func1(T a[], int size, int k) { // N + klogN
    // Push all elements into a heap, then discard the largest k elements

    for (int i = 0; i < size; i++) a[i] = -a[i];

    PriorityQueue<T> q(a, size);
    T result;
    for (int i = 0; i < k; i++) result = q.deQueue();

    for (int i = 0; i < size; i++) a[i] = -a[i];
    return -result;
}

template<class T>
T func2(T a[], int size, int k) { // Nlogk
    // Build a heap with the largest k elements

    PriorityQueue<T> q(a, k); // push the first k elements
    for (int i = k; i < size; i++) { // try to push the else
        if (q.getHead() < a[i])
            q.deQueue(), q.enQueue(a[i]);
    }
    // Now the largest k elements are in the heap

    return q.getHead();
}

int main() {
    cout << "Please enter the size of array, then enter each element of the array:" << endl;
    int n;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++) cin >> a[i];

    cout << "Enter k:" << endl;
    int k;
    cin >> k;

    cout << "Method 1: " << func1(a, n, k) << endl;
    cout << "Method 2: " << func2(a, n, k) << endl;
}