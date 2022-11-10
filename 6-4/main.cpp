#include <iostream>

#include "BinaryTree.h"
using namespace std;

int main() {
    BinaryTree<int> tree;
    tree.createTree(0);
    tree.levelOrder();
    if (tree.isComplete())
        cout << "Congratulations! Valid Complete Binary Tree." << endl;
    else cout << "ERROR: NOT a Complete Binary Tree." << endl;
}