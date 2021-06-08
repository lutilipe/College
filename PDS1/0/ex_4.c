#include <stdio.h>
#include <stdlib.h>

int main() {
    int files;
    files = system("ls");
    printf("%d", files);
    return 0;
}