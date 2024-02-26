#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#define endl '\n'
#define INF 2000001 //2x10^4x10^2 = 2x10^6

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

class Triple {
public:
    int p; // parent
    int v; // vertex
    int w; // weight

    Triple(int a=0, int b=0, int c=0) {
        this->p = a;
        this->v = b;
        this->w = c;
    }
};

struct CompareTriple {
    bool operator() (Triple &t1, Triple &t2) {
        return t1.w > t2.w;
    }
};

void Dijkstra(Graph &g, int s, vector<int> &dist) {
    vector<int> pred(g.n());
    for (int i = 0; i < g.n(); i++) {
        dist[i] = INF;
        pred[i] = -1; // -1 marca o vazio
        g.set_mark(i, false);
    }
    priority_queue<Triple, vector<Triple>, CompareTriple> heap;
    heap.push(Triple(s, s, 0)); dist[s] = 0;
    for (int i = 0; i < g.n(); i++) {
        Triple t;
        do {
            if (heap.empty()) return;
            t = heap.top();
            heap.pop();
        } while (g.get_mark(t.v) == true);
        g.set_mark(t.v, true);
        pred[t.v] = t.p;
        int w = g.first(t.v);
        while (w < g.n()) {
            if (g.get_mark(w) != true && dist[w] > dist[t.v] + g.weight(t.v, w)) {
                dist[w] = dist[t.v] + g.weight(t.v, w);
                heap.push(Triple(t.v, w, dist[w]));
            }
            w = g.next(t.v, w);
        }
    }
}

int main() {

    int c; // casos
    cin >> c;
    for (int i = 0; i < c; i++) {
        int v, a;
        cin >> v >> a; // vertices e arestas
        Graph g(v);
        for (int j = 0; j < a; j++) {
            int v1, v2, wt;
            cin >> v1 >> v2 >> wt;
            g.add_edge(v1, v2, wt);
        }
        int s;
        cin >> s;
        cout << "Caso " << i+1 << endl;
        vector<int> dist(g.n());
        Dijkstra(g, s, dist);
        for (int j = 0; j < g.n(); j++) {
            if (dist[j] == INF) {
                cout << -1 << endl;
            } 
            else {
                cout << dist[j] << endl;
            }
        }
    }

    return 0;
}
