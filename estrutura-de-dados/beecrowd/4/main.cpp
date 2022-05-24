#include <iostream>
 
using namespace std;

void swap(int *nums, int idx1, int idx2) {
    int tmp = nums[idx1];
    nums[idx1] = nums[idx2];
    nums[idx2] = tmp;
}
 
int main() {
    int length = 0;
    cin >> length;
    int* nums = new int(length);

    for (int i = 0; i < length; i++) {
        cin >> nums[i];
    }
 
    return 0;
}
