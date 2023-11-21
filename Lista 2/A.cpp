#include <iostream>
#define endl '\n'

using namespace std;

template <typename T> struct Node {
    T value;
    Node<T> *next;
};

template <typename T> class List {
private:
    Node<T> *head;
    Node<T> *curr;
    Node<T> *tail;
    int size;
public:
    List() {
        this->head = new Node<T>; // aloca o header
        this->head->next = nullptr; // header aponta pra nullptr
        this->curr = this->head;
        this->tail = this->head;
        this->curr_backup = this->curr;
        this->size = 0;
    }
    ~List() {
        this->clear();
        delete this->head;
    }
    void clear() {
        Node<T> *temp = this->head->next;
        while (temp != nullptr) {
            Node<T> *remove = temp;
            temp = temp->next;
            delete remove;
        }
        this->head->next = nullptr;
        this->curr = this->head;
        this->tail = this->head;
        this->size = 0;
    }
    void insert(T value) { // dar fazer o cursor seguir as insercoes
        Node<T> *newNode = new Node<T>;
        newNode->value = value;
        newNode->next = this->curr->next;
        this->curr->next = newNode;
        if (this->tail == this->curr) { // se inserir no ultimo tem que mover a cauda
            this->tail = this->curr->next;
        }
        this->curr = newNode; // move o cursor para o node inserido
        this->size++;
    }
    void currToHome() {
        this->curr = this->head;
    }
    void currBackToPlace() {
        this->curr = this->tail;
    }
    int len() {
        return this->size;
    }
    void print() {
        Node<T> *temp = this->head->next;
        while (temp != nullptr) {
            cout << temp->value;
            temp = temp->next;
        } cout << '\n';
    }
};

int main() {

    List<char> texto;

    string linha;
    while (cin >> linha) {
        for (int i = 0; i < linha.size(); i++) { // passa por todos os char da string
            if (linha[i] == '[') {
                texto.currToHome();
            }
            else if (linha[i] == ']') {
                texto.currBackToPlace();
            }
            else {
                texto.insert(linha[i]);
            }
        }
        texto.print();
        texto.clear();
    }

    return 0;
}
