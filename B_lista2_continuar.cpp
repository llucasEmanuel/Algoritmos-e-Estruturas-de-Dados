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
        
    }
};
// Piores casos
// - A(ABC)BC -> cursor aponta pro A e dps tem o BC (move o cursor pra tras)
// - AB(ABC)C -> cursor aponta pro B e dps tem o C, mas antes tem o A (move o cursor duas vezes pra tras)

int main() {

    string str;
    cin >> str;
    // sempre deve ser removido primeiro o "ABC" mais a esquerda

    return 0;
}
