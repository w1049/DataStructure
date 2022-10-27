#include <iostream>

#include "LinkedStack.h"
using namespace std;

struct Pair {
    int number;
    int m, n;
    int status;
    // 0: a number
    // 1: calculate A(m, n), save in number
    //    or: A(m, ?) wait for the next number
};

int A(int m, int n) {
    if (m == 0) return n + 1;
    if (n == 0) return A(m - 1, 1);
    return A(m - 1, A(m, n - 1));
}

int a(int m, int n) {
    LinkedStack<Pair> s;
    s.push({0, m, n, 1});
    int tmp;
    while (!s.isEmpty()) {
        Pair p = s.pop();
        switch (p.status) {
            case 0:
                tmp = p.number;
                if (s.isEmpty())
                    return tmp;
                else {
                    p = s.pop();
                    p.n = tmp, p.status = 1;
                    s.push(p);
                }
                break;
            case 1:
                if (p.m == 0) {
                    s.push({p.n + 1, 0, 0, 0});
                    break;
                }
                if (p.n == 0) {
                    s.push({0, p.m - 1, 1, 1});
                    break;
                }
                s.push({0, p.m - 1, 0, 2});
                s.push({0, p.m, p.n - 1, 1});
                break;
        }
    }
    return 0;
}

int main() {
    int m, n;

    cout << "Calculate Ackerman(m, n). Please enter m and n:" << endl;
    cin >> m >> n;
    cout << "Use two methods to calculate. Please wait..." << endl;
    cout << A(m, n) << "." << endl;
    cout << a(m, n) << "." << endl;
}