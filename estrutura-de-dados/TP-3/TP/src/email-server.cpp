#include "email-server.h"
#include "email-box.h"
#include "email.h"
#include "msgassert.h"
#include <iostream>

EmailServer::EmailServer(int length) {
    EmailServer::size = length;
    EmailServer::table = new EmailBox[length];
}

EmailServer::~EmailServer() {
    delete[] EmailServer::table;
}

// Funcao de hash. O(1)
int EmailServer::hash(int id) {
    return id % EmailServer::size;
}

// Insere o elemento na arvore correta
// e retorna a posicao da arvore na tabela
int EmailServer::add(Email e) {
    int id = hash(e.getUserId());
    EmailServer::table[id].add(e);
    return id;
}

// Retorna o elemento na arvore ou NULL
Email* EmailServer::get(int userId, int key) {
    int id = hash(userId);
    return EmailServer::table[id].get(userId, key);
}

// Remove o elemento da arvore correspondente e
// retorna se a remocao foi feita com sucesso ou nao
bool EmailServer::remove(int userId, int key) {
    int id = hash(userId);
    return EmailServer::table[id].remove(userId, key);
}

void EmailServer::handleDeliveryMessage(ifstream* in, ofstream* out) {
    int userId = -1, key = -1, msgLength = 0;

    *in >> userId >> key >> msgLength;

    string message = "";
    string tmp = "";

    for (int i = 0; i < msgLength - 1; i++) {
        *in >> tmp;
        message += tmp;
        message += " ";
    }

    *in >> tmp;
    message += tmp;

    Email e(key, userId, message);

    int id = EmailServer::add(e);

    *out << "OK: MENSAGEM " << key;
    *out << " PARA " << userId;
    *out << " ARMAZENADA EM " << id << endl;
}

void EmailServer::handleSearchMessage(ifstream* in, ofstream* out) {
    int userId = -1, key = -1;

    *in >> userId >> key;

    Email* e = EmailServer::get(userId, key);

    *out << "CONSULTA " << userId;
    *out << " " << key;
    *out << ": ";

    if (e != NULL) {
        *out << e->getMessage() << endl;
        return;
    }

    *out << "MENSAGEM INEXISTENTE" << endl;
}

void EmailServer::handleDeleteMessage(ifstream* in, ofstream* out) {
    int userId = -1, key = -1;

    *in >> userId >> key;

    bool deleted = EmailServer::remove(userId, key);

    if (deleted) {
        *out << "OK: MENSAGEM APAGADA" << endl;
        return;
    }

    *out << "ERRO: MENSAGEM INEXISTENTE" << endl;
}

// Lida com os comandos do servidor de emails
void EmailServer::handleCommands(string command, ifstream* in, ofstream* out) {
    erroAssert(command != "", "Invalid command");

    if (command == "ENTREGA") {
        EmailServer::handleDeliveryMessage(in, out);
    } else if (command == "CONSULTA") {
        EmailServer::handleSearchMessage(in, out);
    } else if (command == "APAGA") {
        EmailServer::handleDeleteMessage(in, out);
    } else {
        throw "Invalid command";
    }
}
