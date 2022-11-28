#include <iostream>

#include "BinarySearchTree.h"
using namespace std;

int main() {
    BinarySearchTree<int> t;
    cout << "Use following commands:\n"
            "    i x: insert(x)\n"
            "    = x: remove(x)\n"
            "    f x: find(x)\n"
            "    < x: removeSmall(x)\n"
            "    > x: removeGreater(x)\n"
            "    r x y: removeRange(x, y)\n"
            "    p: midOrder()\n"
            "    q: exit\n";
    char op;
    int x;
    while (1) {
        cin >> op;
        switch (op) {
            case 'i':
                cin >> x;
                t.insert(x);
                break;
            case '=':
                cin >> x;
                t.remove(x);
                break;
            case 'f':
                cin >> x;
                cout << (t.find(x) ? "found" : "not found") << endl;
                break;
            case '<':
                cin >> x;
                t.removeSmaller(x);
                break;
            case '>':
                cin >> x;
                t.removeGreater(x);
                break;
            case 'r':
                int y;
                cin >> x >> y;
                t.removeRange(x, y);
                break;
            case 'p':
                t.midOrder();
                cout << endl;
                break;
            default:
                return 0;
        }
    }
}