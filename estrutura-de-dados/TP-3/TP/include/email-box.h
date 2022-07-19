#ifndef EMAIL_BOX_H
#define EMAIL_BOX_H

#include <iostream>
#include "email.h"

using namespace std;

#ifndef EMAIL_BOX_ID
#define EMAIL_BOX_ID 0
#endif

class TreeNode {
    private:
        Email val;
        TreeNode *right;
        TreeNode *left;
        friend class EmailBox;
    public:
        TreeNode(Email e) { val = e; right = NULL; left = NULL; };
};

class EmailBox {
    private:
        // Memlog id
        int _id = EMAIL_BOX_ID;

        TreeNode* root;
        void addHelper(TreeNode* &p, Email& val);
        bool removeHelper(TreeNode* &p, int userId, int key);
        void antecessor(TreeNode* p, TreeNode* &r);
        Email* dfs(TreeNode* p, int userId, int key);
        void delHelper(TreeNode* p);

    public:
        EmailBox() { root = NULL; };
        ~EmailBox();
        void add(Email& val);
        Email* get(int userId, int key);
        bool remove(int userId, int key);
        TreeNode* getRoot() { return root; };
};

#endif
