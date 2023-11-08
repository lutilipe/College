#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFSZ 1024

int client_id = 0;

void parse_string(char* string) {
    int new_line = strlen(string) -1;
    if (string[new_line] == '\n')
        string[new_line] = '\0';
}

void parse_topic(char* topic) {
    char *substring = " in ";
    if (topic != NULL) {
        memmove(topic, topic + strlen(substring), strlen(topic));
    }
}

int handle_new_post(BlogOperation* operation) {
    char topic[sizeof(operation->topic)];
    fgets(topic, sizeof(topic) + 4, stdin);
    parse_string(topic);
    parse_topic(topic);
    strcpy(operation->topic, topic);

    char content[sizeof(operation->content)];
    fgets(content, sizeof(operation->content), stdin);
    parse_string(content);
    strcpy(operation->content, content);
    return 0;
}

int get_operation_type() {
/*     if (client_id == 0) {
        return NEW_CONNECTION;
    } */

    int type = -1;

    do {
        char in[20];
        scanf("%s", in);
        if (!strcmp(in, "publish")) {
            type = NEW_POST;
        } else if (!strcmp(in, "list topics")) {
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

int handle_input_operation(BlogOperation* operation) {
    operation->operation_type = get_operation_type();

    if (operation->operation_type == EXIT) {
        return 0;
    }

    switch (operation->operation_type) {
        case NEW_POST:
            return handle_new_post(operation);
        case LIST_TOPICS:
            return 0;
        case SUB_TOPIC:
            return 0;
        case UNSUB_TOPIC:
            return 0;
        default:
            return 1;
    }
}

void handle_server_msg(BlogOperation* msg) {
    // TODO
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

	while(1) {
        BlogOperation msg_sent;
        int error = handle_input_operation(&msg_sent);
        if (error) continue;
        send_message(s, &msg_sent);

        BlogOperation msg_received;
        int count = get_message(s, &msg_received);
        if (!count) {
            break;
        }
        handle_server_msg(&msg_received);
	}

    close(s);
	
	exit(EXIT_SUCCESS);
}