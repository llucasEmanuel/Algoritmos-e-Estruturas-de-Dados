#include <iostream>
#include <vector>

using namespace std;

template <typename K, typename V> class HashTable {
private:
    vector<vector<pair<K, V>>> table;
    int hash(K key) {
        return abs(key) % this->table.size();
    }

public:
    HashTable(int m) {
        this->table.resize(m);
    }

    void add(K key, V value) {
        int ind = hash(key);
        this->table[ind].push_back(make_pair(key, value));
    }

    void remove(K key) {
        int ind = hash(key);
        if (this->table[ind].size() > 0) {
            int i = 0;
            for (; i < this->table[ind].size(); i++) {
                if (this->table[ind][i].first == key) {
                    this->table[ind].erase(this->table[ind].begin() + i);
                    return;
                }
            }
            cout << "CHAVE NAO PERTENCE A TABELA" << endl;
        } else {
            cout << "CHAVE NAO PERTENCE A TABELA" << endl;
        }
    }

    void find(K key) {
        int ind = hash(key);
        if (this->table[ind].size() > 0) {
            int i = 0;
            for (; i < this->table[ind].size(); i++) {
                if (this->table[ind][i].first == key) {
                    cout << "Posição: " << ind << ", Índice: " << i << endl;
                    return;
                }
            }
            cout << "CHAVE NAO PERTENCE A TABELA" << endl;
        } else {
            cout << "CHAVE NAO PERTENCE A TABELA" << endl;
        }
    }
};

int main() {
    

    return 0;
}
