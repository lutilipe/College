#include <iostream>

using namespace std;

class Node {
    public:
        Node() { val = 0; next = NULL; };
    private:
        char val;
        Node *next;
        friend class Stack;
};

class Stack {
    private:
        Node *head;
        int length;
    public:
        Stack();
        ~Stack();

        void push(char ch);
        bool empty();
        void pop();
        int size();
};

Stack::Stack() {
    head = new Node();
    length = 0;
}

Stack::~Stack() {
    while(!empty()) {
        pop();
    }
    delete head;
}

bool Stack::empty() {
    return length == 0;
}

void Stack::push(char ch) {
    Node *n = new Node();
    Node *tmp = head->next;
    n->val = ch;
    head->next = n;
    n->next = tmp;
    length++;
}

void Stack::pop() {
    if (!empty()) {
        Node *tmp = head->next;
        head->next = tmp->next;
        delete tmp;
        length--;
    }
}

int Stack::size() {
    return length;
}

int main() {
    string s;

    cin >> s;

    Stack *st = new Stack();

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            st->push(s[i]);
        } else if (!st->empty()) {
            st->pop();
        }
    }

    string ans = "";

    if (st->size()) {
        ans += "Ainda temos ";
        ans += to_string(st->size());;
        ans += " assunto(s) pendente(s)!";
    } else {
        ans += "Partiu RU!";
    }

    cout << ans << endl;

    delete st;

    return 0;
}
