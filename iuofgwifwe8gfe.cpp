#include <iostream>
#define endl '\n'

using namespace std;

template <typename K, typename V> class Node {
public:
    pair<K, V> entry;
    Node *right;
    Node *left;

    Node(K key, V value) {
        this->entry = make_pair(key, value);
        this->right = nullptr;
        this->left = nullptr;
    }
};

template <typename K, typename V> class Dictionary { // BST implementation
private:
    Node<K, V> *root;
    int node_count;
public:
    Dictionary() {
        this->root = nullptr;
        this->node_count = 0;
    }
    V find(K key) {
        if (this->root == nullptr) {
            return V();
        }              

        if (key == this->root) {
            return this->root->entry.value;
        }    
        else if (key > this->root) {
            return this->root->right.find(key);
        }
        else {
            return this->root->left.find(key);
        }                                                                                                         
    }
};

int main() {



    return 0;
}
