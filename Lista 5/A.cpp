#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
#define lli long long int
#define endl '\n'

using namespace std;

// pegar a matriz de adjacencia e verificar cada coluna
// se ela so tiver 0 printa o vertice, se tiver
// fazer uma funcao recursiva que passa por cada coluna
// se so tiver zero printa o vertice da coluna
// se nao vai chamando recursivmente ate chegar na coluna tudo zero
// quando printar um vertice zera todos os elementos da linha dele

enum {
    white = -1,
    gray = 0,
    black = 1
};

class Graph { // unweighted digraph
private:
    vector<vector<int>> matrix;
    int num_edges;
    int count;
    vector<int> mark;

public:
    int n() {
        return this->mark.size(); // eh o mesmo q o numero de vertices
    }
    int e() {
        return this->num_edges;
    }
    int first(int v) {
        for (int i = this->n()-1; i >= 0; i--) {
            if (this->matrix[v][i] != 0) return i;
        }
        return this->n();
    }
    int next(int v, int w) {
        for (int i = w-1; i >= 0; i--) {
            if (this->matrix[v][i] != 0) return i;
        }
        return this->n();
    }
    void add_edge(int i, int j) {
        if (this->matrix[i][j] == 0) this->num_edges++;
        this->matrix[i][j] = 1;
    }
    void del_edge(int i, int j) {
        if (this->matrix[i][j] != 0) this->num_edges--;
        this->matrix[i][j] = 0;
    }
    void set_mark(int v, int state) {
        this->mark[v] = state;
    }
    int get_mark(int v) {
        return this->mark[v];
    }
    void DFS(int v, stack<int> &s) { // w = n visitado, g = visitando e b = visitado
        this->set_mark(v, gray);
        int w = this->first(v);
        while (w < this->n()) {
            if (this->get_mark(w) == white) { // nao visitado
                this->DFS(w, s);
            }
            if (this->get_mark(w) == gray) { // detecta ciclo
                this->count++;
            }
            w = this->next(v, w);
        }
        this->set_mark(v, black);
        s.push(v);
    }   
    void toposort(stack<int> &s) {
        for (int i = 0; i < this->n(); i++) {
            this->set_mark(i, white);
        }

        for (int i = this->n() - 1; i >= 0; i--) {
            if (this->get_mark(i) == white) {
                this->DFS(i, s);
            }
        }
    }
    // void graph_traverse() {
    //     stack<int> s;
    //     for (int v = 0; v < this->n(); v++) {
    //         this->set_mark(v, false);
    //     }
    //     for (int v = 0; v < this->n(); v++) {
    //         if (this->get_mark(v) == false) {
    //             this->toposort(v, s);
    //         }
    //     }
    //     while (!s.empty()) {
    //         cout << s.top() + 1 << ' ';
    //         s.pop();
    //     }
    //     cout << endl;
    // }
    void print_order() {
        stack<int> s;
        this->toposort(s);
        if (this->count == 0) { // no cycleeee
            for (int i = 0; i < this->n(); i++) {
                cout << s.top() + 1 << ' ';
                s.pop();
            }
            cout << endl;
        }
        else {
            cout << "Sandro fails." << endl;
        }
    }
    Graph(int v) {
        this->matrix.resize(v);
        for (int i = 0; i < v; i++) {
            this->matrix[i].resize(v);
        }
        this->mark.resize(v);
        this->num_edges = 0;
        this->count = 0;
    }
};

int main() {

    int n;
    lli m;
    cin >> n >> m;
    Graph graph(n);
    for (lli i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph.add_edge(x-1, y-1);
    }
     //graph.graph_traverse();
    //graph.print_topo();
    graph.print_order();

    return 0;
}
