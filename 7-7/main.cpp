#include <iostream>

#include "PriorityQueue.h"
using namespace std;

int main() {
    cout << "Please enter the size, and then the initial elements in the "
            "queue.\n"
            "For example: 5 3 6 4 1 5\n";
    int n, *data;
    cin >> n;
    data = new int[n];
    for (int i = 0; i < n; i++) cin >> data[i];

    PriorityQueue<int> q(data, n);
    cout << "Now the heap is:\n";
    q.print();

    cout << "Now you can use following command:\n"
            "    e x: enQueue(x)\n"
            "    p: print()\n"
            "    f x: findMin(x)\n"
            "    d i value: decreaseKey(i, value)\n"
            "    q: exit\n";

    char op;
    int x;
    while (1) {
        cin >> op;
        switch (op) {
            case 'e':
                cin >> x;
                q.enQueue(x);
                break;
            case 'p':
                q.print();
                break;
            case 'f':
                cin >> x;
                cout << q.findMin(x) << endl;
                break;
            case 'd':
                int i;
                cin >> i >> x;
                q.decreaseKey(i, x);
                break;
            default:
                return 0;
        }
    }
}