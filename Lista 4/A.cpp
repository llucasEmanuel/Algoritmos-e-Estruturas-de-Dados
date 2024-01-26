#include <iostream>
#include <algorithm>
#define endl '\n'
#define lli long long int

using namespace std;

class Node {
public:
    lli key;
    Node *left;
    Node *right;
    lli height;
    lli left_nodes; // nodes menores q ele pra calcular o indice

    Node(lli k=0) {
        this->key = k;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 0; // altura da folha
        this->left_nodes = 1;
    }
};

class AVL {
private:

    Node *root;
    lli node_count;

    lli h(Node *rt) {
        if (rt == nullptr) {
            return -1;
        }
        else {
            return rt->height;
        }
    }
    lli get_balance(Node *rt) {
        if (rt == nullptr) {
            return 0;
        }
        else {
            return (this->h(rt->left) - this->h(rt->right));
        }
    }
    Node *right_rotate(Node *rt) {
        Node *l = rt->left;
        Node *lr = l->right;
        l->right = rt;
        rt->left = lr;
        rt->height = max(this->h(rt->left), this->h(rt->right)) + 1;
        l->height = max(this->h(l->left), this->h(l->right)) + 1;
        rt->left_nodes -= l->left_nodes;
        return l; // atualiza a subroot
    }
    Node *left_rotate(Node *rt) {
        Node *r = rt->right;
        Node *rl = r->left;
        r->left = rt;
        rt->right = rl;
        rt->height = max(this->h(rt->left), this->h(rt->right)) + 1;
        r->height = max(this->h(r->left), this->h(r->right)) + 1;
        r->left_nodes += rt->left_nodes;
        return r; // atualiza a subroot
    }
    Node *insert_aux(Node *rt, lli k) {
        if (rt == nullptr) {
            return new Node(k);
        }

        if (k < rt->key) {
            rt->left = this->insert_aux(rt->left, k);
            rt->left_nodes++;
        }
        else {
            rt->right = this->insert_aux(rt->right, k);
        }
        rt->height = 1 + max(this->h(rt->left), this->h(rt->right));
        int balance = this->get_balance(rt);
        if (balance < -1 && k >= rt->right->key) {
            return this->left_rotate(rt);
        }
        if (balance > 1 && k < rt->left->key) {
            return this->right_rotate(rt);
        }
        if (balance > 1 && k >= rt->left->key) { // LR
            rt->left = this->left_rotate(rt->left);
            return this->right_rotate(rt);
        }
        if (balance < -1 && k < rt->right->key) { // LR
            rt->right = this->right_rotate(rt->right);
            return this->left_rotate(rt);
        }
        return rt;
    } 
    void delete_tree(Node *rt) {
        if (rt != nullptr) { // em posorder
            this->delete_tree(rt->left);
            this->delete_tree(rt->right);
            delete rt;
        }
    }
    lli find_aux(Node *rt, lli k, lli &cnt) {
        if (rt == nullptr) {
            return -1;
        }

        if (k == rt->key) {
            cnt += rt->left_nodes;
            return cnt;
        }
        else if (k < rt->key) {
            return this->find_aux(rt->left, k, cnt);
        }
        else {
            cnt += rt->left_nodes;
            return this->find_aux(rt->right, k, cnt);
        }
    }

public:
    AVL() {
        this->root = nullptr;
        this->node_count = 0;
    }
    ~AVL() {
        this->delete_tree(this->root);
    }
    void find(lli k, lli &cnt) {
        if (this->find_aux(this->root, k, cnt) == -1) {
            cout << "Data tidak ada" << endl;
        }
        else { // printar a qtd de nodes a esquerda
            cout << cnt << endl;
        }
    }
    void insert(lli k) {
        this->root = this->insert_aux(this->root, k);
        this->node_count++;
    }
};

int main() {

    AVL tree;
    lli comandos;
    cin >> comandos;
    for (int i = 0; i < comandos; i++) {
        lli cnt = 0;
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            lli k;
            cin >> k;
            tree.insert(k);
        }
        else if (cmd == 2) {
            lli k;
            cin >> k;
            tree.find(k, cnt);
        }
    }

    return 0;
}
