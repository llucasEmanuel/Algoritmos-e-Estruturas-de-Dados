#include <iostream>
#include <cmath>

#define endl '\n'

using namespace std;

class Pair {
public:
    int first;
    int second;
};

class TableNode : public Pair {
public:
    bool empty;
};

class Dictionary {
private:
    int table_size;
    TableNode *hash_table;
    int hash(int k) {
        return k - (this->table_size * floor(k / this->table_size));
    }
    int *perm; // array de steps
public:
    Dictionary(int m) {
        this->hash_table = new TableNode[m];
        this->table_size = m;
        for (int i = 0; i < m; i++) {
            this->hash_table[i].empty = true; // marca a flag de vazio em todos os espacos
        }
        perm = new int[m-1];
        for (int i = 0; i < m-1; i++) {
            cin >> perm[i];
        }
    }
    void add(int key, int value) {
        Pair kv = {key, value};
        
    }
    int find(int key) {

    }
};

int main() {

    int m;
    cin >> m;
    Dictionary dict(m);

    return 0;
}
