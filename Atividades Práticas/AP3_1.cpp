#include <iostream>

#define endl '\n'
#define lli long long int

using namespace std;

template <typename any> class List {
private:
    any *array_list;
    int curr;
    int size;

    void resize(int new_size) {
        if (this->array_list == nullptr) {
            this->array_list = new any[new_size];
        } 
        else {
            any *temp = new any[this->size]; // cria array temporario
            for (int i = 0; i < this->size; i++) { // copia os elementos
                temp[i] = this->array_list[i];
            }
            this->array_list = nullptr; // reinicializa o array do objeto
            this->array_list = new any[new_size]; // aloca ele com o novo tamanho

            int smallest_size = (this->size < new_size) ? this->size : new_size; // evita invasao de momeoria se o novo tamanho for menor
            for (int i = 0; i < smallest_size; i++) { // copia de volta os elementos
                this->array_list[i] = temp[i];
            }
            this->size = new_size; // atualiza o tamanho
            delete[] temp; // deleta o array temporario
        }
    }
public:
    List() { // construtor
        this->array_list = nullptr;
        this->curr = 0; // cursor inicia no primeiro elemento
        this->size = 0;
    }
    ~List() { // destrutor (desaloca automaticamente quando o sair do escopo do objeto)
        if (this->array_list != nullptr) {
            delete[] this->array_list;
        } 
    }

    void insert(any value) {
        this->resize(this->size + 1);
        this->size++;

        for (int i = this->size - 1; i > this->curr; i--) { // abre espaco no ind do cursor
            this->array_list[i] = this->array_list[i-1];
        }
        this->array_list[this->curr] = value;
    }

    void remove() {
        // remove o elemento apontado pelo cursor
        for (int i = this->curr; i < this->size - 1; i++) { // move os elementos para a esquerda a partir do cursor
            this->array_list[i]  = this->array_list[i+1];
        }
        this->resize(this->size - 1);
        this->size--;

        if (this->curr >= this->size) {
            this->curr = this->size - 1;
        }
        else if (this->curr < 0) {
            this->curr = 0;
        }
    }

    int count(any value) {
        int count = 0;
        for (int i = 0; i < this->size; i++) {
            if (this->array_list[i] == value) {
                count++;
            }
        }
        return count;
    }

    void prev() {
        if (this->curr > 0) {
            this->curr--;
        }
    }

    void next() {
        if (this->curr < this->size - 1) {
            this->curr++;
        }
    }
};

int main() {

    List<lli> lista;

    int casos;
    cin >> casos;
    for (int i = 0; i < casos; i++) {
        cout << "Caso " << i+1 << ":" << endl;
        int operacoes;
        cin >> operacoes;
        for (int j = 0; j < operacoes; j++) {
            string comando;
            cin >> comando;
            if (comando == "insert") {
                lli value;
                cin >> value;
                lista.insert(value);
            }
            else if (comando == "remove") {
                lista.remove();
            }
            else if (comando == "count") {
                lli value;
                cin >> value;
                cout << lista.count(value) << endl;
            }
            else if (comando == "prev") {
                lista.prev();
            }
            else if (comando == "next") {
                lista.next();
            }
        }
    }

    return 0;
}
