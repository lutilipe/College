#include "common.h"
#include "hashtable.h"

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
struct Map topics;
struct Map subscriptions;

void handle_exit(BlogOperation* operation, int csock) {
    char parsed_id[3];
    parse_to_two_digits(operation->client_id, parsed_id);
    printf("client %s disconnected\n", parsed_id);
    clients[operation->client_id - 1] = 0;
    parse_operation_msg(operation, operation->client_id, EXIT, 1, "", "");
    send_message(csock, operation);

    char csock_string[50];
    sprintf(csock_string, "%d", csock);
    remove_value_from_all(&subscriptions, csock_string);

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

void handle_new_post(BlogOperation* operation, int csock) {
    insert_pair(&topics, operation->topic, operation->content);

    char csock_string[50];
    sprintf(csock_string, "%d", csock);

    char parsed_id[3];
    parse_to_two_digits(operation->client_id, parsed_id);
    printf("new post added in %s by %s\n", operation->topic, parsed_id);

    char** clients_subscribed_in_topic = get_values(&subscriptions, operation->topic);
    if (clients_subscribed_in_topic != NULL) {
        int count = 0;
        while (clients_subscribed_in_topic[count] != NULL) {
            parse_operation_msg(operation, operation->client_id, NEW_POST, 1, operation->topic, operation->content);
            send_message(atoi(clients_subscribed_in_topic[count]), operation);
            count++;
        }
    }
}

void handle_subscription(BlogOperation* operation, int csock) {
    char csock_string[50];
    sprintf(csock_string, "%d", csock);
    if (has_key(&subscriptions, operation->topic) && has_value(&subscriptions, operation->topic, csock_string)) {
        parse_operation_msg(operation, operation->client_id, SUB_TOPIC, 1, "", "error: already subscribed");
        send_message(csock, operation);
        return;
    }

    if (!has_key(&topics, operation->topic)) {
        insert_pair(&topics, operation->topic, "");
    }

    insert_pair(&subscriptions, operation->topic, csock_string);

    char parsed_id[3];
    parse_to_two_digits(operation->client_id, parsed_id);
    printf("client %s subscribed to %s\n", parsed_id, operation->topic);
}

void handle_unsubscription(BlogOperation* operation, int csock) {
    char csock_string[50];
    sprintf(csock_string, "%d", csock);
    remove_value(&subscriptions, operation->topic, csock_string);

    char parsed_id[3];
    parse_to_two_digits(operation->client_id, parsed_id);
    printf("client %s unsubscribed to %s\n", parsed_id, operation->topic);
}

void handle_list_topics(BlogOperation* operation, int csock) {
    char** list = list_keys(&topics);
    int count = 0;
    char res[sizeof(operation->content)] = "";
    if (list != NULL) {
        while (list[count] != NULL) {
            if (count > 0) {
                strcat(res, ";");
            }
            strcat(res, list[count]);
            count++;
        }
    }

    if (count == 0) {
        parse_operation_msg(operation, operation->client_id, LIST_TOPICS, 1, "", "no topics available");
        send_message(csock, operation);
        return;
    }

    parse_operation_msg(operation, operation->client_id, LIST_TOPICS, 1, "", res);
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
            handle_new_post(operation, csock);
            break;
        case SUB_TOPIC:
            handle_subscription(operation, csock);
            break;
        case UNSUB_TOPIC:
            handle_unsubscription(operation, csock);
            break;
        case LIST_TOPICS:
            handle_list_topics(operation, csock);
            break;
        case EXIT:
            handle_exit(operation, csock);
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

    init_map(&topics);
    init_map(&subscriptions);

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

    free_map(&topics);
    free_map(&subscriptions);
    exit(EXIT_SUCCESS);
}
