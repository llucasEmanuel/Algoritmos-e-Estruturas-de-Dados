#include <iostream>
#define endl '\n'

using namespace std;

template <typename T> struct Node {
    T value;
    Node<T> *next;
};

template <typename T> class Queue {
private:
    Node<T> *front;
    Node<T> *rear;
    int size;
public:
    Queue() {
        this->front = new Node<T>; // aloca um header
        this->front->next = nullptr;
        this->rear = this->front;
        this->size = 0;
    }
    ~Queue() {
        this->clear();
        delete this->front;
    }
    void clear() {
        while (this->size > 0) {
            this->dequeue();
        }
    }
    void enqueue(T value) { // add no rear
        this->rear->next = new Node<T>;
        this->rear = this->rear->next;
        this->rear->value = value;
        this->rear->next = nullptr;
        this->size++;
    }
    T dequeue() {
        if (this->size > 0) { // remove no front
            Node<T> *temp = this->front->next;
            T removed = temp->value;
            this->front->next = this->front->next->next;
            
            if (this->front->next == nullptr) { // o rear taria apontando pro node removido
                // para n perder o endereco do rear
                this->rear = this->front;
            }
            delete temp;
            this->size--;

            return removed;
        }
        return T();
    }
    T frontValue() {
        if (this->size > 0) {
            return this->front->next->value;
        }
        else {
            return T();
        }
    }
    int length() {
        return this->size;
    }
    void print() {
        Node<T> *temp = this->front->next;
        while (temp != nullptr) {
            cout << temp->value << ' ';
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {

    Queue<int> queue;

    string comando;
    while (cin >> comando) {
        if (comando == "enqueue") {
            int value;
            cin >> value;
            queue.enqueue(value);
        }
        else if (comando == "dequeue") {
            if (queue.length() > 0)
                queue.dequeue();
        }
        else if (comando == "frontValue") {
            if (queue.length() > 0)
                cout << queue.frontValue() << endl;
        }
        else if (comando == "length") {
            cout << queue.length() << endl;
        }
        else if (comando == "clear") {
            queue.clear();
        }
        queue.print();
    }

    return 0;
}
