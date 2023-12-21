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

template <typename K, typename V> V find_aux(Node<K, V> *root, K key) {
    if (root == nullptr) { // chegou no ultimo node e nao achou a chave
        return V();
    }

    if (key == root->key) {
        return root->value;
    }
    else if (key > root->key) {
        return find_aux(root->right, key);
    }
    else {
        return find_aux(root->left, key);
    }
}

template <typename K, typename V> Node<K, V> *insert_aux(Node<K, V> *root, K key, V value) {
    if (root == nullptr) {
        return new Node<K, V>(key, value);
    }

    if (key < root->key) {
        root->left = insert_aux(root->left, key, value);
    }
    else {
        root->right = insert_aux(root->right, key, value);
    }
    return root; // serve pra volta da recursao
}

template <typename K, typename V> Node<K, V> *get_min(Node<K, V> *root) {
    if (root->left == nullptr) {
        return root;
    }
    return get_min(root->left);
}

template <typename K, typename V> Node<K, V> *delete_min(Node<K, V> *root) {
    if (root->left == nullptr) {
        return root->right;
    }
    root->left = delete_min(root->left);
    return root;
}

template <typename K, typename V> Node<K, V> *remove_aux(Node<K, V> *root, K key) {
    if (root == nullptr) {
        return nullptr;
    }

    if (key < root->key) {
        root->left = remove_aux(root->left, key);
    }
    else if (key > root->key) {
        root->right = remove_aux(root->right, key);
    }
    else {
        if (root->left == nullptr) {
            return root->right;
        }
        else if (root->right == nullptr) {
            return root->left;
        }
        else {
            Node<K, V> *temp = get_min(root->right);
            root->value = temp->value;
            root->key = temp->key;
            root->right = delete_min(root->right);
        }
    }
    return root;
}

template <typename K, typename V> void print_preorder(Node<K, V> *root) {
    if (root != nullptr) {
        cout << root->key << ": " << root->value << endl;
        print_preorder(root->left);
        print_preorder(root->right);
    }
}

template <typename K, typename V> void print_inorder(Node<K, V> *root) {
    if (root != nullptr) {
        print_inorder(root->left);
        cout << root->key << ": " << root->value << endl;
        print_inorder(root->right);
    }
}

template <typename K, typename V> void print_posorder(Node<K, V> *root) {
    if (root != nullptr) {
        print_posorder(root->left);
        print_posorder(root->right);
        cout << root->key << ": " << root->value << endl;
    }
}

template <typename K, typename V> void delete_tree(Node<K, V> *root) {
    if (root != nullptr) { // em posorder
        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
    }
}

template <typename K, typename V> class Dictionary { // dicionario implementado como BST
private:
    Node<K, V> *root;
    int node_count;
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
