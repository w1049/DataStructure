#include <iostream>

#include "SinglyLinkedList.h"
using namespace std;

int main() {
    int n;
    cout << "Please enter the size of A, then enter each element of A:\n";
    cin >> n;
    SinglyLinkedList<int> A;
    for (int i = 0, tmp; i < n; i++) {
        cin >> tmp;
        A.insert(i, tmp);
    }

    A.reverse();
    cout << "Reversed A:\n";
    A.traverse();
}
