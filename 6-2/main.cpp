#include <iostream>

#include "BinaryTree.h"
using namespace std;

int main() {
    BinaryTree<int> tree;
    tree.createTree(0);
    tree.levelOrder();
    cout << "Number of 2-dgree nodes: ";
    cout << tree.count2Degree() << endl;
}