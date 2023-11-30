#include <iostream>
#include <cmath>
#include <vector>
#define endl '\n'

using namespace std;

template <typename K, typename V> class Cell {
public:
    pair <K, V> pair;
    bool empty = true;
};

template <typename K, typename V> class HashTable {
private:
    vector<Cell<K, V>> table;
    vector<int> perm;

    int hash(K key) {
        int temp = static_cast<int>(floor(static_cast<double>(key) / static_cast<double>(this->table.size())));
        int hash = key - (this->table.size() * temp);
        return hash;
    }
    int step(int i) {
        return this->perm[i];
    }
public:
    HashTable(int m) {
        this->table.resize(m);

        this->perm.resize(m-1);
        for (int i = 0; i < m-1; i++) {
            cin >> this->perm[i];
        }
    }
    void add(K key, V value) {
        int ind = hash(key);
        int first_ind = ind;
        int i = 0;
        while (!this->table[ind].empty && i < this->perm.size()) {
            ind = (first_ind + step(i)) % this->table.size();
            i++;
        }

        if (this->table[ind].empty) {
            this->table[ind].empty = false;
            this->table[ind].pair = make_pair(key, value);
            cout << "ADICIONADO NO INDICE " << ind << endl;
        }
        else {
            cout << "TABELA CHEIA" << endl;
        }
    }
    void find(K key) {
        int ind = hash(key);
        int first_ind = ind;
        int i = 0;
        while (this->table[ind].pair.first != key && i < this->perm.size()) {
            ind = (first_ind + step(i)) % this->table.size();
            i++;
        }

        if (this->table[ind].pair.first == key && !this->table[ind].empty) {
            cout << ind << endl;
        }
        else {
            cout << -1 << endl;
        }
    }
};

int main() {

    int m;
    cin >> m;
    HashTable<int, int> dict(m);

    int operacoes;
    cin >> operacoes;
    for (int i = 0; i < operacoes; i++) {
        string comando;
        cin >> comando;
        
        if (comando == "add") {
            int k, v;
            cin >> k >> v;
            dict.add(k, v);
        }
        else if (comando == "find") {
            int k;
            cin >> k;
            dict.find(k);
        }
    }

    return 0;
}
