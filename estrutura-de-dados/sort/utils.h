#include <iostream>

#ifndef UTILS
#define UTILS

void swapUtil(int *v, int i, int j) {
    int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

void printVector(int *v, int length) {
    for (int i = 0; i < length; i++) {
        std::cout << v[i] << std::endl;
    }
}

#endif