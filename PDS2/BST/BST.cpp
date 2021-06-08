#include <iostream>
#include "BST.hpp"

using namespace std;

Node* createNode(int val) {
    Node *n = new Node;
    n->data = val;
    n->dir = nullptr;
    n->esq = nullptr;

    return n;
}

void insertHelper(Node *root, int val) {
    if (val > root->data) {
        if (root->dir == nullptr) {
            root->dir = createNode(val);
        } else {
            insertHelper(root->dir, val);
        }
    } else if (val < root->data) {
        if (root->esq == nullptr) {
            root->esq = createNode(val);
        } else {
            insertHelper(root->esq, val);
        }
    }
    return;
}

void BST::insert(int val) {
    if (root == nullptr) {
        root = createNode(val);
    } else {
        insertHelper(root, val);
    }
}

void inorder(Node *n) {
    if (n == nullptr) return;

    inorder(n->esq);
    cout << n->data << " ";
    inorder(n->dir);
}

void BST::display() {
    inorder(root);
    cout << endl;
}