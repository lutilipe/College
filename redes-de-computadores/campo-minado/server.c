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

// Game constants
#define BOMB -1
#define HIDDEN -2
#define FLAG -3
#define REVEALD_CELL 1

#define BOMB_SYMBOL '*'
#define HIDDEN_SYMBOL '-'
#define FLAG_SYMBOL '>'

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

void print_board(int board[ROWS][COLS], int revealed[ROWS][COLS], int show_all) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int cell = revealed[i][j];
            if (cell == REVEALD_CELL || show_all) {
                if (board[i][j] == BOMB) {
                    printf("%c\t\t", BOMB_SYMBOL);
                } else {
                    printf("%i\t\t", board[i][j]);
                }
            } else if (cell == FLAG) {
                printf("%c\t\t", FLAG_SYMBOL);
            } else {
                printf("%c\t\t", HIDDEN_SYMBOL);
            }
        }
        printf("\n");
    }
}

void handle_send_curr_state(int board[ROWS][COLS], int revealed[ROWS][COLS]) {
    return;
}

void handle_exit(int* csock) {
    printf("client disconnected\n");
    close(csock);
}

void handle_game_win(int board[ROWS][COLS], int revealed[ROWS][COLS]) {
    int win = 1;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j] != BOMB && !revealed[i][j]) {
                    win = 0;
                    break;
                }
            }
        }

    if (win) {
        game_over = 1;
        printf("YOU WIN\n");
    }
}

void handle_remove_flag(int revealed[ROWS][COLS]) {
    int row, col;
    scanf("%d %d", &row, &col);

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS || revealed[row][col] != FLAG) {
        return;
    }

    revealed[row][col] = 0;
}

void handle_reset(int revealed[ROWS][COLS]) {
    int i, j = 0;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            revealed[i][j] = 0;
        }
    }
    printf("starting new game\n");
}

void handle_add_flag(int revealed[ROWS][COLS]) {
    int row, col;
    scanf("%d %d", &row, &col);

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
}

void handle_reveal(int board[ROWS][COLS], int revealed[ROWS][COLS]) {
    int row, col;
    scanf("%d %d", &row, &col);

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
        printf("GAME OVER\n");
        print_board(board, revealed, 1);
    } else {
        revealed[row][col] = 1;
    }
}

int handle_action(
    enum ActionType action_type,
    int board[ROWS][COLS],
    int revealed[ROWS][COLS],
    int* csock
) {
    switch (action_type) {
        case REVEAL:
            handle_reveal(board, revealed);
            break;
        case FLAG_ACTION:
            handle_add_flag(revealed);
            break;
        case REMOVE_FLAG:
            handle_remove_flag(revealed);
            break;
        case RESET:
            handle_reset(revealed);
            break;
        case EXIT:
            handle_exit(csock);
            return 0;
        default:
            printf("error: command not found\n");
            return 2;
    }

    return 1;
}

int get_action() {
    int action;
    scanf("%i", &action);
    return action;
}

void start_game(Options* opt, int* csock) {
    int board[ROWS][COLS];
    int revealed[ROWS][COLS] = {0};

    Message msg;

    init_board(board, opt->filename);

    while (!game_over) {
        int handle_result = -1;
        do {
            int action = get_action();
            handle_result = handle_action(action, board, revealed, csock);
        } while (handle_result == 2);

        if (!handle_result || game_over) {
            break;
        }

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                msg.board[i][j] = revealed[i][j] == REVEALD_CELL ? board[i][j] : HIDDEN;
            }
        }

        print_board(board, revealed, 0);

        printf("\n");
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
        printf("client connected");

        char buf[BUFSZ];
        memset(buf, 0, BUFSZ);
        size_t count = recv(csock, buf, BUFSZ - 1, 0);
        printf("[msg] %s, %d bytes: %s\n", caddrstr, (int)count, buf);

        sprintf(buf, "remote endpoint: %.1000s\n", caddrstr);
        count = send(csock, buf, strlen(buf) + 1, 0);
        if (count != strlen(buf) + 1) {
            logexit("send");
        }
        close(csock);

        /* int action = get_action();
        if (action == START && !game_started) {
            game_started = 1;
            start_game(&opt, &csock);
        } */
    }

    exit(EXIT_SUCCESS);
}
