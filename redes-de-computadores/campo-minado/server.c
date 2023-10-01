#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 4
#define COLS 4
#define NUM_BOMBS 3

#define BOMB -1
#define HIDDEN -2
#define FLAG -3

#define BOMB_SYMBOL '*'
#define HIDDEN_SYMBOL '-'
#define FLAG_SYMBOL '>'

struct Action {
    int type;
    int coordinates[2];
    int board[ROWS][COLS];
};

void create_bombs(int board[ROWS][COLS]) {
    srand(time(NULL));

    for (int k = 0; k < NUM_BOMBS; k++) {
        int row, col;
        do {
            row = rand() % ROWS;
            col = rand() % COLS;
        } while (board[row][col] == BOMB);
        board[row][col] = BOMB;
    }
}

void init_board(int board[ROWS][COLS]) {
    int i, j;
    for(i = 0; i < ROWS; i++) {
        for(j = 0; j < COLS; j++) {
            board[i][j] = HIDDEN;
        }
    }
    create_bombs(board);
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

void reveal_cell(int board[ROWS][COLS], int revealed[ROWS][COLS], int row, int col) {
    int count = 0;
    
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    for (int i = 0; i < 8; i++) {
        int newRow = row + dr[i];
        int newCol = col + dc[i];
        
        if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
            if (board[newRow][newCol] == BOMB) {
                count++;
            }
        }
    }

    revealed[row][col] = 1;
    board[row][col] = count;
}

int main() {
    int board[ROWS][COLS];
    int revealed[ROWS][COLS] = {0};

    struct Action msg;
    int game_over = 0;

    init_board(board);

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
            reveal_cell(board, revealed, row, col);
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

        // Envie a mensagem para o cliente
        // (Neste ponto, você implementaria a lógica de comunicação por sockets)

        // Imprima o tabuleiro atualizado para o cliente
        printf("\nTabuleiro atual:\n");
        print_board(board, revealed);

        if (!game_over) {
            printf("\n");
        }
    }

    return 0;
}
