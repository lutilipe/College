#include <iostream>

using namespace std;

class TreeNode {
    public:
        TreeNode() { val = 0; right = NULL; left = NULL; };
    private:
        char val;
        TreeNode *right;
        TreeNode *left;
        friend class Tree;
};

class Tree {
    private:
        TreeNode* root;
        void addHelper(TreeNode* &p, char val);
        void delHelper(TreeNode* p);
        bool dfs(TreeNode* p, char val);
        void inorder(TreeNode* p, string* ans);
        void postorder(TreeNode* p, string* ans);
        void preorder(TreeNode* p, string* ans);
    public:
        Tree() { root = NULL; };
        ~Tree();
        void add(char val);
        bool has(char val);
        string getValues(string command);
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

void Tree::addHelper(TreeNode* &p, char val) {
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

void Tree::add(char val) {
    addHelper(root, val);
}

bool Tree::dfs(TreeNode* p, char val) {
    if (p == NULL) {
        return false;
    }

    if (val > p->val) {
        return dfs(p->right, val);
    } else if (val < p->val) {
        return dfs(p->left, val);
    }

    return true;
}

bool Tree::has(char val) {
    return Tree::dfs(root, val);
}

void Tree::inorder(TreeNode* p, string* ans) {
    if (p == NULL) {
        return;
    }
    inorder(p->left, ans);
    (*ans) += p->val;
    (*ans) += " ";
    inorder(p->right, ans);
}

void Tree::postorder(TreeNode* p, string* ans) {
    if (p == NULL) {
        return;
    }
    postorder(p->left, ans);
    postorder(p->right, ans);
    (*ans) += p->val;
    (*ans) += " ";
}

void Tree::preorder(TreeNode* p, string* ans) {
    if (p == NULL) {
        return;
    }
    (*ans) += p->val;
    (*ans) += " ";
    preorder(p->left, ans);
    preorder(p->right, ans);
}

string Tree::getValues(string command) {
    string ans;
    if (command == "INFIXA") {
        Tree::inorder(root, &ans);
    } else if (command == "PREFIXA") {
        Tree::preorder(root, &ans);
    } else {
        Tree::postorder(root, &ans);
    }
    ans.pop_back();
    return ans;
}

int main() {
    Tree *t = new Tree();

    string command;
    char c;

    cin >> command >> c;

    t->add(c);

    while (!cin.eof()) {
        cin >> command;
        if (command == "I") {
            cin >> c;
            t->add(c);
        } else if (command == "P") {
            cin >> c;
            bool found = t->has(c);
            if (found) {
                cout << c << " existe" << endl;
            } else {
                cout << c << " nao existe" << endl;
            }
        } else if (command == "INFIXA") {
            cout << t->getValues("INFIXA") << endl;
        } else if (command == "PREFIXA") {
            cout << t->getValues("PREFIXA") << endl;
        } else if (command == "POSFIXA") {
            cout << t->getValues("POSFIXA") << endl;
        } else {
            exit(1);
        }
        
        command = "";
        c = 0;
    }

    return 0;
}
