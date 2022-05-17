#include <iostream>

class QueueNode {
    public:
        QueueNode() { val = 0; next = NULL; };
    private:
        QueueNode *next;
        int val;
        friend class Queue;
};

class Queue {
    private:
        QueueNode *head;
        QueueNode *tail;
        int length;
    public:
        Queue();
        ~Queue();

        void enqueue(char ch);
        bool empty();
        int dequeue();
        int size();
};

Queue::Queue() {
    head = new QueueNode();
    tail = head;
    length = 0;
}

Queue::~Queue() {
    while(!empty()) {
        dequeue();
    }
    delete head;
}

bool Queue::empty() {
    return length == 0;
}

void Queue::enqueue(char ch) {
    QueueNode *n = new QueueNode();
    n->val = ch;
    tail->next = n;
    tail = n;
    length++;
}

int Queue::dequeue() {
    if (empty()) 
        throw "Queue is empty!";

    int aux = head->next->val;
    QueueNode *p = head;
    head = head->next;
    delete p;
    length--;
    return aux;
}

int Queue::size() {
    return length;
}

class TreeNode {
    public:
        TreeNode() { val = 0; right = NULL; left = NULL; };
    private:
        int val;
        TreeNode *right;
        TreeNode *left;
        friend class Tree;
};

class Tree {
    private:
        TreeNode* root;
    public:
        Tree() { root = NULL; };
        void add(int val);
};

void Tree::add(int val) {
    TreeNode *t = new TreeNode();
    t->val = val;
    if (root == NULL) {
        root = t;
        return;
    }
}

int main() {
    Queue *q = new Queue();
    q->enqueue(1);
    q->enqueue(2);
    std::cout << q->size() << std::endl;
    std::cout << q->dequeue() << std::endl;
    std::cout << q->size() << std::endl;
    delete q;
    return 0;
}