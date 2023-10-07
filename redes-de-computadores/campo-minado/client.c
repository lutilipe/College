#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "common.h"

#define BUFSZ 1024

void get_message_coords(Message* msg) {
    char input[3];
    do {
        scanf("%s", input);
    } while (sizeof(input) != sizeof(char)*3);
    char *token = strtok(input, ",");
    if (token != NULL) {
        msg->coordinates[0] = atoi(token);
    }
    token = strtok(NULL, ",");
    if (token != NULL) {
        msg->coordinates[1] = atoi(token);
    }
}

int get_message_type() {
    int type = -1;

    do {
        char in[100];
        scanf("%s", in);
        if (!strcmp(in, "start")) {
            type = START;
        } else if (!strcmp(in, "reveal")) {
            type = REVEAL;
        } else if (!strcmp(in, "flag")) {
            type = FLAG_ACTION;
        } else if (!strcmp(in, "remove_flag")) {
            type = REMOVE_FLAG;
        } else if (!strcmp(in, "reset")) {
            type = RESET;
        } else if (!strcmp(in, "exit")) {
            type = EXIT;
        }
    } while (type == -1);
    return type;
}

int handle_server_msg(Message* msg) {
    int type = msg->type;
    if (type == GAME_OVER) {
        printf("GAME OVER!\n");
    } else if (type == WIN) {
        printf("YOU WIN!\n");
    }
    print_board(msg->board);
    if (type == GAME_OVER || type == WIN) {
        return 0;
    }
    return 1;
}

void get_message_input(Message* msg) {
    msg->type = get_message_type();
    if (
        msg->type == REVEAL ||
        msg->type == REMOVE_FLAG ||
        msg->type == FLAG_ACTION    
    ) {
        get_message_coords(msg);
    }
}

int main(int argc, char **argv) {
    struct sockaddr_storage storage;
	if (0 != addrparse(argv[1], argv[2], &storage)) {
		logexit("addparse");
	}

	int s;
	s = socket(storage.ss_family, SOCK_STREAM, 0);
	if (s == -1) {
		logexit("socket");
	}
	struct sockaddr *addr = (struct sockaddr *)(&storage);
	if (0 != connect(s, addr, sizeof(storage))) {
		logexit("connect");
	}

	char addrstr[BUFSZ];
	addrtostr(addr, addrstr, BUFSZ);

    int revealed[ROWS][COLS] = {0};

	while(1) {
        Message msg_sent;
        get_message_input(&msg_sent);
        send_message(s, &msg_sent);

        Message msg_received;
        int count = get_message(s, &msg_received);
        if (count == 0) {
            break;
        }
        if (!handle_server_msg(&msg_received)) {
            break;
        }
	}

    close(s);
	
	exit(EXIT_SUCCESS);
}
