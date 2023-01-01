#include <iostream>

#include "SinglyLinkedList.h"
using namespace std;

int dfs(int u, SinglyLinkedList<int> *G, int* d) {
    if (d[u]) return d[u]; // memoization
    int len = G[u].length();
    if (len == 0) return d[u] = 1; // no prerequisite
    for (int i = 0; i < len; i++)
        d[u] = max(d[u], dfs(G[u].visit(i), G, d)); // find longest
    return ++d[u]; // dont forget to add 1 for itself
}

int main() {
    /* Example input:
        7
        9
        1 2
        1 3
        2 4
        2 5
        2 6
        3 5
        3 7
        5 7
        6 7
     */
    cout << "Enter n, the total number of courses, which will be numbered 1 to n: " << endl;
    int n, m;
    cin >> n;
    SinglyLinkedList<int> *G = new SinglyLinkedList<int>[n]; // saving graph
    cout << "Enter m, the number of course relationships: " << endl;
    cin >> m;
    cout << "Enter " << m << " courses relationships, \"A B\" means A is before B: " << endl;
    for (int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        G[b - 1].insert(a - 1);
        // reverse every edge for dfs
    }
    
    int *d = new int[n](); // max depth
    for (int i = 0; i < n; i++)
        if (!d[i]) dfs(i, G, d); // calculate d for every vertex
    
    int maxd = 0;
    for (int i = 0; i < n; i++)
        maxd = max(maxd, d[i]);
    cout << "It will take you " << maxd << " semesters to complete all courses." << endl;
    
    SinglyLinkedList<int> *sem = new SinglyLinkedList<int>[maxd];
    for (int i = 0; i < n; i++)
        sem[d[i] - 1].insert(i + 1);
    
    for (int i = 0; i < maxd; i++) {
        cout << "Semester " << i + 1 << ": ";
        sem[i].traverse();
    }
}