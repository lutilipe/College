#include "common.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#define BUFSZ 1024
#define MAX_CLIENTS 15

struct client_data {
    int csock;
    struct sockaddr_storage storage;
};

int clients[MAX_CLIENTS] = { 0 };

void handle_exit(int csock, int id) {
    char parsed_id[3];
    parse_to_two_digits(id, parsed_id);
    printf("client %s disconnected\n", parsed_id);
    close(csock);
    pthread_exit(EXIT_SUCCESS);
}

void handle_new_connection(BlogOperation* operation, int csock) {
    int client_id = 0;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] == 0) {
            clients[i] = i + 1;
            client_id = clients[i];
            break;
        }
    }
    char parsed_id[3];
    parse_to_two_digits(client_id, parsed_id);
    printf("client %s connected\n", parsed_id);
    parse_operation_msg(operation, client_id, NEW_CONNECTION, 1, "", "");
    send_message(csock, operation);
}

int handle_action(
    BlogOperation* operation,
    int csock
) {
    switch (operation->operation_type) {
        case NEW_CONNECTION:
            handle_new_connection(operation, csock);
            break;
        case NEW_POST:
            printf("%s\n", operation->topic);
            printf("%s\n", operation->content);
            break;
        case EXIT:
            handle_exit(csock, operation->client_id);
            return 0;
        default:
            return 1;
    }

    return -1;
}

void * handle_client_thread(void *data) {
    struct client_data *cdata = (struct client_data *)data;

    while (1) {
        int handle_result = 1;
        do {
            BlogOperation operation;
            get_message(cdata->csock, &operation);
            handle_result = handle_action(&operation, cdata->csock);
        } while (handle_result == 1);

        if (!handle_result) {
            break;
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 3) {
        exit(EXIT_FAILURE);
    }

    struct sockaddr_storage storage;
    if (0 != server_sockaddr_init(argv[1], argv[2], &storage)) {
        exit(EXIT_FAILURE);
    }

    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if (s == -1) {
        exit(EXIT_FAILURE);
    }

    int enable = 1;
    if (0 != setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))) {
        exit(EXIT_FAILURE);
    }

    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (0 != bind(s, addr, sizeof(storage))) {
        exit(EXIT_FAILURE);
    }

    if (0 != listen(s, 10)) {
        exit(EXIT_FAILURE);
    }

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);

    while (1) {
        struct sockaddr_storage cstorage;
        struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
        socklen_t caddrlen = sizeof(cstorage);

        int csock = accept(s, caddr, &caddrlen);
        if (csock == -1) {
            exit(EXIT_FAILURE);
        }

        struct client_data *cdata = malloc(sizeof(*cdata));
        if (!cdata) {
            exit(EXIT_FAILURE);
        }
        cdata->csock = csock;
        memcpy(&(cdata->storage), &cstorage, sizeof(cstorage));

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client_thread, cdata);
    }

    exit(EXIT_SUCCESS);
}
