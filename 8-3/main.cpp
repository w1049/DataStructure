#include <iostream>

#include "Set.h"
using namespace std;

int main() {
    cout << "Please enter the Set A and B, first the size then the elements:"
         << endl;
    int na, nb;
    Set<int> A(na), B(nb);
    cin >> na;
    for (int i = 1, x; i <= na; i++) cin >> x, A.insert(x);
    cin >> nb;
    for (int i = 1, x; i <= nb; i++) cin >> x, B.insert(x);

    cout << "A = ";
    A.print();
    cout << "A = ";
    B.print();

    cout << "A + B = ";
    (A + B).print();

    cout << "A - B = ";
    (A - B).print();

    cout << "A * B = ";
    (A * B).print();
}