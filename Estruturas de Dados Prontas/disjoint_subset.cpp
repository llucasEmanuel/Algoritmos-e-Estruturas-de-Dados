class DisjointSubset {
private:
    vector<int> parent_arr;
public:

    DisjointSubset(int n) {
        vector<int> vet(n);
        for (int i = 0; i < n; i++) {
            vet[i] = i;
        }
        this->parent_arr = vet;
    }
    int find(int x) {
        if (this->parent_arr[x] == x) return x;
        this->parent_arr[x] = this->find(this->parent_arr[x]);
        return this->parent_arr[x];
    }
    void unite(int x, int y) {
        int r1 = this->find(x);
        int r2 = this->find(y);
        if (r1 != r2) this->parent_arr[r2] = r1;
    }
    void print() {
        for (int i : this->parent_arr) {
            cout << i << ' ';
        }
        cout << endl;
        for (int i = 0; i < 10; i++) {
            cout << i << ' ';
        }
        cout << endl;
    }
};
