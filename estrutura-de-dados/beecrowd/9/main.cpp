#include <iostream>

using namespace std;

class Node {
    public:
        Node(): val(-1), next(NULL) {};
        Node(int i): val(i) {};
        Node(int i, Node* n): val(i), next(n) {};
        int val;
        Node *next;
};

class LinkedList {
    private:
        Node* head;
        Node* tail;
    public:
        LinkedList();
        void push(int item);
        string print();
};

LinkedList::LinkedList() {
    head = new Node();
    tail = tail;
}

void LinkedList::push(int item) {
    Node* newNode = new Node(item);
    if (!head->next) {
        head->next = newNode;
        tail = head->next;
    } else { 
        tail->next = newNode;
        tail = newNode;
    }
}

string LinkedList::print() {
    Node* curr = head->next;
    string ans = "";
    while (curr && curr->next) {
        ans += to_string(curr->val);
        ans += " -> ";
        curr = curr->next;
    }
    if (curr && curr->val) {
        ans += to_string(curr->val);
        ans += " ";
        ans += "-> ";
    }
    ans += "\\";
    return ans;
}

class Hash {
    public:
        Hash(int length);
        void print();
        void add(int item);
    private:
        int hash(int item);
        LinkedList* table;
        int size;
};

int Hash::hash(int item) {
    return item % size;
}

Hash::Hash(int length) {
    table = new LinkedList[length];
    size = length;
}

void Hash::add(int item) {
    int key = hash(item);
    table[key].push(item);
}

void Hash::print() {
    for (int i = 0; i < size; i++) {
        string tmp = table[i].print();
        cout << to_string(i) << " -> " << tmp << endl;
    }
}

int main() {
    int cases = 0;
    cin >> cases;
    for (int i = 0; i < cases; i++) {
        int tSize = 0, kSize = 0;
        cin >> tSize >> kSize;
        Hash* hash = new Hash(tSize);
        for (int j = 0; j < kSize; j++) {
            int tmp = 0;
            cin >> tmp;
            hash->add(tmp);
        }
        hash->print();
        if (i != cases - 1) {
            cout << endl;
        }
    }
    return 0;
}
