#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_set>
#include <algorithm>
#define endl '\n'

using namespace std;

class Graph { // unweighted graph
private:
    vector<vector<int>> matrix;
    int num_edges;
    vector<bool> mark;

public:
    map<string, int> m; // mapear as strings
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
    void add_edge(int i, int j) { // grafo nao direcionado
        if (this->matrix[i][j] == 0) this->num_edges++;
        this->matrix[i][j] = 1;
        this->matrix[j][i] = 1;
    }
    void del_edge(int i, int j) {
        if (this->matrix[i][j] != 0) this->num_edges--;
        this->matrix[i][j] = 0;
        this->matrix[j][i] = 0;
    }
    void set_mark(int v, bool state) {
        this->mark[v] = state;
    }
    bool get_mark(int v) {
        return this->mark[v];
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
    // LÓGICA DO MENOR CAMINHO
    // marca todos os vertices do mark como nao visitados
    // cria um vetor de predecessores e marca todos com -1
    // marca o vertice de inicio como visitado no mark
    // adiciona ele a fila
    // inicia as operacoes ate a fila ficar vazia
    // remove o elemento da frente da fila
    // checa se ele eh igual ao destino
    // se sim, inicializa o path_size como 0 e o vertice do destino como curr
    // enqnto curr for diferente de -1 (enqnt n chegar no elemento start)
    // aumenta o path_size a cada iteração e faz curr = pred[curr] (vai pro predecessor desse vertice)
    // no fim vai terminar no vertice de start com o path_size com 1 a mais, ent retorna ele -1
    // se v for diferente de dest, faz um loop por todos os vertices do grafo
    // se o vertice dessa iteração tiver aresta com oq foi removido da fila e ele n tiver sido visitado
    // marca ele como visitado, adiciona na fila e marca o predecessor dele como o que antes era o da frente da fila
    // no final de tudo se n achar um caminho, retorna -1
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
        return this->num_edges+1; // nao existe caminho
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
        if (v > 0) {
            this->matrix.resize(v);
            for (int i = 0; i < v; i++) {
                this->matrix[i].resize(v, 0);
            }
            this->mark.resize(v);
        }
        this->num_edges = 0;
    }
};

void swap(pair<string, int> &a, pair<string, int> &b) {
    pair<string, int> temp = a;
    a = b;
    b = temp;
}

int main() {

    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n; // num de equipes
        Graph g(3*n); // cada equipe tem 3 pessoas (pode haver repeticao)
        int index = 0; // atribuir aos vertices
        for (int j = 0; j < n; j++) {
            string a1, a2, a3;
            cin >> a1 >> a2 >> a3;
            if (g.m.find(a1) == g.m.end()) { // nao achou
                g.m[a1] = index;
                index++;
            }
            if (g.m.find(a2) == g.m.end()) {
                g.m[a2] = index;
                index++;
            }
            if (g.m.find(a3) == g.m.end()) {
                g.m[a3] = index;
                index++;
            }
            g.add_edge(g.m[a1], g.m[a2]);
            g.add_edge(g.m[a2], g.m[a3]);
            g.add_edge(g.m[a1], g.m[a3]);
        }

        vector<pair<string, int>> results;
        for (auto it = g.m.begin(); it != g.m.end(); it++) {
            int d = g.shortest_path(g.m["Ahmad"], (*it).second);
            results.push_back(make_pair((*it).first,  d));
            // first eh o nome e d eh a distancia
        }

        //ordenar results
        for (int i = 0; i < results.size(); i++) {
            for (int j = 0; j < results.size() - 1 - i; j++) {
                if (results[j].second > results[j+1].second) {
                    swap(results[j], results[j+1]);
                }
                else if (results[j].second == results[j+1].second) {
                    // checa ordem lexicografica
                    if (results[j].first > results[j+1].first) {
                        swap(results[j], results[j+1]);
                    }
                }
            }
        }
        cout << index << endl; // printar o index
        for (auto result : results) {
            cout << result.first << ' ';
            if (result.second == g.e() + 1) cout << "undefined" << endl;
            else cout << result.second << endl;
        }
    }

    return 0;
}
