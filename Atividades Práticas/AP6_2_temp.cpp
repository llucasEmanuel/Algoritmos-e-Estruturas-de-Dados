#include <iostream>
#include <vector>
#define endl '\n'

using namespace std;

class Cell {
public:
    string key;
    bool empty;
    Cell() {
        this->empty = true; // inicializa todos como empty
    }
};

class HashTable{
private:
    vector<Cell> table;
    int hash(string str) {
        int sum = 0;
        for (char &i : str) {
            sum += i;
        }
        return abs(sum) % this->table.size();
    }
    int probe(int &i) { // retorna o step em relacao ao calculado pela função hash
        return i++;
    }
public:
    HashTable(int m) {
        this->table.resize(m);
    }
    void add(string key) {
        int ind = hash(key);
        int first_ind = ind;
        int i = 0;
        while (!this->table[ind].empty && i < this->table.size()) {
            // calculo do step em relacao ao primeiro ind da funcao hash
            ind = (first_ind + probe(i)) % this->table.size();
        }

        if (this->table[ind].empty) {
            this->table[ind].key = key;
            this->table[ind].empty = false;
            //cout << "Adicionado no indice " << ind << endl;
        }
        else {
            cout << "Tabela cheia" << endl;
        }
    }
    void rmv(string key) {
        int ind = hash(key);
        int first_ind = ind;
        int i = 0;
        while (this->table[ind].key != key && i < this->table.size()) {
            ind = (first_ind + probe(i)) % this->table.size();
        }

        if (this->table[ind].key == key && !this->table[ind].empty) {
            this->table[ind].empty = true;
            this->table[ind].key = "";
        }
        else {
            cout << "Chave nao encontrada" << endl;
        }
    }
    int sch(string key) {
        int ind = hash(key);
        int first_ind = ind;
        int i = 0;
        while (this->table[ind].key != key && i < this->table.size()) {
            ind = (first_ind + probe(i)) % this->table.size();
        }
        cout << key << ' ';
        if (this->table[ind].key == key && !this->table[ind].empty) {
            cout << ind << endl;
        }
        else {
            cout << -1 << endl;
        }
        return ind;
    }
};

int main() {

    int m;
    cin >> m;
    HashTable table(m);

    string comando;
    do {
        cin >> comando;
        if (comando == "add") {
            string key;
            cin >> key;
            table.add(key);
        }
        else if (comando == "sch") {
            string key;
            cin >> key;
            table.sch(key);
        }
        else if (comando == "rmv") {
            string key;
            cin >> key;
            table.rmv(key);
        }

    } while (comando != "fim");

    return 0;
}
