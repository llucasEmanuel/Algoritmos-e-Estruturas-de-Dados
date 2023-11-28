#include <iostream>
#define endl '\n'

using namespace std;

template <typename T> class table_node {
public:
    bool empty;
    T value;
};

class Dictionary {
private:
    int table_size; // m
    table_node<string> *hash_table = new table_node<string>[this->table_size];
    // desalocar no destrutor
    int hash(string str) { // fold
        int sum = 0;
        for (int i = 0; i < str.size(); i++) {
            sum += str[i];
        }
        return abs(sum) % (this->table_size);
    }
    int linearProbing(int hash) { 
        int first_hash = hash;
        do{ 
            hash++; // incrementa primeiro (garante q n caia no if na primeira iteracao)
            if (hash == first_hash) {
                return -1;
            }
        } while (!this->hash_table[hash].empty);
        return hash;
    }
public:
    void setTableSize(int size) {
        this->table_size = size;
    }
    void add(string str) {
        int ind = hash(str);
        while (!this->hash_table[ind].empty) {
            ind = linearProbing(ind);
        }
        this->hash_table[ind].value = str;
        this->hash_table[ind].empty = false;
    }
    void remove(string str) {
        int ind = hash(str);
        if (this->hash_table[ind].value == str) {
            this->hash_table[ind].empty = true;
            this->hash_table[ind].value = "";
            //usa a flag para deixar o espaco disponivel
        }
        else {
        
        }
    }
    string search(string str) {
        int ind = hash(str);
        if (this->hash_table[ind].value == str) {
            return this->hash_table[ind].value;
        }
        else { //linear probing
        // se n tivesse o elemento seria um loop infinito
        // Lista tabela[5]
        }
    }
};

int main() {



    return 0;
}
