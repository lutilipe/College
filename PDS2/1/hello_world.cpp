#include <iostream>
#include <vector>
using namespace std;

bool includeNumber(vector<int> vec, int number) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == number) return true;
    }
    return false;
}

void printList(vector<int> vec) {
    int size = vec.size();
    for (int i = 0; i < size; i++) {
        if (i != size - 1) {
            cout << vec[i] << ' ';
        } else {
            cout << vec[i] << endl;
        }
    }
}

int main() {
    string list, curr_number;
    vector<int> odd;
    vector<int> even;
    int t;
    int i, count = 0;
    while (count <= 20 && cin) {
        if (cin >> t) {
            count++;
            if (t % 2 == 0) {
                if (!includeNumber(even, t)) {
                even.push_back(t);
            }
            } else {
                if (!includeNumber(odd, t)) {
                    odd.push_back(t);
                }
            }
        }
    }
    printList(even);
    printList(odd);
}