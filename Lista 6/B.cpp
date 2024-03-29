#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <tuple>
#include <algorithm>
#define endl '\n'
#define lli long long int
#define INF 5000000001 // 10^12 + 1

using namespace std;

class Graph {
private:
    vector<list<pair<int, lli>>> adj; // adjacency list (vertex, weight)
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
    void add_edge(int i, int j, lli wt) {
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
    lli weight(int i, int j) {
        auto it = this->adj[i].begin();
        while (it != this->adj[i].end()) {
            if ((*it).first == j) {
                return (*it).second;
            }
            it++;
        }
        return -1; // ausencia de aresta
    }
    void set_mark(int v, bool val) {
        this->mark[v] = val;
    }
    int get_mark(int v) {
        return this->mark[v];
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

void Prim(Graph &g,  vector<lli> &dist, vector<int> &pred) {
    for (int i = 0; i < g.n(); i++) {
        dist[i] = INF; // distancia de peso acumulado "infinito"
        pred[i] = -1; // -1 marca como vazio
        g.set_mark(i, false);
    }

    priority_queue<Triple, vector<Triple>, CompareTriple> heap;
    heap.push(Triple(0, 0, 0)); dist[0] = 0;
    for (int i = 0; i < g.n(); i++) {
        Triple t; // inicializou tudo com 0 por padrão
        do {
            if (heap.empty()) return; // encerra a execução do algoritmo
            t = heap.top(); // atribui o topo
            heap.pop();
        } while (g.get_mark(t.second) == true);
        g.set_mark(t.second, true); 
        pred[t.second] = t.first;
        int w = g.first(t.second);
        while (w < g.n()) {
            if (g.get_mark(w) != true && dist[w] > g.weight(t.second, w)) {
                dist[w] = g.weight(t.second, w);
                heap.push(Triple(t.second, w, dist[w]));
            }
            w = g.next(t.second, w);
        }
    }
}

int main() {

    int n, m;
    do {
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        Graph g(n);
        for (int i = 0; i < m; i++) {
            int v1, v2, w;
            cin >> v1 >> v2 >> w;
            if (g.weight(v1, v2) > w || g.weight(v1, v2) == -1) { // garante q vai add as menores arestas
                g.add_edge(v1, v2, w);
                g.add_edge(v2, v1, w);
            }
        }
        vector<lli> dist(g.n());
        vector<int> pred(g.n());
        Prim(g, dist, pred);
        // achar o maior valor de dist
        lli range = -1;
        for (int i = 0; i < dist.size(); i++) {
            if (pred[i] == -1) {
                range = -1;
                cout << "IMPOSSIBLE" << endl;
                break;
            }
            if (dist[i] > range) {
                range = dist[i];
            }
        }
        if (range != -1) {
            cout << range << endl;
        }

    } while (n != 0 || m != 0);

    return 0;
}
