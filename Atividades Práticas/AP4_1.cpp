#include <iostream>
#define endl '\n'
#define lli long long int

// CORRIGIR IMPLEMENTAÇÃO

using namespace std;

template <typename T> struct Node {
    T value;
    Node *next;
};

template <typename T> class LinkedList {
private:
    Node<T> *head;
    int curr;
    int size;
public:
    LinkedList() { // inicializa a lista como vazia
        this->head = nullptr;
        this->curr = 0;
        this->size = 0;
    };
    ~LinkedList() { // deleta os ponteiros
        Node<T> *curr = this->head;
        Node<T> *nextNode;
        while (curr != nullptr) {
            nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }
    void insert(T value) {
        if (this->head != nullptr) {
            Node<T> *curr = this->head;
            int count = 0;
            while (count < this->curr) {
                curr = curr->next; // move o ponteiro pro cursor
                count++;
            }
            // count termina com o indice do cursor
            Node<T> *newNode = new Node<T>;
            newNode->value = value;
            newNode->next = curr->next;
            curr->next = newNode; 
            this->size++;
        }
        else { // se tiver vazio
            this->head = new Node<T>;
            this->head->value = value;
            this->head->next = nullptr; // nullptr pq é o ultmo node da lista
            this->size++;
        }
    }
    T remove() {
        if (this->head != nullptr && this->size > 0 && this->curr < this->size - 1) { // se a lista nao estiver vazia
            Node<T> *curr = this->head;
            int count = 0;
            while (count < this->curr - 1) { 
                curr = curr->next;
                count++;
            }
            // curr aponta pro node anterior ao do cursor
            Node<T> *removedNode = curr->next;
            T removedValue = removedNode->value;
            curr->next = curr->next->next;

            delete removedNode;

            this->size--;
            return removedValue;
        }
        else {
            return T();
        }
    }
    int count(T value) {
        Node<T> *curr = this->head;
        int count = 0;
        while (curr != nullptr) {
            if (curr->value == value) {
                count++;
            }
            curr = curr->next;
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

    LinkedList<int> lista;

    int casos;
    cin >> casos;
    for (int i = 0; i < casos; i++) {
        int operacoes;
        cin >> operacoes;
        for (int j = 0; j < operacoes; j++) {
            string comando;
            cin >> comando;
            if (comando == "insert") {
                int value;
                cin >> value;
                lista.insert(value);
            }
            else if (comando == "remove") {
                lista.remove();
            }
            else if (comando == "count") {
                int value;
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
