#include <iostream>

#include "SequenceList.h"
using namespace std;

int main() {
    int na, nb;
    cout << "Please enter the size of A, then enter each element of A:\n";
    cin >> na;
    SequenceList<int> A(na);
    for (int i = 0, tmp; i < na; i++) {
        cin >> tmp;
        A.insert(i, tmp);
    }

    cout << "Please enter the size of B, then enter each element of B:\n";
    cin >> nb;
    SequenceList<int> B(nb);
    for (int i = 0, tmp; i < nb; i++) {
        cin >> tmp;
        B.insert(i, tmp);
    }

    cout << "A concat B:\n";
    SequenceList<int> C = A + B;
    C.traverse();
}
