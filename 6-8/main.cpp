#include <iostream>

#include "Tree.h"
using namespace std;

int main() {
    Tree<int> tree;
    tree.createTree(0);
    tree.preOrder();
    tree.postOrder();
    tree.levelOrder();
}