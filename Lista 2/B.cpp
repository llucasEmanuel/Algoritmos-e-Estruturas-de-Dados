#include <iostream>
#define endl '\n'

using namespace std;

template <typename T> class Node {
public:
    T value;
    Node<T> *next;
    Node<T> *prev;
};

template <typename T> class DoublyLinkedList {
private:
    Node<T> *head;
    Node<T> *curr;
    Node<T> *tail;
    int size;
public:
    DoublyLinkedList() {
        this->head = new Node<T>; // aloca o header;
        this->head->next = nullptr;
        this->head->prev = nullptr;
        this->curr = this->head;
        this->tail = this->head;
        this->size = 0;
    }
    ~DoublyLinkedList() {
        Node<T> *temp = this->head;
        while (temp != nullptr) {
            Node<T> *removed = temp;
            temp = temp->next;
            delete removed;
        }
    }
    void insert(T value) {
        Node<T> *newNode = new Node<T>;
        newNode->value = value;
        newNode->next = this->curr->next;
        newNode->prev = this->curr;
        this->curr->next = newNode;
        this->curr->next->prev = newNode;
        if (this->tail == this->curr) {
            this->tail = this->curr->next;
        }
        this->size++;
    }
    void append(T value) {
        Node<T> *newNode = new Node<T>;
        newNode->value = value;
        newNode->next = nullptr;
        newNode->prev = this->tail;

        if (this->tail != nullptr) {
            this->tail->next = newNode;
        }
        else {
            this->head->next = newNode;
        }

        this->tail = newNode;
        this->size++;
    }
    void remove() {
        if (this->curr->next == nullptr) { // nao ha elemento a direita do curr
            return;
        }
        Node<T> *temp = this->curr->next;
        if (this->tail == this->curr->next) { // remove do ultimo elemento
            this->tail = this->curr;
        }
        this->curr->next = this->curr->next->next;

        if (this->curr->next != nullptr) {
            this->curr->next->prev = this->curr;
        }
        delete temp;
        this->size--;
    }
    // Piores casos
    // - A(ABC)BC -> cursor aponta pro A e dps tem o BC (move o cursor pra tras)
    // - AB(ABC)C -> cursor aponta pro B e dps tem o C, mas antes tem o A (move o cursor duas vezes pra tras)
    void removeABC() {
        this->curr = this->head; // volta o cursor pro header (checa o proximo elemento -> comeca pelo primeiro)
        while (this->curr->next != nullptr && this->curr->next->next != nullptr && this->curr->next->next->next != nullptr) {
            if (this->curr->next->value == 'A' && this->curr->next->next->value == 'B' && this->curr->next->next->next->value == 'C') {
                this->remove(); // remove A
                this->remove(); // remove B
                this->remove(); // remove C
                if (this->curr->value == 'A') { 
                    this->prev();
                }
                if (this->curr->value == 'B' && this->curr->prev->value == 'A') {
                    this->prev();
                    this->prev();
                }
            }
            else {
                this->next();
            }
        }
    }
    void prev() {
        if (this->curr->prev != nullptr)
            this->curr = this->curr->prev;
    }
    void next() {
        if (this->curr->next != nullptr)
            this->curr = this->curr->next;
    }
    void print() {
        Node<T> *temp = this->head->next;
        while (temp != nullptr) {
            cout << temp->value;
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {

    string str;
    cin >> str;
    // sempre deve ser removido primeiro o "ABC" mais a esquerda
    DoublyLinkedList<char> list;
    for (int i = 0; i < str.length(); i++) {
        list.append(str[i]);
    }
    list.removeABC();
    list.print();


    return 0;
}
