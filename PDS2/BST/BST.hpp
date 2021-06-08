#ifndef BST_H
#define BST_H

struct Node {
    int     data;
    Node    *dir;
    Node    *esq;
};

struct BST {
    Node *root = nullptr;

    void insert(int val);
    void display();
};

#endif