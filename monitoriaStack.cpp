#include <iostream>
#include <string>

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
    void push(T value) {
        Node<T> *newNode = new Node<T>;
        newNode->value = value;
        newNode->next = this->top;
        this->top = newNode;
        this->size++;
    }
    T pop() {
        Node<T> *removed = this->top;
        T removedValue = this->getTop();
        this->top = this->top->next;
        delete removed;

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

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string lista;
        cin >> lista;
        Stack<char> operadores;
        string result = ""; // inicializa como string vazia
        // iterar por todos os char da string
        for (int j = 0; j < lista.length(); j++) {
            if (lista[j] == ')') { // checa apenas quando fecha parenteses
                char op = operadores.pop();
                result.push_back(op);
            }
            else if (lista[j] == '+' || lista[j] == '-' || lista[j] == '*' || lista[j] == '/' || lista[j] == '^') {
                operadores.push(lista[j]);
            }
            else if (lista[j] != '(') {
                result.push_back(lista[j]);
            }
        }
        cout << result << endl;
    }

    return 0;
}
