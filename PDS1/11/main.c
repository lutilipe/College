#include <stdio.h>

void swap(int* xp, int* yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}

void prinfRow(int vec[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%i ", vec[i]);
    }

    printf("\n");
}

int main() {
    FILE *arq;
    arq = fopen("cartelas.txt", "r");

    int n, count = 0, i = 0, j = 0, result = 0;
    int win[] = {4, 8, 15, 16, 23, 42}, curr[6];

    while (!feof(arq)) {
        fscanf(arq, "%d", &n);
        curr[i] = n;
        if (i == 5) {
            selectionSort(curr, 6);
            for (j = 0; j < 6; j++) {
                if (curr[j] == win[j]) {
                    count++;
                } else {
                    i = 0;
                    count = 0;
                    break;
                }

                if (count == 6) {
                    result += 1;
                    i = 0;
                    count = 0;
                }
            }
        } else {
            i++;
        }
    }
    printf("%d\n", result);
    fclose(arq);
    return 0;
}