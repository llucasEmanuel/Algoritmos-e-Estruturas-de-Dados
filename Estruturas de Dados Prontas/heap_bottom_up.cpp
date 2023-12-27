#include <iostream>
#include <cmath>
#include <vector>
#define endl '\n'

using namespace std;

//BOTTOM UP // ja conhece todos os elementos de antemao
template <typename T> class PriorityQueue { // implementado como heap
private:
    int size;
    vector<T> heap;

    void heapify() {
        int lim = floor(this->size / 2);
        for (int i = lim; i >= 1; i--) {
            int k = i;
            T v = this->heap[k];
            while (2*k <= this->size) { // enquanto k for ind de um node interno
                int j = 2*k;
                if (j < this->size) { // existe filho a direita
                    if (this->heap[j] < this->heap[j+1]) {
                        j++; // seleciona o maior filho
                    }
                }
                if (v >= this->heap[j]) { // subarvore ja eh uma heap
                    break;
                }
                else { // copia o maior filho para rt
                    this->heap[k] = this->heap[j];
                    k = j;
                }
            }
            this->heap[k] = v;
        }
    }
    
public:
    PriorityQueue(const vector<T> &vec) { // construtor
        this->size = vec.size();
        this->heap.emplace_back(); // add o primeiro elemento qualquer na heap
        for (auto &i : vec) {
            this->heap.emplace_back(i);
        }
        this->heapify();
    }
    T find_max() {
        if (this->size > 0) {
            return this->heap[1];
        }
        else {
            return T();
        }
    }
    T delete_max() {
        if (this->size > 0) {
            T max = this->heap[1];
            this->heap[1] = this->heap[this->size]; // troca o maior com a ultima folha
            this->size--;
            this->heapify();
            return max;
        }
        return T();
    }
    void heapsort() {
        while (this->size > 0) {
            T el = this->delete_max();
            cout << el << ' ';
        }
        cout << endl;
    }
    void print_heap() { // printa na forma que o array eh organizado
        for (int i = 1; i <= this->size; i++) {
            cout << this->heap[i] << ' ';
        }
        cout << endl;
    }
};

int main() {

    vector<int> vec = {3, 1, 2, 7, 5,};
    PriorityQueue<int> heap(vec);
    heap.print_heap();
    heap.heapsort(); 

    return 0;
}
