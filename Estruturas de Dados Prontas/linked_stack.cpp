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
        this->clear();
    }
    void clear() {
        Node<T> *temp = this->top;
        while (temp != nullptr) {
            Node<T> *removed = temp;
            temp = temp->next;
            delete removed;
        }
        this->top = nullptr;
        this->size = 0;
    }
    void print() {
        Node<T> *temp = this->top;
        while (temp != nullptr) {
            cout << temp->value << ' ';
            temp = temp->next;
        }
        cout << "(size = " << this->size <<  ')' << endl;

    }
    void push (T value) {
        Node<T> *newNode = new Node<T>;
        newNode->value = value;
        newNode->next = this->top;
        this->top = newNode;
        this->size++;
    }
    T pop() {
        Node<T> *removedNode = this->top;
        T removedValue = this->getTop();
        this->top = this->top->next;
        delete removedNode;
        this->size--;
            
        return removedValue;
    }
    T getTop() {
        return this->top->value;
    }
    bool empty() {
        if (this->size == 0) {
            return true;
        }
        else {
            return false;
        }
    }
    int getSize() {
        return this->size;
    }
    
};

int main() {

    Stack<int> stack;
    string comando;
    while (cin >> comando) {
        if (comando == "push") {
            int value;
            cin >> value;
            stack.push(value);
            stack.print();
        }
        else if (comando == "pop") {
            if (!stack.empty()) {
                stack.pop();
            }
            stack.print();
        }
        else if (comando == "empty") {
            cout << stack.empty() << endl;
        }
        else if (comando == "top") {
            if (!stack.empty()) {
                cout << stack.getTop() << endl;
            }
        }
        else if (comando == "clear") {
            if (!stack.empty()) {
                stack.clear();
                stack.print();
            }
        }
    }

    return 0;
}
