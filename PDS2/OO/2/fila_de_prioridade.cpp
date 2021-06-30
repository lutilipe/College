#include "fila_de_prioridade.h"

FilaDePrioridade::FilaDePrioridade() {
    primeiro_ = nullptr;
    tamanho_ = 0;
}

string FilaDePrioridade::primeiro() const {
    return primeiro_->nome;
}

int FilaDePrioridade::tamanho() const {
    return tamanho_;
}

bool FilaDePrioridade::vazia() const {
    return tamanho_ <= 0;
}

void FilaDePrioridade::RemoverPrimeiro() {
    if (primeiro_ != nullptr) {
        primeiro_ = primeiro_->next;
        tamanho_--;
    }
}

void FilaDePrioridade::Inserir(int p, string s) {
    No *n = new No(s, p);
    tamanho_++;
    if (primeiro_ == nullptr || n->prioridade > primeiro_->prioridade) {
        n->next = primeiro_;
        primeiro_ = n;
        return;
    } else {
        No *curr = primeiro_;
        while (curr->next != nullptr && curr->next->prioridade >= n->prioridade) {
            curr = curr->next;
        }
        n->next = curr->next;
        curr->next = n;
    }
}
