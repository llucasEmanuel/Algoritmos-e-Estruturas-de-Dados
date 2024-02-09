#include <iostream>
#include <vector>
#include <queue>
#define endl '\n'

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
    void add_edge(int i, int j) {
        if (this->matrix[i][j] == 0) this->num_edges++;
        this->matrix[i][j] = 1;
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

int main() {

    int c;
    cin >> c; // qtd de casos
    for (int i = 0; i < c; i++) {
        int v, a; // numero de vertices e numero de arestas
        cin >> v >> a;
        Graph graph(v); // cria um grafo com v vertices
        for (int j = 0; j < a; j++) { // le as arestas
            int w1, w2;
            cin >> w1 >> w2;
            graph.add_edge(w1, w2);
        }
        int n;
        cin >> n; // numero de perguntas;
        cout << "Caso " << i+1 << endl;
        for (int j = 0; j < n; j++) {
            int s, d;
            cin >> s >> d;
            cout << graph.shortest_path(s, d) << endl;
        }

    }

    return 0;
}
