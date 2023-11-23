#include <iostream>
#include <vector>
#define endl '\n'

using namespace std;

template <typename T> class HashTable {
private:
    static const int table_size = 10; // static representa variavel de classe (vai ser uma variavel para todas as instancias da classe)
    vector<T> hash_table[table_size]; // array de listas

    int hash(T key) {
        return abs(key) % table_size;
    }
public:
    void insert(T key) {
        int index = hash(key);
        this->hash_table[index].push_back(key);
    }
    void print() {
        for (int i = 0; i < this->table_size; i++) {
            cout << i << ' ';
            for (int j = 0; j < this->hash_table[i].size(); j++) {
                cout << this->hash_table[i][j] << ' ';
            }
            cout << endl;
        }
    }
};


int main() {

    int n;
    cin >> n;
    HashTable<int> hash_table;
    int value;
    for (int i = 0; i < n; i++) {
        cin >> value;
        hash_table.insert(value);
    }
    hash_table.print();

    return 0;
}
