#include <iostream>

template<typename T = int>
T fibonnacci(int n) {
    T x = 0, y = 1, z = 0;
    for (int i = 0; i < n; i++) {
        z = x + y;
        x = y;
        y = z;
    }
    return x;
}

int main() {
    std::cout << fibonnacci<unsigned long long>(80) << std::endl;
    return 0;
}