#include <iostream>
 
using namespace std;

void swap(string* nums, int idx1, int idx2) {
    string tmp = nums[idx1];
    nums[idx1] = nums[idx2];
    nums[idx2] = tmp;
}

void bubbleSort(string* nums, int length) {
    int i = 0, j = 0;
    for (i = 0; i < length - 1; i++)
        for (j = 0; j < length - i - 1; j++)
            if (nums[j].size() < nums[j + 1].size())
                swap(nums, j+1, j);
}

int main() {
    int n = 0, i = 0;
    cin >> n;
    string v[n];
    cin.ignore();
    for (int i = 0; i < n; i++) {
        getline(cin, v[i]);
    }
    for (int i = 0; i < n; i++) {
        string str[50];
        int c = 0;
        string tmp = "";
        for (int j = 0; j < v[i].size(); j++) {
            if (v[i][j] == ' ') {
                str[c] = tmp;
                tmp = "";
                c++;
            } else {
                tmp += v[i][j];
            }
        }
        str[c] = tmp;
        c++;
        bubbleSort(str, c);
        for (int j = 0; j < c; j++) {
            if (j != c - 1) {
                cout << str[j] << " ";
            } else {
                cout << str[j];
            }
        }
        cout  << endl;
    }
    return 0;
}
