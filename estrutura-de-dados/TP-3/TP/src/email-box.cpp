#include "email.h"
#include "email-box.h"
#include <iostream>
#include "memlog.h"

using namespace std;

// Deleta todos elementos da arvore
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

// Funcao auxiliar para procurar a folha na qual
// sera inserido o novo valor
void EmailBox::addHelper(TreeNode* &p, Email& val) {
    if (p == NULL) {
        p = new TreeNode(val);
        ESCREVEMEMLOG((long int)(&(p)),sizeof(p),EmailBox::_id);
    } else {
        LEMEMLOG((long int)(&(p)),sizeof(p),EmailBox::_id);
        if (val.getKey() > p->val.getKey()) {
            EmailBox::addHelper(p->right, val);
        } else {
            EmailBox::addHelper(p->left, val);
        }
    }
}

void EmailBox::add(Email& val) {
    EmailBox::addHelper(root, val);
}

// Busca em profundidade
// O match e' feito comparando o id do usuario e a key
Email* EmailBox::dfs(TreeNode* p, int userId, int key) {
    if (p == NULL) {
        return NULL;
    }
    
    LEMEMLOG((long int)(p),sizeof(p),EmailBox::_id);

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

// Localiza o maior elemento (X) no ramo da esquerda do no
// a ser deletado e substitui esse no por X.
void EmailBox::antecessor(TreeNode* p, TreeNode* &r) {
    if (r->right != NULL) {
        LEMEMLOG((long int)(&(r->right)),sizeof(r->right),EmailBox::_id);
        return antecessor(p, r->right);
    }

    p->val = r->val;
    LEMEMLOG((long int)(&(r)),sizeof(r),EmailBox::_id);
    p = r;
    ESCREVEMEMLOG((long int)(&(p)),sizeof(p),EmailBox::_id);
    r = r->left;
    ESCREVEMEMLOG((long int)(&(r)),sizeof(r),EmailBox::_id);

    delete p;
}

// Funcao recursiva auxiliar para buscar o elemento e remove-lo
// da arvore. O match e' feito comparando o id do usuario e a key
bool EmailBox::removeHelper(TreeNode* &p, int userId, int key) {
    if (p == NULL) {
        return false;
    }

    LEMEMLOG((long int)(&(p)),sizeof(p),EmailBox::_id);

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
        LEMEMLOG((long int)(&(p)),sizeof(p),EmailBox::_id);
        aux = p;
        ESCREVEMEMLOG((long int)(&(p)),sizeof(p),EmailBox::_id);
        LEMEMLOG((long int)(&(p->left)),sizeof(p->left),EmailBox::_id);
        p = p->left;
        delete aux;
    } else if (p->left == NULL) {
        LEMEMLOG((long int)(&(p)),sizeof(p),EmailBox::_id);
        aux = p;
        ESCREVEMEMLOG((long int)(&(p)),sizeof(p),EmailBox::_id);
        LEMEMLOG((long int)(&(p->right)),sizeof(p->right),EmailBox::_id);
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
