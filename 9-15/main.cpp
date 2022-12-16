#include <iostream>

#include "CloseHashTable.h"
using namespace std;

int main() {
    CloseHashTable<int> t(8, [](const int& x) { return x % 7; }, 2);

    cout << "Use following commands:\n"
            "    i x: insert(x)\n"
            "    r x: remove(x)\n"
            "    f x: find(x)\n"
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
            case 'r':
                cin >> x;
                t.remove(x);
                break;
            case 'f':
                cin >> x;
                cout << (t.find(x) ? "found" : "not found") << endl;
                break;
            default:
                return 0;
        }
    }
}