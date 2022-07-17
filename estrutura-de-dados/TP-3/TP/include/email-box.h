#ifndef EMAIL_BOX_H
#define EMAIL_BOX_H

#include <iostream>
#include "email.h"

using namespace std;

class TreeNode {
    public:
        TreeNode() { right = NULL; left = NULL; };
    private:
        Email val;
        TreeNode *right;
        TreeNode *left;
        friend class EmailBox;
};

class EmailBox {
    private:
        TreeNode* root;
        void addHelper(TreeNode* &p, Email& val);
        bool removeHelper(TreeNode* &p, int key);
        void antecessor(TreeNode* p, TreeNode* &r);
        Email* dfs(TreeNode* p, int key);
        void delHelper(TreeNode* p);

    public:
        EmailBox() { root = NULL; };
        ~EmailBox();
        void add(Email& val);
        Email* get(int key);
        bool remove(int key);
        TreeNode* getRoot() { return root; };
};

#endif