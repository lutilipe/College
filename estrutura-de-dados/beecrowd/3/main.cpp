#include <iostream>

class TreeNode {
    public:
        TreeNode() { val = 0; right = NULL; left = NULL; };
    private:
        int val;
        TreeNode *right;
        TreeNode *left;
        friend class Tree;
};

class QueueNode {
    public:
        QueueNode() { val = NULL; next = NULL; };
    private:
        QueueNode *next;
        TreeNode *val;
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

        void enqueue(TreeNode *ch);
        bool empty();
        TreeNode* dequeue();
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

void Queue::enqueue(TreeNode *ch) {
    QueueNode *n = new QueueNode();
    n->val = ch;
    tail->next = n;
    tail = n;
    length++;
}

TreeNode* Queue::dequeue() {
    if (empty()) 
        throw "Queue is empty!";

    TreeNode *aux = head->next->val;
    QueueNode *p = head;
    head = head->next;
    delete p;
    length--;
    return aux;
}

int Queue::size() {
    return length;
}

class Tree {
    private:
        TreeNode* root;
        void addHelper(TreeNode* &p, int val);
        void delHelper(TreeNode* p);
    public:
        Tree() { root = NULL; };
        ~Tree();
        void add(int val);
        std::string bfs();
        TreeNode* getRoot() { return root; };
};

void Tree::delHelper(TreeNode *p){
    if(p != NULL){
        delHelper(p->left);
        delHelper(p->right);
        delete p;
    }
}

Tree::~Tree() {
    delHelper(root);
    root = NULL;
}

std::string Tree::bfs() {
    Queue *q = new Queue();
    std::string ans = "";
    q->enqueue(root);
    while (!q->empty()) {
        TreeNode* tmp = q->dequeue();
        if (tmp != NULL) {
            ans += std::to_string(tmp->val);
            ans += " ";
            q->enqueue(tmp->left);
            q->enqueue(tmp->right);
        }
        delete tmp;
    }
    delete q;

    ans.pop_back();
    return ans;
}

void Tree::addHelper(TreeNode* &p, int val) {
    if (p == NULL) {
        p = new TreeNode();
        p->val = val;
    } else {
        if (val > p->val) {
            addHelper(p->right, val);
        } else {
            addHelper(p->left, val);
        }
    }
}

void Tree::add(int val) {
    addHelper(root, val);
}

int main() {
    int numberOfCases = 0, i = 0;
    std::cin >> numberOfCases;

    std::string ans = "";

    for (i = 0; i < numberOfCases; i++) {
        int treeLength = 0, j = 0;
        std::cin >> treeLength;

        Tree *t = new Tree();

        ans += "Case ";
        ans += std::to_string(i+1);
        ans += ":";
        ans += '\n';

        for (j = 0; j < treeLength; j++) {
            int tmp = 0;
            std::cin >> tmp;
            t->add(tmp);
        }
        ans += t->bfs();
        ans += '\n';
        ans += '\n';
    }
    std::cout << ans;
    return 0;
}
