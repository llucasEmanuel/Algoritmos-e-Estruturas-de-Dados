#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <algorithm>
#define endl '\n'
// 5x10^4 arestas e 10^4 peso max
// 5x10^8 max -> int resolve
#define INF 500000001

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
        return -1;
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

void Dijkstra(Graph &g, int s, vector<int> &dist) {
    vector<int> pred(g.n()); // vetor de predecessores
    for (int i = 0; i < g.n(); i++) {
        dist[i] = INF; // distancia de peso acumulado "infinito"
        pred[i] = -1; // -1 marca como vazio
        g.set_mark(i, false);
    }

    priority_queue<Triple, vector<Triple>, CompareTriple> heap;
    heap.push(Triple(s, s, 0)); dist[s] = 0;
    while (!heap.empty()) {
        Triple t = heap.top(); // atribui o topo
        heap.pop();
        if (g.get_mark(t.second) == true) continue;
        g.set_mark(t.second, true); 
        pred[t.second] = t.first;
        int w = g.first(t.second);
        while (w < g.n()) {
            if (g.get_mark(w) != true && dist[w] > dist[t.second] + g.weight(t.second, w)) {
                dist[w] = dist[t.second] + g.weight(t.second, w);
                heap.push(Triple(t.second, w, dist[w]));
            }
            w = g.next(t.second, w);
        }
    }
}

int main() {

    int n;
    cin >> n; // num de casos teste
    for (int i = 0; i < n; i++) {
        int n, m, s, t;
        cin >> n >> m >> s >> t;
        Graph g(n);
        vector<int> dist(n);
        for (int j = 0; j < m; j++) {
            int s1, s2, w;
            cin >> s1 >> s2 >> w;
            g.add_edge(s1, s2, w);
            g.add_edge(s2, s1, w); // supor bidirecional
        }
        cout << "Case #" << i+1 << ": ";
        Dijkstra(g, s, dist);
        if (dist[t] == INF) {
            cout << "unreachable" << endl;
        }
        else {
            cout << dist[t] << endl;
        }

    }

    return 0;
}
