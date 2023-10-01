#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>

#include "action_type.h"

#define ROWS 4
#define COLS 4
#define NUM_BOMBS 3

#define BOMB -1
#define HIDDEN -2
#define FLAG -3

#define BOMB_SYMBOL '*'
#define HIDDEN_SYMBOL '-'
#define FLAG_SYMBOL '>'

int game_started = 0;
int game_over = 0;

typedef struct Action {
    int type;
    int coordinates[2];
    int board[ROWS][COLS];
} Action;

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

void print_board(int board[ROWS][COLS], int revealed[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int revealed_cell = revealed[i][j];
            if (revealed_cell == 1) {
                if (board[i][j] == BOMB) {
                    printf("%c\t\t", BOMB_SYMBOL);
                } else {
                    printf("%i\t\t", board[i][j]);
                }
            } else if (revealed_cell == FLAG) {
                printf("%c\t\t", FLAG_SYMBOL);
            } else {
                printf("%c\t\t", HIDDEN_SYMBOL);
            }
        }
        printf("\n");
    }
}

void reveal_cell(int board[ROWS][COLS], int revealed[ROWS][COLS]) {
    int row, col;
    scanf("%d %d", &row, &col);

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("error: invalid cell\n");
        return;
    }

    if (revealed[row][col]) {
        printf("error: cell already revealed\n");
        return;
    }

    if (board[row][col] == BOMB) {
        game_over = 1;
    } else {
        revealed[row][col] = 1;
    }
}

void handle_action(
    enum ActionType action_type,
    int board[ROWS][COLS],
    int revealed[ROWS][COLS]
) {
    if (!game_started) {
        return;
    } 
    switch (action_type) {
        case REVEAL:
            reveal_cell(board, revealed);
            break;
        case FLAG_ACTION:
            break;
        case REMOVE_FLAG:
            break;
        case RESET:
            break;
        case EXIT:
            break;
        default:
            printf("error: command not found\n");
            break;
    }
}

int get_action() {
    int action;
    scanf("%i", &action);
    return action;
}

void start_game(Options* opt) {
    int board[ROWS][COLS];
    int revealed[ROWS][COLS] = {0};

    Action msg;

    init_board(board, opt->filename);

    while (!game_over) {
        int action = get_action();

        handle_action(action, board, revealed);

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
            msg.type = 6;
            game_over = 1;
        }

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                msg.board[i][j] = revealed[i][j] ? board[i][j] : HIDDEN;
            }
        }

        print_board(board, revealed);

        if (!game_over) {
            printf("\n");
        }
    }
    printf("GAME OVER\n");
    game_started = 0;
    return;
}

int main(int argc, char ** argv) {
    Options opt;
    parse_args(argc, argv, &opt);

    while (1) {
        int action = get_action();
        if (action == START && !game_started) {
            game_started = 1;
            start_game(&opt);
        }
    }

    return 0;
}
