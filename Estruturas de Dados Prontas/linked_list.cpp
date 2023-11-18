#include <iostream>
#define endl '\n'

using namespace std;

template <typename T> struct Node {
    T value;
    Node<T> *next;
};

template <typename T> class LinkedList {
private:
    Node<T> *head; // aponta pro header
    Node<T> *curr; // aponta pro node onde esta o cursor
    Node<T> *tail; // aponta pra cauda da lista
    Node<T> *header; // node vazio que todos apontam (nao conta como elemento)
    int size;
public:
    LinkedList() { // construtor
        this->header = new Node<T>;
        this->head = this->header;
        this->curr = this->header;
        this->tail = this->header;
        this->size = 0;
        this->header->next = nullptr;
    }
    ~LinkedList() { // destrutor

    }
    void clear() {

    }
    void insert(T value) {
        Node<T> *newNode = new Node<T>;
        newNode->value = value;
        newNode->next = this->curr->next;
        this->curr->next = newNode;
        if (this->tail == this->curr) { // se inserir no ultimo tem que mover a cauda
            this->tail = this->curr->next;
        }
        this->size++;
    }
    void append(T value) {
        Node<T> *newNode = new Node<T>;
        newNode->value = value;
        newNode->next = nullptr;
        this->tail->next = newNode;
    }
    T remove() { // remove o this->curr->next (a direita do cursor)
        if (this->curr->next == nullptr) { // se nao houver elemento a direita do cursor
            return nullptr;
        }
        T removedValue = this->curr->value;
        if (this->tail == this->curr->next) { // removendo o ultimo elemento
            this->tail = this->curr;
        }
        Node<T> *temp = this->curr->next;
        this->curr->next = this->curr->next->next;
        
        delete temp;
        this->size--;

        return removedValue;
    }
    void moveToStart() {

    }
    void moveToEnd() {

    }
    void prev() {

    }
    void next() {

    }
    int length() {
        return 1;
    }
    int currPos() {
        return 1;
    }
    void moveToPos(int pos) {

    }
    T getValue() {

    }
};

int main() {



    return 0;
}
