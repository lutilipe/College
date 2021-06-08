#include <iostream>
#include "BST.hpp"

using namespace std;

BST::BST() {};

Node* createNode(Aluno aluno) {
    Node *n = new Node;
    n->aluno = new Aluno(aluno.getMatricula(), aluno.getNome());
    n->dir = nullptr;
    n->esq = nullptr;

    return n;
}

void insertHelper(Node *root, Aluno aluno) {
    if (aluno.getMatricula() > root->aluno->getMatricula()) {
        if (root->dir == nullptr) {
            root->dir = createNode(aluno);
        } else {
            insertHelper(root->dir, aluno);
        }
    } else if (aluno.getMatricula() < root->aluno->getMatricula()) {
        if (root->esq == nullptr) {
            root->esq = createNode(aluno);
        } else {
            insertHelper(root->esq, aluno);
        }
    }
    return;
}

void BST::inserir_aluno(Aluno aluno) {
    if (root == nullptr) {
        root = createNode(aluno);
    } else {
        insertHelper(root, aluno);
    }
}

void inorder(Node *n) {
    if (n == nullptr) return;
    inorder(n->esq);
    n->aluno->imprimir_dados();
    inorder(n->dir);
}

void BST::imprimir_arvore() {
    inorder(root);
}

Aluno* searchHelper(Node *n, int matricula) {
    Aluno *temp;
    if (n == nullptr) return nullptr;
    else if (n->aluno->getMatricula() == matricula) {
        return n->aluno;
    } else if (matricula > n->aluno->getMatricula()) {
        temp = searchHelper(n->dir, matricula);
        return temp;
    } else if (matricula < n->aluno->getMatricula()) {
        temp = searchHelper(n->esq, matricula);
        return temp;
    }
    return nullptr;
} 

Aluno* BST::procurar_aluno(int matricula) {
    if (root == nullptr) return nullptr;
    return searchHelper(root, matricula);
}
