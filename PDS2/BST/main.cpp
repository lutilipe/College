#include <iostream>
#include "BST.hpp"

int main() {
    BST tree;
    tree.insert(9);
    tree.insert(7);
    tree.insert(0);
    tree.insert(5);
    tree.insert(1);
    tree.insert(3);
    tree.insert(8);
    tree.insert(6);
    tree.insert(4);
    tree.insert(2);
    tree.display();
    return 0;
}