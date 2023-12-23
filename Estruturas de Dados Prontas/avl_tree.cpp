#include <iostream>
#include <algorithm>
#define endl '\n'

using namespace std;

template <typename K, typename V> class Node {
public:
    K key;
    V value;
    Node<K, V> *left;
    Node<K, V> *right;
    int height;

    Node(K k, V v) { // construtor
        this->key = k;
        this->value = v;
        this->right = nullptr;
        this->left = nullptr;
        this->height = 0; // altura padrao de uma folha eh 0
    }
};

template <typename K, typename V> class Dictionary { // dicionario implementado como BST
private:
    Node<K, V> *root;
    int node_count;

    int getHeight(Node<K, V> *rt) {
        if (rt == nullptr) {
            return -1;
        }
        else {
            return rt->height;
        }
    }
    int getBalance(Node<K, V> *rt) {
        if (rt == nullptr) {
            return 0;
        }
        else {
            return (getHeight(rt->left) - getHeight(rt->right));
        }
    }
    Node<K, V> *rightRotate(Node<K, V> *rt) {
        Node<K, V> *l = rt->left;
        Node<K, V> *lr = l->right;
        l->right = rt;
        rt->left = lr;
        rt->height = max(getHeight(rt->left), getHeight(rt->right)) + 1;
        l->height = max(getHeight(l->left), getHeight(l->right)) + 1;
        cout << "R-rotate" << endl;
        return l;
    }
    Node<K, V> *leftRotate(Node<K, V> *rt) {
        Node<K, V> *r = rt->right;
        Node<K, V> *rl = r->left;
        r->left = rt;
        rt->right = rl;
        rt->height = max(getHeight(rt->left), getHeight(rt->right)) + 1;
        r->height = max(getHeight(r->left), getHeight(r->right)) + 1;
        cout << "L-rotate" << endl;
        return r;
    }
    V find_aux(Node<K, V> *rt, K k) {
        if (rt == nullptr) { // chegou no ultimo node e nao achou a chave
            return V();
        }

        if (k == rt->key) {
            return rt->value;
        }
        else if (k > rt->key) {
            return find_aux(rt->right, k);
        }
        else {
            return find_aux(rt->left, k);
        }
    }
    Node<K, V> *insert_aux(Node<K, V> *rt, K k, V v) {
        if (rt == nullptr) {
            return new Node<K, V>(k, v);
        }

        if (k < rt->key) {
            rt->left = insert_aux(rt->left, k, v);
        }
        else {
            rt->right = insert_aux(rt->right, k, v);
        }
        rt->height = 1 + max(getHeight(rt->left), getHeight(rt->right));
        int balance = getBalance(rt);
        if (balance < -1 && k >= rt->right->key) {
            return leftRotate(rt);
        }
        if (balance > 1 && k < rt->left->key) {
            return rightRotate(rt);
        }
        if (balance > 1 && k >= rt->left->key) { // LR
            rt->left = leftRotate(rt->left);
            return rightRotate(rt);
        }
        if (balance < -1 && k < rt->right->key) { // LR
            rt->right = rightRotate(rt->right);
            return leftRotate(rt);
        }
        return rt; // serve pra volta da recursao
    }
    void print_preorder(Node<K, V> *rt) {
        if (rt != nullptr) {
            cout << rt->key << ": " << rt->value << endl;
            print_preorder(rt->left); // faz a recursao sem o this
            print_preorder(rt->right);
        }
    }
    void print_inorder(Node<K, V> *rt) {
        if (rt != nullptr) {
            print_inorder(rt->left);
            cout << rt->key << ": " << rt->value << endl;
            print_inorder(rt->right);
        }
    }
    void print_posorder(Node<K, V> *rt) {
        if (rt != nullptr) {
            print_posorder(rt->left);
            print_posorder(rt->right);
            cout << rt->key << ": " << rt->value << endl;
        }
    }
    void delete_tree(Node<K, V> *rt) {
        if (rt != nullptr) { // em posorder
            this->delete_tree(rt->left);
            this->delete_tree(rt->right);
            delete rt;
        }
    }
public:
    Dictionary() { // construtor
        this->root = nullptr;
        this->node_count = 0;
    }
    ~Dictionary() { // destrutor
        delete_tree(this->root);
    }
    V find(K key) {
        return find_aux(this->root, key);
    }
    void insert(K key, V value) {
        this->root = insert_aux(this->root, key, value);
        this->node_count++;
    }
    void print() {
        print_inorder(this->root);
    }
};

int main() {

    Dictionary<int, string> dict;

    string comando;
    while (cin >> comando){
        if (comando == "add") {
            int k;
            string v;
            cin >> k >> v;
            dict.insert(k, v);
        }
        else if (comando == "find") {
            int k;
            cin >> k;
            cout << dict.find(k) << endl;
        }
        dict.print(); // usa o inorder
    }

    return 0;
}
