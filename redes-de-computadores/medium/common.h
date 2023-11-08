#pragma once

#include <stdlib.h>

#include <arpa/inet.h>

typedef struct BlogOperation {
    int client_id;
    int operation_type;
    int server_response;
    char topic[50];
    char content[2048];
} BlogOperation;

enum OperationType {
    NEW_CONNECTION = 1,
    NEW_POST,
    LIST_TOPICS,
    SUB_TOPIC,
    EXIT,
    UNSUB_TOPIC,
};

void logexit(const char *msg);

int addrparse(const char *addrstr, const char *portstr,
              struct sockaddr_storage *storage);

void addrtostr(const struct sockaddr *addr, char *str, size_t strsize);

int server_sockaddr_init(const char *proto, const char *portstr,
                         struct sockaddr_storage *storage);
int get_message(int socket, BlogOperation* msg);
void send_message(int socket, BlogOperation* msg);
void parseToTwoDigits(int number, char *result);