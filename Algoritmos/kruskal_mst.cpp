#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>
#define endl '\n'

using namespace std;

#define INF 10000001
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4

class Graph {
private:
    vector<list<pair<int, int>>> adj; // adjacency list (vertex, weight)
    vector<bool> mark;
    int num_edges;
public:
    Graph(int n) {
        this->adj.resize(n);
        this->mark.resize(n);
        this->num_edges = 0;
    }
    int n() {
        return this->mark.size(); // eh o mesmo q o numero de vertices
    }
    int e() {
        return this->num_edges;
    }
    void add_edge(int i, int j, int wt) {
        auto it = this->adj[i].begin();
        while (it != this->adj[i].end()) { // insercao ordenada
            if ((*it).first >= j) {
                break;
            }
            it++;
        }
        this->adj[i].insert(it, make_pair(j, wt));
    }
    int first(int v) {
        if (this->adj[v].empty()) return this->n();
        else return this->adj[v].front().first;
    }
    int next(int v, int w) {
        auto it = this->adj[v].begin();
        while (it != this->adj[v].end() && (*it).first < w+1) {
            it++;
        }
        if (it == this->adj[v].end()) {
            return this->n();
        }
        // it sai igual a w+1
        return (*it).first;
    }
    int weight(int i, int j) {
        auto it = this->adj[i].begin();
        while (it != this->adj[i].end()) {
            if ((*it).first == j) {
                return (*it).second;
            }
            it++;
        }
        return 0;
    }
    void set_mark(int v, bool val) {
        this->mark[v] = val;
    }
    int get_mark(int v) {
        return this->mark[v];
    }
    void print() {
        for (int i = 0; i < this->adj.size(); i++) {
            cout << i << ": ";
            for (auto it = this->adj[i].begin(); it != this->adj[i].end(); it++) {
                cout << (*it).first << ' ';
            }
            cout << endl;
        }
    }
};

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

class Triple { 
public:
    int first;
    int second;
    int third;

    Triple (int a=0, int b=0, int c=0) {
        this->first = a;
        this->second = b;
        this->third = c;
    }
};

// comparador para usar na priority queue
struct CompareTriple { // tem q ser struct
    bool operator() (Triple &a, Triple &b) {
        return a.third > b.third;
    }
};

void Kruskal(Graph &g1, Graph &g2) { // g2 é a mst
    priority_queue<Triple, vector<Triple>, CompareTriple> heap;
    for (int i = 0; i < g1.n(); i++) {
        int w = g1.first(i);
        while (w < g1.n()) {
            heap.push(Triple(i, w, g1.weight(i, w)));
            w = g1.next(i, w);
        } 
    }
    DisjointSubset ds(g1.n());
    int num_mst = g1.n();
    while (num_mst > 1) {
        Triple t = heap.top();
        heap.pop();
        if (ds.find(t.first) != ds.find(t.second)) {
            ds.unite(t.first, t.second);
            g2.add_edge(t.first, t.second, t.third);
            g2.add_edge(t.second, t.first, t.third);
            num_mst--;
        }
    }
}

int main() {

    Graph g(5);
    g.add_edge(A, B, 10);
    g.add_edge(B, A, 10);
    g.add_edge(A, C, 3);
    g.add_edge(C, A, 3);
    g.add_edge(A, D, 20);
    g.add_edge(D, A, 20);
    g.add_edge(B, C, 2);
    g.add_edge(C, B, 2);
    g.add_edge(B, D, 5);
    g.add_edge(D, B, 5);
    g.add_edge(C, E, 15);
    g.add_edge(E, C, 15);
    g.add_edge(D, E, 11);
    g.add_edge(E, D, 11);
    Graph mst(5);
    Kruskal(g, mst);
    mst.print();

    return 0;
}
