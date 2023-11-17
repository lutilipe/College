#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define BUFSZ 1024

int client_id = 0;

/* Remove a quebra de linha de uma string, caso a mesma exista */
void parse_string(char* string) {
    int new_line = strlen(string) -1;
    if (string[new_line] == '\n')
        string[new_line] = '\0';
}

/* Remove os caracteres " in " de uma determinada string */
void parse_topic(char* topic) {
    char *substring = " in ";
    if (topic != NULL) {
        memmove(topic, topic + strlen(substring), strlen(topic));
    }
}

void handle_subscribe_post(BlogOperation* operation) {
    char topic[sizeof(operation->topic)];
    scanf("%s", topic);
    parse_string(topic);
    strcpy(operation->topic, topic);
}

void handle_unsubscribe_post(BlogOperation* operation) {
    char topic[sizeof(operation->topic)];
    scanf("%s", topic);
    parse_string(topic);
    strcpy(operation->topic, topic);
}

void handle_new_post(BlogOperation* operation) {
    char topic[sizeof(operation->topic)];
    fgets(topic, sizeof(topic) + 4, stdin);
    parse_string(topic);
    parse_topic(topic);
    strcpy(operation->topic, topic);

    char content[sizeof(operation->content)];
    fgets(content, sizeof(operation->content), stdin);
    parse_string(content);
    strcpy(operation->content, content);
}

/* Obtem o tipo da operacao a partir da entrada do usuario */
int get_operation_type() {
    int type = -1;

    do {
        char in[20];
        scanf("%s", in);
        if (!strcmp(in, "publish")) {
            type = NEW_POST;
        } else if (!strcmp(in, "list")) {
            scanf("%s", in);
            type = LIST_TOPICS;
        } else if (!strcmp(in, "subscribe")) {
            type = SUB_TOPIC;
        } else if (!strcmp(in, "unsubscribe")) {
            type = UNSUB_TOPIC;
        } else if (!strcmp(in, "exit")) {
            type = EXIT;
        } else {
            printf("error: command not found\n");
        }
    } while (type == -1);
    return type;
}

/* Trata a entrada do usuario */
int handle_input_operation(BlogOperation* operation) {
    operation->operation_type = get_operation_type();

    if (operation->operation_type == EXIT) {
        parse_operation_msg(operation, client_id, EXIT, 0, "", "");
        return 0;
    }

    switch (operation->operation_type) {
        case NEW_POST:
            handle_new_post(operation);
            parse_operation_msg(operation, client_id, NEW_POST, 0, operation->topic, operation->content);
            return 0;
        case LIST_TOPICS:
            parse_operation_msg(operation, client_id, LIST_TOPICS, 0, "", "");   
            return 0;
        case SUB_TOPIC:
            handle_subscribe_post(operation);
            parse_operation_msg(operation, client_id, SUB_TOPIC, 0, operation->topic, ""); 
            return 0;
        case UNSUB_TOPIC:
            handle_subscribe_post(operation);
            parse_operation_msg(operation, client_id, UNSUB_TOPIC, 0, operation->topic, ""); 
            return 0;
        default:
            return 1;
    }
}

void handle_server_msg(BlogOperation* operation) {
    if (!operation->server_response) {
        return;
    }
    switch (operation->operation_type) {
        case LIST_TOPICS:
            printf("%s\n", operation->content);
            break;
        case NEW_POST: {
            char parsed_id[3];
            parse_to_two_digits(operation->client_id, parsed_id);
            printf("new post added in %s by %s\n", operation->topic, parsed_id);
            printf("%s\n", operation->content);
            break;
        }
        case SUB_TOPIC: {
            if (strlen(operation->content) != 0) {
                printf("%s\n", operation->content);
            }
            break;
        }
        default:
            break;
    }
}

/* Faz uma requisicao no servidor para pegar o id do cliente */
void create_client_id(int soc) {
    BlogOperation msg;
    parse_operation_msg(&msg, client_id, NEW_CONNECTION, 0, "", "");
    send_message(soc, &msg);
    get_message(soc, &msg);
    client_id = msg.client_id;
}

int main(int argc, char **argv) {
    struct sockaddr_storage storage;
	if (0 != addrparse(argv[1], argv[2], &storage)) {
		exit(EXIT_FAILURE);
	}

	int s;
	s = socket(storage.ss_family, SOCK_STREAM, 0);
	if (s == -1) {
		exit(EXIT_FAILURE);
	}
	struct sockaddr *addr = (struct sockaddr *)(&storage);
	if (0 != connect(s, addr, sizeof(storage))) {
		exit(EXIT_FAILURE);
	}

	char addrstr[BUFSZ];
	addrtostr(addr, addrstr, BUFSZ);

	fd_set read_fds;
    fd_set write_fds;

    create_client_id(s);

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(s, &read_fds);

        /* Permite a selecao do canal de entrada ou saida pelo cliente */
        int select_result = select(s + 1, &read_fds, &write_fds, NULL, NULL);

        if (select_result == -1) {
            exit(EXIT_FAILURE);
        }

        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            BlogOperation msg_sent;
            int error = handle_input_operation(&msg_sent);
            if (error) continue;
            send_message(s, &msg_sent);
        }

        if (FD_ISSET(s, &read_fds)) {
            BlogOperation msg_received;
            get_message(s, &msg_received);
            if (msg_received.operation_type == EXIT) {
                break;
            }
            handle_server_msg(&msg_received);
        }
    }

    close(s);

    exit(EXIT_SUCCESS);
}