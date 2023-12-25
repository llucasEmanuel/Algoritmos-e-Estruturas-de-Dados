#include <iostream>
#define endl '\n'

using namespace std;

class Node {
public:
    int key;
    Node *right;
    Node *left;

    Node(int k) {
        this->key = k;
        this->right = nullptr;
        this->left = nullptr;
    }
};

class BST {
private:
    Node *root;
    int node_count;

    Node *insert_aux(Node *rt, int k) {
        if (rt == nullptr) {
            return new Node(k); 
        }

        if (k < rt->key) {
            rt->left = this->insert_aux(rt->left, k);
        }
        else {
            rt->right = this->insert_aux(rt->right, k);
        }
        return rt;
    }
    void print(Node *rt) {
        cout << rt->key << ' ';
    }
    void preorder(Node *rt) {
        if (rt != nullptr) {
            cout << rt->key << ' ';
            this->preorder(rt->left);
            this->preorder(rt->right);
        }
    }
    void inorder(Node *rt) {
        if (rt != nullptr) {
            this->inorder(rt->left);
            cout << rt->key << ' ';
            this->inorder(rt->right);
        }
    }
    void posorder(Node *rt) {
        if (rt != nullptr) {
            this->posorder(rt->left);
            this->posorder(rt->right);
            cout << rt->key << ' ';
        }
    }
    void delete_tree(Node *rt) {
        if (rt != nullptr) {
            this->delete_tree(rt->left);
            this->delete_tree(rt->right);
            delete rt;
        }
    }
public:
    BST() { // construtor
        this->root = nullptr;
        this->node_count = 0;
    }
    ~BST() { // destrutor
        this->delete_tree(this->root);
    }
    void insert(int k) {
        this->root = insert_aux(this->root, k);
    }
    void print_pre() {
        this->preorder(this->root);
    }
    void print_in() {
        this->inorder(this->root);
    }
    void print_pos() {
        this->posorder(this->root);
    }
};

int main() {

    BST tree;
    int comandos;
    cin >> comandos;
    for (int i = 0; i < comandos; i++) {
        string cmd;
        cin >> cmd;
        if (cmd == "insert") {
            int k;
            cin >> k;
            tree.insert(k);
        }
        else if (cmd == "pre") {
            tree.print_pre();
            cout << endl;
        }
        else if (cmd == "in") {
            tree.print_in();
            cout << endl;
        }
        else if (cmd == "post") {
            tree.print_pos();
            cout << endl;
        }

    }

    return 0;
}
