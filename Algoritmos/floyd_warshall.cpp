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

void floyd_warshall(Graph g, vector<vector<int>> &d) {
    for (int i = 0; i < g.n(); i++) {
        for (int j = 0; j < g.n(); j++) {
            if (i == j) d[i][j] = 0;
            else if (g.weight(i, j) != 0) d[i][j] = g.weight(i, j);
            else d[i][j] = INF;
        }
    }

    for (int k = 0; k < g.n(); k++) {
        for (int i = 0; i < g.n(); i++) {
            for (int j = 0; j < g.n(); j++) {
                if (d[i][k] != INF && d[k][j] != INF && d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
}

int main() {
    Graph g(4);
    vector<vector<int>> d(4, vector<int>(4));
    g.add_edge(0, 2, 3);
    g.add_edge(1, 0, 2);
    g.add_edge(2, 3, 1);
    g.add_edge(2, 1, 7);
    g.add_edge(3, 0, 6);

    floyd_warshall(g, d);
    for (auto i : d) {
        for (auto j : i) {
            cout << j << ' ';
        }
        cout << endl;
    }
  
    return 0;
}
