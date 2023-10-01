#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>

#define ROWS 4
#define COLS 4
#define NUM_BOMBS 3

#define BOMB -1
#define HIDDEN -2
#define FLAG -3

#define BOMB_SYMBOL '*'
#define HIDDEN_SYMBOL '-'
#define FLAG_SYMBOL '>'

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
            if (revealed[i][j]) {
                if (board[i][j] == BOMB) {
                    printf("%c\t\t", BOMB_SYMBOL);
                } else {
                    printf("%i\t\t", board[i][j]);
                }
            } else {
                if (board[i][j] == FLAG) {
                    printf("%c\t\t", FLAG_SYMBOL);
                } else {
                    printf("%c\t\t", HIDDEN_SYMBOL);
                }
            }
        }
        printf("\n");
    }
}

int main(int argc, char ** argv) {
    int board[ROWS][COLS];
    int revealed[ROWS][COLS] = {0};

    Action msg;
    Options opt;
    int game_over = 0;

    parse_args(argc, argv, &opt);
    init_board(board, opt.filename);

    while (!game_over) {
        int row, col;

        printf("Digite a linha e a coluna (0 a 3) que deseja revelar: ");
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= ROWS || col < 0 || col >= COLS || revealed[row][col]) {
            printf("Coordenadas inválidas. Tente novamente.\n");
            continue;
        }

        msg.type = 1;  // Tipo de ação: revelar
        msg.coordinates[0] = row;
        msg.coordinates[1] = col;

        if (board[row][col] == BOMB) {
            // O cliente revelou uma célula com bomba, jogo encerrado
            msg.type = 8;  // Tipo de ação: game_over
            game_over = 1;
        } else {
            revealed[row][col] = 1;
        }

        // Verifique se o cliente ganhou
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
            msg.type = 6;  // Tipo de ação: win
            game_over = 1;
        }

        // Atualize o estado do tabuleiro na mensagem
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

    return 0;
}
