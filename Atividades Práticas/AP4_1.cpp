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
        this->clear();
        delete this->header; // desaloca o header (n vai mais usar)
    }
    void clear() {
        Node<T> *temp = this->header->next; // temp aponta pro primeiro elemento
        while (temp != nullptr) {
            Node<T> *removed = temp;
            temp = temp->next;
            delete removed;
        }
        this->header->next = nullptr;
        this->size = 0;
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
        this->tail = newNode; // o node add eh a cauda agora

        this->size++;
    }
    T remove() { // remove o this->curr->next (a direita do cursor)
        if (this->curr->next == nullptr) { // se nao houver elemento a direita do cursor
            return T();
        }
        T removedValue = this->curr->next->value;
        Node<T> *temp = this->curr->next;

        if (this->tail == this->curr->next) { // removendo o ultimo elemento
            this->tail = this->curr;
        }
        this->curr->next = this->curr->next->next;
        
        delete temp;
        this->size--;

        return removedValue;
    }
    void moveToStart() {
        this->curr = this->head;
    }
    void moveToEnd() {
        this->curr = this->tail;
    }
    void prev() {
        if (this->curr != this->head) {
            Node<T> *temp = this->head;
            while (temp->next != this->curr) { // sai do loop quando o temp tiver no anterior ao curr
                temp = temp->next;
            }
            this->curr = temp;
        }    
    }
    void next() {
        if (this->curr != this->tail) {
            this->curr = this->curr->next;
        }
    }
    int length() {
        return this->size;
    }
    int currPos() {
        Node<T> *temp = this->head;
        int count = 0;
        while (temp != this->curr) {
            temp = temp->next;
            count++;
        }

        return count;
    }
    void moveToPos(int pos) {
        Node<T> *temp = this->head;
        int count = 0;
        while (count != pos && temp != nullptr) {
            temp = temp->next;
            count++;
        }
        this->curr = temp;
    }
    T getValue() {
        if (this->curr->next != nullptr) { // nao for vazio
            return this->curr->next->value;
        }
        return T();
    }
    void print() {
        Node<T> *temp = this->head->next;
        while (temp != nullptr) {
            cout << temp->value << ' ';
            temp = temp->next;
        }
        cout << endl;
    }
    int count (T value) {
        Node<T> *temp = this->head->next;
        int count = 0;
        while (temp != nullptr) {
            if (temp->value == value) {
                count++;
            }
            temp = temp->next;
        }
        return count;
    }
};

int main() {

    LinkedList<int> list;

    int casos;
    cin >> casos;
    for (int i = 0; i < casos; i++) {
        cout << "Caso " << i+1 << ":\n";
        int operacoes;
        cin >> operacoes;
        for (int j = 0; j < operacoes; j++) {
            string comando;
            cin >> comando;
            if (comando == "insert") {
                int value;
                cin >> value;
                list.insert(value);
            }
            else if (comando == "remove") {
                list.remove();
            }
            else if (comando == "count") {
                int value;
                cin >> value;
                cout << list.count(value) << endl;
            }
            else if (comando == "next") {
                list.next();
            }
            else if (comando == "prev") {
                list.prev();
            }
        }
    }

    return 0;
}
