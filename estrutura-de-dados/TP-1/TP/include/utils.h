#ifndef UTILS_H
#define UTILS_H

template <typename T>
void sort(T *v, int length) {
    if (!length) return;
    // Bubble sort
    int i = 0, j = 0;
    for (i = 0; i < length - 1; i++) {
        for (j = 0; j < length - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                T tmp = v[j];
                v[j] = v[j+1];
                v[j+1] = tmp;
            }
        }
    }
}

#endif