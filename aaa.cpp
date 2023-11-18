#include <iostream>
#define endl '\n'

using namespace std;

template <typename T> struct Node {
    T value;
    Node<T> *next;
};

template <typename T> class Stack {
private:
    Node<T> *top;
    int size;
public:
    Stack() {
        this->top = nullptr;
        this->size = 0;
    }
    ~Stack() {

    }
    void push (T value) {
        Node<T> *newNode = new Node<T>;
        newNode->next = this->top;
        this->top = newNode;
        this->size++;
    }
    T pop() {
        if (!this->empty()) {
            Node<T> *removedNode = this->top;
            T removedValue = this->top();
            this->top = this->top->next;
            delete removedNode;

            return removedValue
        }
        else {
            return T();
        }
    }
    T top() {
        if (!this->empty()) {
            return this->top->value;
        }
        else {
            return T();
        }
    }
    bool empty() {
        if (this->size == 0) {
            return true;
        }
        else {
            return false;
        }
    }
    int size() {
        return this->size;
    }
    
};

int main() {

    Stack<int> stack;
    string comando

    return 0;
}
