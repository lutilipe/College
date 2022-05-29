#include "utils.h"

#define LENGTH 5

void bubbleSort(int* v, int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (v[j] > v[j+1]) {
                swapUtil(v, j, j+1);
            }
        }
    }
}

int main() {
    int v[LENGTH] = { 5, 2, 1, 3, 4 };
    bubbleSort(v, LENGTH);
    printVector(v, LENGTH);
}
