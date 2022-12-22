#include <iostream>
using namespace std;

// Sort a[l, r]
template <class T>
void sort(T a[], int l, int r) {
    if (l >= r) return;
    T key = a[l];
    int i = l, j = r;
    do {
        while (i < j && a[j] >= key) --j; // find a[j] that < key
        if (i < j) a[i] = a[j], ++i; // put it on the left

        while (i < j && a[i] <= key) ++i; // find a[i] that > key
        if (i < j) a[j] = a[i], --j; // put it on the right
    } while (i < j);
    a[i] = key;
    sort(a, l, i - 1);
    sort(a, i + 1, r);
}

// Delete duplicate from sorted a[0, size]
// return remaining size
template <class T>
int unique(T a[], int size) {
    int j = 0;
    for (int i = 1; i < size; i++)
        if (a[i] != a[j]) a[++j] = a[i];
    return j + 1;
}

int main() {
    cout << "Please enter the size of array, then enter each element of the array:" << endl;
    int n;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a, 0, n - 1);
    n = unique(a, n);

    cout << n << " unique element(s) in the array:" << endl;
    for (int i = 0; i < n; i++) cout << a[i] << " ";
}