#include <iostream>
using std::cout;
using std::endl;

template <class VT, class ET>
class Graph {
   public:
    Graph(int vSize, const VT d[]);
    bool insert(int u, int v, ET w);
    bool remove(int u, int v);
    bool exist(int u, int v) const;
    void find(int start, int M) const;
    ~Graph();

   protected:
    int Vers, Edges;

   private:
    struct edgeNode {
        int end;
        ET weight;
        edgeNode *next;
        edgeNode(int e, ET w, edgeNode *n = nullptr) {
            end = e;
            weight = w;
            next = n;
        }
    };
    struct verNode {
        VT ver;
        edgeNode *head;
        verNode(edgeNode *h = nullptr) { head = h; }
    };
    verNode *verList;
    void find(int start, int M, int* v, int *stack, int &top) const;
};

template <class VT, class ET>
Graph<VT, ET>::Graph(int vSize, const VT d[]) {
    Vers = vSize;
    Edges = 0;
    verList = new verNode[vSize];
    for (int i = 0; i < Vers; ++i) verList[i].ver = d[i];
}

template <class VT, class ET>
Graph<VT, ET>::~Graph() {
    int i;
    edgeNode *p;
    for (i = 0; i < Vers; ++i)
        while ((p = verList[i].head) != nullptr) {
            verList[i].head = p->next;
            delete p;
        }
    delete[] verList;
}

template <class VT, class ET>
bool Graph<VT, ET>::insert(int u, int v, ET w) {
    verList[u].head = new edgeNode(v, w, verList[u].head);

    ++Edges;
    return 1;
}

template <class VT, class ET>
bool Graph<VT, ET>::remove(int u, int v) {
    edgeNode *p = verList[u].head, *q;
    if (p == nullptr) return 0;
    if (p->end == v) {
        verList[u].head = p->next;
        delete p;
        --Edges;
        return 1;
    }
    while (p->next != nullptr && p->next->end != v) p = p->next;
    if (p->next == nullptr) return 0;
    q = p->next;
    p->next = q->next;
    delete q;
    --Edges;
    return 1;
}

template <class VT, class ET>
bool Graph<VT, ET>::exist(int u, int v) const {
    edgeNode *p = verList[u].head;
    while (p != nullptr && p->end != v) p = p->next;
    if (p == nullptr)
        return 0;
    else
        return 1;
}

template <class VT, class ET>
void Graph<VT, ET>::find(int start, int M) const {
    int u = -1;
    for (int i = 0; i < Vers; i++)
        if (verList[i].ver == start) { u = i; break; }
    if (u == -1) return; // no such start

    int *v = new int[Vers](), *stack = new int[M + 1], top = 0;
    find(u, M, v, stack, top);
    delete []v;
    delete []stack;
}

template <class VT, class ET>
void Graph<VT, ET>::find(int u, int M, int* v, int *stack, int &top) const {
    // cout << "find" << u << endl;
    if (top == M) { // found
        for (int i = 0; i < top; i++)
            cout << verList[stack[i]].ver << " ";
        cout << verList[u].ver << endl;
        return;
    }
    edgeNode *p = verList[u].head;
    v[u] = 1;
    stack[top++] = u; // save path

    while (p) {
        if (!v[p->end]) find(p->end, M, v, stack, top); // dfs
        p = p->next;
    }

    v[u] = 0; // recover
    --top;

}