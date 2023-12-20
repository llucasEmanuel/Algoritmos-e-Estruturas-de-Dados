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

    void insert_aux(int k) { // dps add o node null como caso base da recursao
        if (k < this->key) {
            if (this->left == nullptr) {
                this->left = new Node(k);
            }
            else {
                this->left->insert_aux(k);
            }
        }
        else {
            if (this->right == nullptr) {
                this->right = new Node(k);
            }
            else {
                this->right->insert_aux(k);
            }
        }
    }
};

void print_preorder(Node *root) {
    if (root != nullptr) {
        cout << ' ' << root->key;
        print_preorder(root->left);
        print_preorder(root->right);
    }
}
void print_inorder(Node *root) {
    if (root != nullptr) {
        print_inorder(root->left);
        cout << ' ' << root->key;
        print_inorder(root->right);
    }
}
void print_posorder(Node *root) {
    if (root != nullptr) {
        print_posorder(root->left);
        print_posorder(root->right);
        cout << ' ' << root->key;
    }
}

class BST {
private:
    int node_count;
public:
    Node *root;
    BST() {
        this->root = nullptr;
        this->node_count = 0;
    }
    void insert(int k) {
        if (this->root == nullptr) { // se nao tiver elementos
            this->root = new Node(k);
        }
        else {
            this->root->insert_aux(k);
        }
        this->node_count++;
    }
};

int main() {

    int n;
    cin >> n;
    BST tree;
    for (int i = 0; i < n; i++) { // insercao na arvore
        int k;
        cin >> k;
        tree.insert(k);
    }

    cout << "Pre order :"; print_preorder(tree.root); cout << endl;
    cout << "In order  :"; print_inorder(tree.root); cout << endl;
    cout << "Post order:"; print_posorder(tree.root); cout << endl;


    return 0;
}
