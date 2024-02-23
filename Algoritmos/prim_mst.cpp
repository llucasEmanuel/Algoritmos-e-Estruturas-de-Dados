#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <algorithm>
#define endl '\n'
// Considerar um grafo de até 10^5 vertices e arestas de 0 a 10^2
// Logo a maior soma possivel de custo de arestas é 10^5 * 10^2 = 10^7
// "Infinito" = 10^7 + 1
#define INF 10000001

using namespace std;

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

};

// tripla ordenada
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

void Prim(Graph &g,  vector<int> &dist, vector<int> &pred) {
    for (int i = 0; i < g.n(); i++) {
        dist[i] = INF; // distancia de peso acumulado "infinito"
        pred[i] = -1; // -1 marca como vazio
        g.set_mark(i, false);
    }

    priority_queue<Triple, vector<Triple>, CompareTriple> heap;
    heap.push(Triple(0, 0, 0)); dist[0] = 0;
    for (int i = 0; i < g.n(); i++) {
        Triple t; // inicializou tudo com 0 por padrão
        while(true) {
            if (heap.empty()) return; // encerra a execução do algoritmo
            if (g.get_mark(t.second) == false) break;
            t = heap.top(); // atribui o topo
            heap.pop();
        }
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
    Graph g(5);
    vector<int> dist(g.n()); // vetor de distancias
    vector<int> pred(g.n()); // vetor de predecessores
    g.add_edge(0, 1, 10);
    g.add_edge(0, 3, 20);
    g.add_edge(0, 2, 3);
    g.add_edge(1, 3, 5);
    g.add_edge(2, 1, 2);
    g.add_edge(2, 4, 15);
    g.add_edge(3, 4, 11);
    
    Prim(g, dist, pred);
    
    for (int i : dist) {
        cout << i << ' ';
    }
    cout << endl;
    for (int i : pred) {
        cout << i << ' ';
    }
    cout << endl;

  
    return 0;
}
