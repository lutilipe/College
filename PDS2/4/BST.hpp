#ifndef BST_H
#define BST_H

#include "Aluno.hpp"

struct Node {
    Aluno   *aluno;
    Node    *dir;
    Node    *esq;
};

struct BST {
    Node *root = nullptr;

    BST();
    void inserir_aluno(Aluno aluno);
    void imprimir_arvore();
    Aluno* procurar_aluno(int matricula);
};

#endif