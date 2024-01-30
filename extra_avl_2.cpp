#include <iostream>
#include <vector>
#define endl '\n'

using namespace std;

int max(int a, int b) {
    if (a > b) return a;
    else return b; 
}

class MaxHeap {
private:
    vector<pair<int, string>> heap; // o int eh o num de modelos e a string a cor
    int size; // size = heap.size() - 1 (desconsidera o primeiro)

    void heapify() {
        for (int i = this->size / 2; i >= 1; i--) {
            int k = i;
            pair<int, string> v = this->heap[k];

            while (2*k <= this->size) {
                int j = 2*k;
                if (j < this->size) {
                    if (this->heap[j].first < this->heap[j+1].first) {
                        j++;
                    }
                }
                if (v.first >= this->heap[j].first) {
                    break;
                }
                else {
                    this->heap[k] = this->heap[j];
                    k = j;
                }
            }
            this->heap[k] = v;
        }
    }

public:
    MaxHeap(vector<pair<int, string>> vet) { // recebe um vetor
        this->size = vet.size();
        this->heap.emplace_back();
        for (int i = 0; i < vet.size(); i++) {
            this->heap.push_back(vet[i]);
        }
        this->heapify();
    }
    pair<int, string> get_max() {
        return this->heap[1];
    }
};

class Node {
public:
    pair<int, string> key;
    string brand;
    Node *right;
    Node *left;
    int height;

    Node(pair<int, string> k, string brand) { // cada node guarda um int associado a uma cor
        this->key = k;
        this->brand = brand;
        this->height = 0;
        this->right = nullptr;
        this->left = nullptr;
    }
};

class AVL {
private:
    Node *root;
    int node_count;

    int h(Node *rt) {
        if (rt == nullptr) {
            return -1;
        }
        else {
            return rt->height;
        }
    }
    int get_balance(Node *rt) {
        if (rt == nullptr) {
            return 0;
        }
        else {
            return (this->h(rt->left) - this->h(rt->right));
        }
    }
    int update_height(Node *rt) {
        return (max(this->h(rt->left), this->h(rt->right)) + 1);
    }
    Node *right_rotate(Node *rt) {
        Node *l = rt->left;
        Node *lr = l->right;
        l->right = rt;
        rt->left = lr;
        rt->height = this->update_height(rt);
        l->height = this->update_height(l);
        return l;
    }
    Node *left_rotate(Node *rt) {
        Node *r = rt->right;
        Node *rl = r->left;
        r->left = rt;
        rt->right = rl;
        rt->height = this->update_height(rt);
        r->height = this->update_height(r);
        return r;   
    }
    Node *insert_aux(Node *rt, pair<int, string> k, string brand) {
        if (rt == nullptr) {
            return new Node(k, brand);
        }
        if (k < rt->key) {
            rt->left = this->insert_aux(rt->left, k, brand);
        }
        else {
            rt->right = this->insert_aux(rt->right, k, brand);
        }
        rt->height = this->update_height(rt);
        int balance = this->get_balance(rt);
        if (balance < -1 && k.first >= rt->right->key.first) {
            return this->left_rotate(rt);
        }
        if (balance > 1 && k.first < rt->left->key.first) {
            return this->right_rotate(rt);
        }
        if (balance > 1 && k.first >= rt->left->key.first) {
            rt->left = this->left_rotate(rt->left);
            return this->right_rotate(rt);
        }
        if (balance < -1 && k.first < rt->right->key.first) {
            rt->right = this->right_rotate(rt->right);
            return this->left_rotate(rt);
        }
        return rt;
    }
    void delete_tree(Node *rt) {
        if (rt != nullptr) {
            this->delete_tree(rt->left);
            this->delete_tree(rt->right);
            delete rt;
        }
    }
    void print_pos(Node *rt) {
        if (rt != nullptr) {
            this->print_pos(rt->left);
            this->print_pos(rt->right);
            cout << rt->brand << ' ' << rt->key.second << endl;
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
    void print() {
        this->print_pos(this->root);
    }
    void insert(pair<int, string> k, string brand) {
        this->root = this->insert_aux(this->root, k, brand);
        this->node_count++;
    }
};

// armazenar numero de modelos e cores em uma heap maxima
// pegar todos os maiores elementos da heap maxima e colocar numa avl com o elemento e o brand
// printar brand e cor em posordem

int main() {

    int n;
    cin >> n;
    AVL tree;
    for (int i = 0; i < n; i++) {
        string brand; // pro node da avl
        cin >> brand;
        vector<pair<int, string>> heap;
        int kf = 0;
        while (kf != -1) {
            cin >> kf;
            if (kf != -1) {
                heap.push_back(make_pair(kf, "")); // str vazia preenche dps
            }
        }
        for (int j = 0; j < heap.size(); j++) {
            cin >> heap[j].second;
        }
        MaxHeap pq(heap);
        tree.insert(pq.get_max(), brand);
    }
    tree.print();
    
    return 0;
}
