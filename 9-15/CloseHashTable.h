#pragma once

template <class T>
class CloseHashTable {
   private:
    struct node {
        T data;
        int state; // 0 empty, 1 using, 2 removed
        node(): state(0) {}
    };
    node *table;
    int size, alive, removed, limit;
    int (*key)(const T &x); // hash function
    static int defaultKey(const int &k) { return k; } // default: hash(k)=k
    void update();
   public:
    CloseHashTable(int = 128, int (*f)(const T &x) = defaultKey, int = 32);
    ~CloseHashTable() { delete[] table; }
    bool find(const T &x) const;
    void insert(const T &x);
    bool remove(const T &x);
    void rehash();
    void p(){
        #include<iostream>
        using namespace std;
        for (int i = 0; i < size; i++) cout << (table[i].state ? table[i].data : 0) << ' ';
    }
};

template <class T>
CloseHashTable<T>::CloseHashTable(int maxSize, int (*f)(const T &x), int deadLimit): alive(0), removed(0) {
    size = maxSize;
    table = new node[size];
    key = f;
    limit = deadLimit;
}

template <class T>
bool CloseHashTable<T>::find(const T &x) const {
    int initPos, pos;
    initPos = pos = key(x) % size;
    do {
        if (table[pos].state == 0)
            return false;
        if (table[pos].state == 1 && table[pos].data == x)
            return true;
        pos = (pos + 1) % size;
    } while (pos != initPos); // equal means failed
    return false;
}

template <class T>
void CloseHashTable<T>::insert(const T &x) {
    int initPos, pos;
    initPos = pos = key(x) % size;
    do {
        if (table[pos].state != 1) {
            table[pos].data = x;
            table[pos].state = 1;
            ++alive;
            update();
            return;
        }
        pos = (pos + 1) % size;
    } while (pos != initPos);
}

template <class T>
bool CloseHashTable<T>::remove(const T &x) {
    int initPos, pos;
    initPos = pos = key(x) % size;
    do {
        if (table[pos].state == 0) return false;  // doesn't exist
        if (table[pos].state == 1 && table[pos].data == x) {
            table[pos].state = 2;
            --alive, ++removed;
            update();
            return true;
        }
        pos = (pos + 1) % size;
    } while (pos != initPos);
    return false;
}

template <class T>
void CloseHashTable<T>::rehash() {
    node *tmp = table;
    table = new node[size];
    alive = removed = 0;
    for (int i = 0; i < size; ++i) {
        if (tmp[i].state == 1)
            insert(tmp[i].data);
    }
    delete[] tmp;
}

template <class T>
void CloseHashTable<T>::update() {
    if (alive > size / 2) {
        size *= 2; // hash() is related to size
        rehash(); // double space changes the size, need rehash
    }
    if (removed > limit) rehash();
}