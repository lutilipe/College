#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "common.h"

#define BUFSZ 1024

int game_started = 0;
int game_ended = 0;

int get_message_coords(Message* msg) {
    char input[100];
    int x = -1;
    int y = -1;
    scanf("%s", input);
    char *token = strtok(input, ",");
    if (token != NULL) {
        x = atoi(token);
    }
    token = strtok(NULL, ",");
    if (token != NULL) {
        y = atoi(token);
    }
    if (x < 0 || x >= ROWS || y < 0 || y >= COLS) {
        return 1;
    }

    msg->coordinates[0] = x;
    msg->coordinates[1] = y;
    return 0;
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
        } else {
            printf("error: command not found\n");
        }
    } while (type == -1);
    return type;
}

void handle_server_msg(Message* msg) {
    int type = msg->type;
    if (type == GAME_OVER) {
        printf("GAME OVER!\n");
        game_ended = 1;
    } else if (type == WIN) {
        printf("YOU WIN!\n");
        game_ended = 1;
    }
    print_board(msg->board);
}

int handle_reveal(Message* msg, int revealed[ROWS][COLS]) {
    int x = -1;
    int y = -1;
    
    int invalid_cell = get_message_coords(msg);

    if (invalid_cell) {
        printf("error: invalid cell\n");
        return 1;
    }

    x = msg->coordinates[0];
    y = msg->coordinates[1];

    if (revealed[x][y] == REVEALD_CELL) {
        printf("error: cell already revealed\n");
        return 1;
    }
    revealed[x][y] = REVEALD_CELL;
    return 0;
}

int handle_flag(Message* msg, int revealed[ROWS][COLS]) {
    int x = -1;
    int y = -1;
    
    int invalid_cell = get_message_coords(msg);

    if (invalid_cell) {
        printf("error: invalid cell\n");
        return 1;
    }
    x = msg->coordinates[0];
    y = msg->coordinates[1];


    if (revealed[x][y] == FLAG) {
        printf("error: cell already has a flag\n");
        return 1;
    } else if (revealed[x][y] == REVEALD_CELL) {
        printf("error: cannot insert flag in revealed cell\n");
        return 1;
    }
    revealed[x][y] = FLAG;

    return 0;
}

int handle_remove_flag(Message* msg, int revealed[ROWS][COLS]) {
    int x = -1;
    int y = -1;
    
    int invalid_cell = get_message_coords(msg);

    if (invalid_cell) {
        printf("error: invalid cell\n");
        return 1;
    }
    x = msg->coordinates[0];
    y = msg->coordinates[1];

    if (revealed[x][y] != FLAG) {
        return 1;
    }

    revealed[x][y] = 0;

    return 0;
}

void handle_reset(int revealed[ROWS][COLS]) {
    int i, j = 0;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            revealed[i][j] = 0;
        }
    }
}

int handle_input_message(Message* msg, int revealed[ROWS][COLS]) {
    msg->type = get_message_type();

    if (msg->type == EXIT) {
        return 0;
    }

    if ((!game_started && msg->type != START) || (game_ended && msg->type != RESET)) {
        return 1;
    }

    switch (msg->type) {
        case START:
            if (game_started) {
                return 1;
            }
            game_ended = 0;
            game_started = 1;
            return 0;
        case REVEAL:
            return handle_reveal(msg, revealed);
        case FLAG_ACTION:
            return handle_flag(msg, revealed);
        case REMOVE_FLAG:
            return handle_remove_flag(msg, revealed);
        case RESET:
            game_ended = 0;
            handle_reset(revealed);
            return 0;
        default:
            return 1;
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
        int error = handle_input_message(&msg_sent, revealed);
        if (error) continue;
        send_message(s, &msg_sent);

        Message msg_received;
        int count = get_message(s, &msg_received);
        if (!count) {
            break;
        }
        handle_server_msg(&msg_received);
	}

    close(s);
	
	exit(EXIT_SUCCESS);
}
