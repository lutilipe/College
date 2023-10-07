#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include "common.h"

// Game definitions
#define NUM_BOMBS 3

int game_started = 0;
int game_over = 0;

typedef struct Options {
    char filename[100];
} Options;

void parse_args(int argc, char **argv, Options* opt) {
    int c;
    extern char * optarg;    

    opt->filename[0] = 0;

    while ((c = getopt(argc, argv, "i:")) != EOF)
    switch(c) {
        case 'i': 
            strcpy(opt->filename, optarg);
        break;
        default:
            break;
    }
}

void copy_board_to_msg(Message* msg, int board[ROWS][COLS], int revealed[ROWS][COLS], int show_all) {
    int i = 0, j = 0;
    for (i = 0; i < ROWS; i++) {
       for (j = 0; j < COLS; j++) {
            int cell = revealed[i][j];
            if (cell == REVEALD_CELL || show_all) {
                msg->board[i][j] = board[i][j];
            } else if (cell == FLAG) {
                msg->board[i][j] = FLAG;
            } else {
                msg->board[i][j] = HIDDEN;
            }
        } 
    }
}

void parse_msg_to_sent(
    int type,
    int board[ROWS][COLS],
    int revealed[ROWS][COLS],
    int csock
) {
    Message msg;
    msg.type = type;
    copy_board_to_msg(&msg, board, revealed, type == WIN || type == GAME_OVER);
    send_message(csock, &msg);
}

void init_board(int board[ROWS][COLS], char* filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "Error ao abrir: %s\n", filename);
        exit(1);
    }

    char line[1024];
    int rows = 0;
    int cols = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, ",");
        while (token != NULL) {
            board[rows][cols] = atof(token);
            token = strtok(NULL, ",");
            cols++;
        }
        rows++;
        cols = 0;
    }

    fclose (file); 
}

void handle_exit(int csock) {
    printf("client disconnected\n");
    close(csock);
}

int handle_game_win(int csock, int board[ROWS][COLS], int revealed[ROWS][COLS]) {
    int win = 1;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j] != BOMB && !revealed[i][j]) {
                    win = 0;
                    break;
                }
            }
        }

    return win;
}

void handle_remove_flag(int csock, int board[ROWS][COLS], int revealed[ROWS][COLS], Message* msg) {
    int row = msg->coordinates[0];
    int col = msg->coordinates[1];
    scanf("%d %d", &row, &col);

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS || revealed[row][col] != FLAG) {
        return;
    }

    revealed[row][col] = 0;
    parse_msg_to_sent(STATE, board, revealed, csock);
}

void handle_reset(int csock, int board[ROWS][COLS], int revealed[ROWS][COLS], Message* msg) {
    int i, j = 0;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            revealed[i][j] = 0;
        }
    }
    parse_msg_to_sent(STATE, board, revealed, csock);
    printf("starting new game\n");
}

void handle_add_flag(int csock, int board[ROWS][COLS], int revealed[ROWS][COLS], Message* msg) {
    int row = msg->coordinates[0];
    int col = msg->coordinates[1];

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        return;
    }

    if (revealed[row][col] == FLAG) {
        printf("error: cell already has a flag\n");
        return;
    }

    if (revealed[row][col] == REVEALD_CELL) {
        printf("error: cannot insert flag in revealed cell\n");
        return;
    }

    revealed[row][col] = FLAG;
    parse_msg_to_sent(STATE, board, revealed, csock);
}

void handle_reveal(int csock, int board[ROWS][COLS], int revealed[ROWS][COLS], Message* msg) {
    int row = msg->coordinates[0];
    int col = msg->coordinates[1];

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("error: invalid cell\n");
        return;
    }

    if (revealed[row][col] == REVEALD_CELL) {
        printf("error: cell already revealed\n");
        return;
    }

    if (board[row][col] == BOMB) {
        game_over = 1;
    } else {
        revealed[row][col] = 1;
        int win = handle_game_win(csock, board, revealed);
        if (win) {
            game_over = 1;
            return parse_msg_to_sent(WIN, board, revealed, csock);
        }
        parse_msg_to_sent(STATE, board, revealed, csock);
    }
}

int handle_action(
    Message* msg,
    int board[ROWS][COLS],
    int revealed[ROWS][COLS],
    int csock
) {
    switch (msg->type) {
        case REVEAL:
            handle_reveal(csock, board, revealed, msg);
            break;
        case FLAG_ACTION:
            handle_add_flag(csock, board, revealed, msg);
            break;
        case REMOVE_FLAG:
            handle_remove_flag(csock, board, revealed, msg);
            break;
        case RESET:
            handle_reset(csock, board, revealed, msg);
            break;
        case EXIT:
            handle_exit(csock);
            return 0;
        default:
            printf("error: command not found\n");
            return 1;
    }

    return -1;
}

void start_game(Options* opt, int csock) {
    if (game_started) {
        return;
    }
    game_started = 1;
    game_over = 0;

    int board[ROWS][COLS];
    int revealed[ROWS][COLS] = {0};

    init_board(board, opt->filename);
    parse_msg_to_sent(STATE, board, revealed, csock);

    while (!game_over) {
        int handle_result = -1;
        do {
            Message msg_received;
            get_message(csock, &msg_received);
            handle_result = handle_action(&msg_received, board, revealed, csock);
        } while (handle_result == 1);

        if (!handle_result || game_over) {
            parse_msg_to_sent(GAME_OVER, board, revealed, csock);
            break;
        }
    }
    game_started = 0;
    game_over = 0;
    return;
}

int main(int argc, char ** argv) {
    if (argc < 3) {
        logexit("argc");
    }

    struct sockaddr_storage storage;
    printf("%s %s\n", argv[0], argv[3]);
    if (0 != server_sockaddr_init(argv[1], argv[2], &storage)) {
        logexit("storage");
    }

    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if (s == -1) {
        logexit("socket");
    }

    int enable = 1;
    if (0 != setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))) {
        logexit("setsockopt");
    }

    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (0 != bind(s, addr, sizeof(storage))) {
        logexit("bind");
    }

    if (0 != listen(s, 1)) {
        logexit("listen");
    }

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);
    printf("bound to %s, waiting connections\n", addrstr);

    Options opt;
    parse_args(argc, argv, &opt);

    while (1) {
        struct sockaddr_storage cstorage;
        struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
        socklen_t caddrlen = sizeof(cstorage);

        int csock = accept(s, caddr, &caddrlen);
        if (csock == -1) {
            logexit("accept");
        }

        char caddrstr[BUFSZ];
        addrtostr(caddr, caddrstr, BUFSZ);
        printf("client connected\n");

        Message msg;
        get_message(csock, &msg);

        if (msg.type == START && !game_started) {
            start_game(&opt, csock);
        }
    }

    exit(EXIT_SUCCESS);
}
