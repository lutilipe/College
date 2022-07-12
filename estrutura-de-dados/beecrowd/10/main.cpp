#include <iostream>

using namespace std;

void swap(int* arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(int* arr, int start, int end) {
    int medianIndex = -1;

    int currLength = end - start;
    int middle = (start + end) / 2;
        medianIndex = middle;

    swap(arr, medianIndex, end);

    int pivot = arr[end];
    int i = start - 1;
    int j = start;
    for (j = start; j < end; j++) {
        if (!(arr[j] > pivot)) {
            i++;
            swap(arr, i, j);
        }
    }

    swap(arr, i + 1, end);
    return i + 1;
}

void quicksort(int* arr, int start, int end) {
    if (start < end) {
        int p = partition(arr, start, end);
        quicksort(arr, start, p - 1);
        quicksort(arr, p + 1, end);
    }
}

void sort(int* arr, int length) {
    int start = 0;
    quicksort(arr, start, length-1);
}

int main() {
    int n,num;
        int x,y;

    while (cin >> n) {
        int arr[10000];
        int aux = 0;

        for (int i=0;i<n;i++){
            scanf("%i %i", &x, &y);
            for (int i2=x;i2<=y;i2++){
                arr[aux] = i2;
                aux++;
            }
        }

        sort(arr, aux);

        scanf("%i", &num);

        int v=-1;
        int start = -1;
        int end = -1;

        for (int i = 0; i < aux; i++){
            if (arr[i] == num){
                v=i;
                start = i;
                break;
            }
        }

        for (int i = aux-1; i >= 0; i--){
            if (arr[i] == num){
                v=i;
                end = v;
                break;
            }
        }

        if (v != -1)
            printf("%i found from %i to %i\n", num, start, end);
        else
            printf("%i not found\n", num);
    }
    return 0;
}