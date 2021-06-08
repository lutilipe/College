#include <stdio.h>
#include <stdlib.h>

#define MAX_MATRIX_LENGTH 100
#define MIN_MATRIX_LENGTH 1

int matrix[MAX_MATRIX_LENGTH][MAX_MATRIX_LENGTH];


int randInt(int min, int max) {
    return min + rand() % max;
}

void printMatrix(int m, int n) {
    int i, j;
    printf("\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
}

void fillBinaryMatrixWithOnes(int matrix[MAX_MATRIX_LENGTH][MAX_MATRIX_LENGTH], int m, int n) {
    int i = 0, j = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            matrix[i][j] = 1;
        }
    }
}

void fillMatrix(int m, int n, int k) {
    int i = 0, j = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            matrix[i][j] = randInt(1, k);
        }
    }
    printMatrix(m, n);
}

int findHorizontalSequences(int binaryMatrix[MAX_MATRIX_LENGTH][MAX_MATRIX_LENGTH], int m, int n) {
    int i, j, k, consec, start, found = 0;
    for (i = 0; i < m; i++) {
        consec = 1;
        start = 0;
        for (j = 1; j < n; j++) {
            if (matrix[i][j] == 0) {
                continue;
            } else if (matrix[i][j] == matrix[i][j-1]) {
                consec++;
                if (consec >= 3 && j == n - 1) {
                    for (k = start; k <= j; k++) {
                        binaryMatrix[i][k] = 0;
                    }
                    found = 1;
                }
            } else {
                if (consec >= 3) {
                    for (k = start; k < j; k++) {
                        binaryMatrix[i][k] = 0;
                    }
                    found = 1;
                }
                consec = 1;
                start = j;
            }
        }
    }
    return found;
}

int findVerticalSequences(int binaryMatrix[MAX_MATRIX_LENGTH][MAX_MATRIX_LENGTH], int m, int n) {
    int i, j, k, consec, start, found = 0;
    for (j = 0; j < n; j++) {
        consec = 1;
        start = 0;
        for (i = 1; i < m; i++) {
            if (matrix[i][j] == 0) {
                continue;
            } else if (matrix[i][j] == matrix[i-1][j]) {
                consec++;
                if (consec >= 3 && i == m - 1) {
                    for (k = start; k <= i; k++) {
                        binaryMatrix[k][j] = 0;
                    }
                    found = 1;
                }
            } else {
                if (consec >= 3) {
                    for (k = start; k < i; k++) {
                        binaryMatrix[k][j] = 0;
                    }
                    found = 1;
                }
                consec = 1;
                start = i;
            }
        }
    }
    return found;
}

void changeNumbersInSequenceToZero(int binaryMatrix[MAX_MATRIX_LENGTH][MAX_MATRIX_LENGTH], int m, int n) {
    int x, y;
    for (x = 0; x < m; x++) {
        for (y = 0; y < n; y++) {
            if (binaryMatrix[x][y] == 0) {
                matrix[x][y] = 0;
            }
        }
    }
}

int changeSequencesInMatrixToZero(int m, int n) {
    int hasMadeOperation = 0, foundHorizontalSequence = 0, foundVerticalSequence = 0;
    int binaryMatrix[MAX_MATRIX_LENGTH][MAX_MATRIX_LENGTH];
    fillBinaryMatrixWithOnes(binaryMatrix, m, n);
    foundHorizontalSequence = findHorizontalSequences(binaryMatrix, m, n);
    foundVerticalSequence = findVerticalSequences(binaryMatrix, m, n);
    changeNumbersInSequenceToZero(binaryMatrix, m, n);
    if (foundHorizontalSequence || foundVerticalSequence) {
        hasMadeOperation = 1;
    }
    return hasMadeOperation;
}

void countZeroInMatrix(int m, int n) {
    int i, j, count = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (matrix[i][j] == 0) {
                count++;
            }
        }
    }
    printf("\nQuantidade de zeros: %i\n", count);
}

void swapZerosToBegginingOfMatrix(int m, int n) {
    int i, j, k, tmp;
    for (j = 0; j < n; j++) {
        for (i = 0; i < m; i++) {
            if (matrix[i][j] == 0) {
                for (k = i; k > 0; k--) {
                    tmp = matrix[k][j];
                    matrix[k][j] = matrix[k-1][j];
                    matrix[k-1][j] = tmp;
                }
            }
        }
    }
}

int main() {
    int m, n, k, hasMadeOperation;
    do {
        scanf("%i %i %i", &m, &n, &k);
    } while (m > MAX_MATRIX_LENGTH || n > MAX_MATRIX_LENGTH || m < MIN_MATRIX_LENGTH || n < MIN_MATRIX_LENGTH || k < 1);
    fillMatrix(m, n, k);
    do {
        hasMadeOperation = changeSequencesInMatrixToZero(m, n);
        if (hasMadeOperation) {
            swapZerosToBegginingOfMatrix(m, n);
        }
    } while (hasMadeOperation);
    printMatrix(m, n);
    countZeroInMatrix(m, n);
}