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
        void addHelper(TreeNode* &p, Email val);
        bool removeHelper(TreeNode* &p, Email val);
        void antecessor(TreeNode* p, TreeNode* &r);
        bool dfs(TreeNode* p, Email val);
        void delHelper(TreeNode* p);

    public:
        EmailBox() { root = NULL; };
        ~EmailBox();
        void add(Email val);
        bool has(Email val);
        bool remove(Email val);
        TreeNode* getRoot() { return root; };
};

#endif
