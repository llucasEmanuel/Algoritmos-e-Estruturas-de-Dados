#include <iostream>
#include <cmath>
#include <vector>
#define endl '\n'
#define lli long long int

using namespace std;

class PriorityQueue { // heap minima bottom up
private:
    int size;
    vector<lli> heap;

    void heapify() {
        lli lim = floor(this->size / 2);
        for (lli i = lim; i >= 1; i--) {
            lli k = i;
            lli v = this->heap[k];
            while (2*k <= this->size) {
                lli j = 2*k;
                if (j < this->size) {
                    if (this->heap[j] >= this->heap[j+1]) {
                        j++;
                    }
                }
                if (v < this->heap[j]) {
                    break;
                }
                else {
                    this->heap[k] = this->heap[j];
                    k = j;
                }
            }
            this->heap[k] = v;
        }
    }
public:
    PriorityQueue(const vector<lli> &vet) {
        this->size = vet.size();
        this->heap.emplace_back();	
        for (auto &i : vet) {
            this->heap.emplace_back(i);
        }
        this->heapify();
    }
    void insert(lli v) {
        this->size++;
        this->heap[this->size] = v;
        this->heapify();
    }
    lli find_min() {
        if (this->size > 0) {
            return this->heap[1];
        }
        else {
            return -1;
        }
    }
    lli delete_min() {
        if (this->size > 0) {
            lli min = this->heap[1];
            this->heap[1] = this->heap[this->size];
            this->size--;
            this->heapify();
            return min;
        }
        else {
            return -1;
        }
    }
    void heapsort() {
        while (this->size > 0) {
            lli el = this->delete_min();
            cout << el << ' ';
        }
        cout << endl;
    }
    void print_heap() {
        for (lli i = 1; i <= this->size; i++) {
            cout << this->heap[i] << ' ';
        }
        cout << endl;
    }
    lli get_cost() {
        vector<lli> costs(this->size);
        lli sum = 0;
        while (this->size > 1) {
            lli cost = this->delete_min() + this->delete_min();
            this->insert(cost);
            sum += cost;
            //cout << cost << ' ';
        }
        //cout << endl;
        return sum;
    }
};

int main() {

    lli val;
    while (cin >> val) {
        if (val > 0) {
            vector<lli> vet(val);
            for (lli i = 0; i < val; i++) { // preenche o vetor
                cin >> vet[i];
            }
            PriorityQueue heap(vet);
            //heap.print_heap();
            cout << heap.get_cost() << endl;
            //heap.print_heap();

        }
        else {
            break;
        }
    }

    return 0;
}
