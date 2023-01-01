#include <iostream>

#include "Graph.h"
using namespace std;

int main() {
    cout << "Enter n, the total number of vertices, which will be numbered 1 to n: " << endl;
    int n, m;
    cin >> n;
    int *d = new int[n];
    for (int i = 0; i < n; i++) d[i] = i + 1;
    Graph<int, int> G(n, d);
    cout << "Enter m, the number of edges: " << endl;
    cin >> m;
    cout << "Enter " << m << " edges, \"A B\" means A -> B: " << endl;
    for (int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        G.insert(a - 1, b - 1, i);
    }
    int s, M;
    cout << "Enter start and M: " << endl;
    cin >> s >> M;
    G.find(s, M);
}