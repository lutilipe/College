#include "email.h"
#include "email-box.h"
#include <iostream>

using namespace std;

void EmailBox::delHelper(TreeNode *p){
    if(p != NULL){
        EmailBox::delHelper(p->left);
        EmailBox::delHelper(p->right);
        delete p;
    }
}

EmailBox::~EmailBox() {
    EmailBox::delHelper(root);
    EmailBox::root = NULL;
}

void EmailBox::addHelper(TreeNode* &p, Email& val) {
    if (p == NULL) {
        p = new TreeNode();
        p->val = val;
    } else {
        if (val > p->val) {
            EmailBox::addHelper(p->right, val);
        } else {
            EmailBox::addHelper(p->left, val);
        }
    }
}

void EmailBox::add(Email& val) {
    EmailBox::addHelper(root, val);
}

Email* EmailBox::dfs(TreeNode* p, int userId, int key) {
    if (p == NULL) {
        return NULL;
    }

    if (key > p->val.getKey()) {
        return EmailBox::dfs(p->right, userId, key);
    } else if (key < p->val.getKey()) {
        return EmailBox::dfs(p->left, userId, key);
    }

    if (userId == p->val.getUserId()) {
        return &(p->val);
    }

    return NULL;
}

Email* EmailBox::get(int userId, int key) {
    return EmailBox::dfs(root, userId, key);
}

void EmailBox::antecessor(TreeNode* p, TreeNode* &r) {
    if (r->right != NULL) {
        return antecessor(p, r->right);
    }

    p->val = r->val;
    p = r;
    r = r->left;

    delete p;
}

bool EmailBox::removeHelper(TreeNode* &p, int userId, int key) {
    if (p == NULL) {
        return false;
    }

    if (key > p->val.getKey()) {
        return EmailBox::removeHelper(p->right, userId, key);
    } else if (key < p->val.getKey()) {
        return EmailBox::removeHelper(p->left, userId, key); 
    }

    if (userId != p->val.getUserId()) {
        return false;
    }

    TreeNode* aux;

    if (p->right == NULL) {
        aux = p;
        p = p->left;
        delete aux;
    } else if (p->left == NULL) {
        aux = p;
        p = p->right;
        delete aux;
    } else {
        EmailBox::antecessor(p, p->left);
    }

    return true;
}

bool EmailBox::remove(int userId, int key) {
    return EmailBox::removeHelper(root, userId, key);
}
