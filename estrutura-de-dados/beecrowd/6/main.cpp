#include <iostream>
 
using namespace std;

class Country {
    private:
        string name;
        int medals[3];
    public:
        Country(): name("") {};
        string getName() { return name; };
        int* getMedals() { return medals;};
        void setGold(int g) { medals[0] = g; };
        void setSilver(int s) {  medals[1] = s; };
        void setBronze(int b) {  medals[2] = b; };
        int getGold() { return medals[0]; };
        int getSilver() { return medals[1]; };
        int getBronze() { return medals[2]; };
        void setName(string n) { name = n;};
};

void swap(Country* &nums, int idx1, int idx2) {
    Country tmp = nums[idx1];
    nums[idx1] = nums[idx2];
    nums[idx2] = tmp;
}

bool compareCountries(Country c1, Country c2) {
    int mT = 3;
    int *m1 = c1.getMedals();
    int *m2 = c2.getMedals();
    for (int i = 0; i < mT; i++) {
        if (m1[i] < m2[i]) {
            return true;
        } else if (m1[i] > m2[i]) return false;
    }


    return c1.getName() > c2.getName();
}

void bubbleSort(Country* c, int length) {
    int i = 0, j = 0;
    for (i = 0; i < length - 1; i++)
        for (j = 0; j < length - i - 1; j++)
            if (compareCountries(c[j], c[j+1])) {
                Country tmp = c[j];
                c[j] = c[j+1];
                c[j+1] = tmp;
            }
}

int main() {
    int t = 0;
    cin >> t;
    
    Country* table = new Country[t];

    for (int i = 0 ; i < t; i++) {
        string name  = "";
        int g  = 0;
        int s  = 0;
        int b  = 0;
        cin >> name >> g >> s >> b;
        table[i].setBronze(b);
        table[i].setGold(g);
        table[i].setSilver(s);
        table[i].setName(name);
    }

    bubbleSort(table, t);

    string ans = "";
    for (int j = 0; j < t; j++) {
        ans += table[j].getName() + " ";
        ans += to_string(table[j].getGold()) + " ";
        ans += to_string(table[j].getSilver()) + " ";
        ans += to_string(table[j].getBronze()) + '\n';
    }

    cout << ans;

    delete[] table;
 
    return 0;
}
