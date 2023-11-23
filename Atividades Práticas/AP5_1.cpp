#include <iostream>

#define endl '\n'

using namespace std;

template <typename T> class Node {
public:
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
        Node<T> *temp = this->top;
        while (temp != nullptr) {
            Node<T> *removed = temp;
            temp = temp->next;
            delete removed;
        }
    }
    void push(T value) {
        Node<T> *newTop = new Node<T>;
        newTop->value = value;

        newTop->next = this->top;
        this->top = newTop;
        
        this->size++;
    }
    int popN(int n) {
        if (n <= this->size) {
            int sum = 0;
            for (int i = 0; i < n; i++) {
                sum += this->pop();
            }
            return sum;
        }
        else {
            return -1;
        }
    }
    T pop() {
        if (this->top != nullptr) {
            T removed = this->top->value;
            Node<T> *temp = this->top;
            this->top = this->top->next;
            delete temp;

            this->size--;
            return removed;
        }
        else return T();
    }
};

int main() {

    Stack<int> stack;
    int casos;
    cin >> casos;
    string comando;
    for (int i = 0; i < casos; i++) {
        cout << "Caso " << i+1 << ':' << endl;
        do {
            cin >> comando;
            if (comando != "end") {
                if (comando == "push") {
                    int value;
                    cin >> value;
                    stack.push(value);
                }
                else if (comando == "pop") {
                    int n;
                    cin >> n;
                    cout << stack.popN(n) << endl;
                }
            }
        }
        while (comando != "end");
    }

    return 0;
}
