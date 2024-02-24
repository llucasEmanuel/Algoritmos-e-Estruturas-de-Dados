#include <iostream>
#include <vector>
#include <queue>
#define endl '\n'
// Considerar um grafo de até 10^5 vertices e arestas de 0 a 10^2
// Logo a maior soma possivel de custo de arestas é 10^5 * 10^2 = 10^7
// "Infinito" = 10^7 + 1
#define INF 10000001

using namespace std;

class Graph { // unweighted digraph
private:
    vector<vector<int>> matrix;
    int num_edges;
    vector<bool> mark;

public:
    int n() {
        return this->mark.size(); // eh o mesmo q o numero de vertices
    }
    int e() {
        return this->num_edges;
    }
    int first(int v) {
        for (int i = 0; i < this->n(); i++) {
            if (this->matrix[v][i] != 0) return i;
        }
        return this->n();
    }
    int next(int v, int w) {
        for (int i = w+1; i < this->n(); i++) {
            if (this->matrix[v][i] != 0) return i;
        }
        return this->n();
    }
    void add_edge(int i, int j, int wt) {
        if (this->matrix[i][j] == 0) this->num_edges++;
        this->matrix[i][j] = wt;
    }
    void del_edge(int i, int j) {
        if (this->matrix[i][j] != 0) this->num_edges--;
        this->matrix[i][j] = 0;
    }
    void set_mark(int v, bool state) {
        this->mark[v] = state;
    }
    bool get_mark(int v) {
        return this->mark[v];
    }
    int weight(int v, int w) {
        return this->matrix[v][w];
    }
    void BFS(int start) {
        queue<int> q;
        q.push(start);
        this->set_mark(start, true);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            // previsit
            int w = this->first(v);
            while (w < this->n()) {
                if (this->get_mark(w) == false) {
                    this->set_mark(w, true);
                    q.push(w);
                }
                w = this->next(v, w);
            }
            // posvisit
        }
    }   
    int shortest_path(int start, int dest) { // menor caminho entre start e dest
        for (int v = 0; v < this->n(); v++) {
            this->set_mark(v, false);
        }
        vector<int> pred(this->n(), -1); // vetor de predecessores (inicializa tudo como -1)
        queue<int> q;
        this->set_mark(start, true); // visita o vertice de inicio
        q.push(start);
        while (!q.empty()) {
            int v = q.front();
            q.pop();

            // o previsit do vertice faz a checagem
            if (v == dest) { // encontrou um caminho
                // reconstruir o caminho
                int curr = v;
                int path_size = 0;
                while (curr != -1) {
                    path_size++;
                    curr = pred[curr]; 
                }
                return path_size - 1; // exclui o vertice da origem
            }

            int w = this->first(v);
            while (w < this->n()) { // enquanto houver vertices adjacentes a v
                if (this->get_mark(w) == false) {
                    this->set_mark(w, true);
                    q.push(w);
                    pred[w] = v; // marca o predecessor
                }
                w = this->next(v, w);
            }
        }
        return -1;
    }
    void graph_traverse() {
        for (int v = 0; v < this->n(); v++) {
            this->set_mark(v, false);
        }
        for (int v = 0; v < this->n(); v++) {
            if (this->get_mark(v) == false) {
                this->BFS(v);
            }
        }
    }
    Graph(int v) {
        this->matrix.resize(v);
        for (int i = 0; i < v; i++) {
            this->matrix[i].resize(v);
        }
        this->mark.resize(v);
        this->num_edges = 0;
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

void Dijkstra(Graph &g, int s, vector<int> &dist) {
    vector<int> pred(g.n()); // vetor de predecessores
    for (int i = 0; i < g.n(); i++) {
        dist[i] = INF; // distancia de peso acumulado "infinito"
        pred[i] = -1; // -1 marca como vazio
        g.set_mark(i, false);
    }

    priority_queue<Triple, vector<Triple>, CompareTriple> heap;
    heap.push(Triple(s, s, 0)); dist[s] = 0;
    for (int i = 0; i < g.n(); i++) {
        Triple t;
        do {
            if (heap.empty()) return; // encerra a execução do algoritmo
            t = heap.top();
            heap.pop();
        } while (g.get_mark(t.second) == true);
        g.set_mark(t.second, true); pred[t.second] = t.first;
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
    Graph g(5);
    vector<int> dist(g.n()); // vetor de distancias
    g.add_edge(0, 1, 10);
    g.add_edge(0, 3, 20);
    g.add_edge(0, 2, 3);
    g.add_edge(1, 3, 5);
    g.add_edge(2, 1, 2);
    g.add_edge(2, 4, 15);
    g.add_edge(3, 4, 11);
    
    Dijkstra(g, 0, dist);
    
    for (int i : dist) {
        cout << i << ' ';
    }
    cout << endl;

  
    return 0;
}
