#include <iostream>
#define endl '\n'

using namespace std;

template <typename T> struct Node {
    T value;
    Node<T> *next;
};

struct Parenteses {
    bool abriu;
    bool fechou;
};

template <typename T> class List {
private:
    Node<T> *head;
    Node<T> *curr;
    Node<T> *tail;
    int size;
public:
    List() {
        this->head = new Node<T>;
        this->head->next = nullptr;
        this->curr = this->head;
        this->tail = this->head;
        this->size = 0;
    }
    ~List() {
        this->clear();
        delete this->head;
    }
    void insert(T value) {
        Node<T> *newNode = new Node<T>;
        newNode->value = value;
        newNode->next = this->curr->next;
        this->curr->next = newNode;
        if (this->tail == this->curr) {
            this->tail = this->curr->next;
        }
        this->curr = this->curr->next;
        this->size++;
    }
    void print() {
        Node<T> *temp = this->head->next;
        while (temp != nullptr) {
            cout << temp->value << ' ';
            temp = temp->next;
        }
        cout << endl;
    }
    void clear() {
        Node<T> *temp = this->head->next;
        while (temp != nullptr) {
            Node<T> *remove = temp;
            temp = temp->next;
            delete remove;
        }
    }
};

int main() {

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        List<char> lista;
        char letra;
        while (cin >> letra) {
            lista.insert(letra);
            lista.print();
        }
    }

    return 0;
}