#include <stdio.h>
#include <string.h>

using namespace std;

class StackNode {
    public:
        StackNode() { val = 0; next = NULL; };
    private:
        long long int val;
        StackNode *next;
        friend class Stack;
};

class Stack {
    private:
        int id = -1;
        StackNode *head;
        int length;
    public:
        Stack();
        ~Stack();

        void push(long long int el);
        bool empty();
        void clean();
        void pop();
        int size();
        long long int top();
};

Stack::Stack() {
    head = new StackNode();
    length = 0;
}

void Stack::clean() {
    while(!empty()) {
        pop();
    }
}

Stack::~Stack() {
    Stack::clean();
    delete head;
}

bool Stack::empty() {
    return length == 0;
}

void Stack::push(long long int el) {
    StackNode *n = new StackNode();
    StackNode *tmp = head->next;
    n->val = el;
    head->next = n;
    n->next = tmp;
    length++;
}

void Stack::pop() {
    StackNode *tmp = head->next;
    head->next = tmp->next;
    delete tmp;
    length--;
}

long long int Stack::top() {
    return this->head->next->val;
}

int Stack::size() {
    return length;
}

int main() {
    int t = 0;
    scanf("%u", &t);
    Stack* st = new Stack();
    Stack* aux = new Stack();
    char c[4];
    long long int val = 0;
    while (t > 0) {
        scanf("%s", c);
        if (strcmp(c, "POP") == 0) {
            if (st->empty()) {
                printf("EMPTY\n");
            } else {
                st->pop();
                aux->pop();
            }
        } else if (strcmp(c, "MIN") == 0) {
            if (aux->empty()) {
                printf("EMPTY\n");
            } else {
                printf("%lld\n", aux->top());
            }
        } else {
            scanf("%lld", &val);
            st->push(val);
            if (aux->empty()) {
                aux->push(val);
            } else {
                if (val < aux->top()) {
                    aux->push(val);
                } else {
                    aux->push(aux->top());
                }
            }
        } 
        t--;
    }

    return 0;
}