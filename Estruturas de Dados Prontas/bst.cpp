#include <iostream>
#define endl '\n'

using namespace std;

template <typename K, typename V> class Node {
public:
    K key;
    V value;
    Node<K, V> *left;
    Node<K, V> *right;

    Node(K k, V v) { // construtor
        this->key = k;
        this->value = v;
        this->right = nullptr;
        this->left = nullptr;
    }
};

template <typename K, typename V> class Dictionary { // dicionario implementado como BST
private:
    Node<K, V> *root;
    int node_count;

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
        return rt; // serve pra volta da recursao
    }
    Node<K, V> *get_min(Node<K, V> *rt) {
        if (rt->left == nullptr) {
            return rt;
        }
        return get_min(rt->left);
    }
    Node<K, V> *delete_min(Node<K, V> *rt) {
        if (rt->left == nullptr) {
            return rt->right;
        }
        rt->left = delete_min(rt->left);
        return rt;
    }
    Node<K, V> *remove_aux(Node<K, V> *rt, K k) {
        if (rt == nullptr) {
            return nullptr;
        }

        if (k < rt->key) {
            rt->left = remove_aux(rt->left, k);
        }
        else if (k > rt->key) {
            rt->right = remove_aux(rt->right, k);
        }
        else {
            if (rt->left == nullptr) {
                return rt->right;
            }
            else if (rt->right == nullptr) {
                return rt->left;
            }
            else {
                Node<K, V> *temp = get_min(rt->right);
                rt->value = temp->value;
                rt->key = temp->key;
                rt->right = delete_min(rt->right);
            }
        }
        return rt;
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
    V remove(K key) {
        V temp = find_aux(this->root, key);
        if (temp != V()) { // se achou o elemento
            this->root = remove_aux(this->root, key);
            this->node_count--;
        }
        return temp;
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
        else if (comando == "remove") {
            int k;
            cin >> k;
            dict.remove(k);
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
