#include <iostream>
#include <algorithm> 
#include <vector>
#define endl '\n'

using namespace std;

class Cell {
public:
    string key;
    bool empty = true;
};

class HashTable {
private:
    static const int size = 101;
    vector<int> indexes;
    Cell hash_table[size];

    int h(string key) {
        int mult = 1;
        int soma = 0;
        for (int i = 0; i < key.size(); i++) {// -1 pelo \0?
            soma += (key[i] * mult);
            mult++;
        }
        return soma * 19;
    }
    int hash(string key) {
        return abs(h(key)) % 101;
    }
    int q_probe(int j) {
        return (j*j) + 23*j;
    }
public:
    void add(string key) {
        int ind = hash(key);
        int first_ind = ind;
        int j = 1;
        while (this->hash_table[ind].empty && j < 20) {
            ind = abs(first_ind + this->q_probe(j)) % 101;
            j++;
        }

        if (this->hash_table[ind].empty) {
            this->hash_table[ind].key = key;
            this->hash_table[ind].empty = false;
            this->indexes.push_back(ind);
        }
    }
    int find(string key) { // retorna o indice do elemento na tabela
        int ind = hash(key);
        int first_ind = ind;
        int j = 1;
        while (this->hash_table[ind].key != key && j < 20) {
            ind = abs(first_ind + this->q_probe(j)) % 101;
            j++;
        }

        if (this->hash_table[ind].key == key) {
            return ind;
        }
        else {
            return -1;
        }
    }
    void remove(string key) {
        int ind = this->find(key);
        if (ind != -1) {
            this->hash_table[ind].empty = true;
            this->hash_table[ind].key = "";
            this->indexes.erase(this->indexes.begin() + ind);
        }
    }
    void print() {
        cout << this->indexes.size() << endl;
        sort(this->indexes.begin(), this->indexes.end());
        for (int i: this->indexes) {
            cout << i << ":" << this->hash_table[i].key << endl;
        }
    }
};

int main() {

    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        HashTable dict;
        int operacoes;
        cin >> operacoes;
        for (int j = 0; j < operacoes; j++) {
            string comando;
            cin >> comando;
            if (comando[0] == 'A' && comando[1] == 'D' && comando[2] == 'D' && comando[3] == ':') {
                string str = "";
                for (int k = 4; k < comando.size(); k++) {
                    str.push_back(comando[k]);
                }
                dict.add(str);
            }
            else if(comando[0] == 'D' && comando[1] == 'E' && comando[2] == 'L' && comando[3] == ':') {
                string str = "";
                for (int k = 4; k < comando.size(); k++) {
                    str.push_back(comando[k]);
                }
                dict.remove(str);
            }
        }

        dict.print();
    }

    return 0;
}
