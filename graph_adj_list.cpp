#include <iostream>
#include <vector>
#include <list>
#include <stack>
#define endl '\n'

using namespace std;

class Graph {
private:
    vector<list<pair<int, int>>> list;
    int num_edge;
    vector<bool> mark;

public:
    Graph(int n) {
        this->mark.resize(n);
        this->list.resize(n);
        this->num_edge = 0;
    }

    int n() {
        return this->mark.size(); // num de vertices
    }
    int e() {
        return this->num_edge;
    }
    void set_edge(int i, int j, int weight) { // aresta de i pra j
        if (weight == 0) return;
        auto it = list[i].begin(); // iterador inicia no primeiro elemento da linked_list
        for (; it != list[i].end(); it++) {
            if ((*it).first >= j) {
                break;
            }
        }
        list[i].insert(it, make_pair(j, weight)); // insere antes do elemento
        // talvez de problema de adicionar no fim // n deu não :O
    }
    void del_edge(int i, int j) {
        auto it = list[i].begin();
        for (; it != list[i].end(); it++) {
            if ((*it).first == j) {
                list[i].remove(make_pair(j, (*it).second));
                return;
            }
        }
    }
    bool is_edge(int i, int j) {
        auto it = list[i].begin();
        for (; it != list[i].end(); it++) {
            if ((*it).first == j && (*it).second == 0) {
                return false;
            }
        }
        return true;
    }
    int first(int v) { // primeiro vertice dps de v
        if (list[v].empty()) return this->n();
        else return list[v].front().first;
    }
    int next(int v, int w) { // pega o primeiro vertice que v se conecta dps de w
        auto it = list[v].begin();
        while (it != list[v].end() && (*it).first < w+1) {
            it++;
        } // it sai do loop = w + 1
        if (it == list[v].end()) {
            return this->n();
        }
        return (*it).first;
    }
    int weight(int i, int j) {
        auto it = list[i].begin();
        for (; it != list[i].end(); it++) {
            if ((*it).first == j) {
                return (*it).second;
            }
        }
        return 0;
    }
    void set_mark(int v, bool val) {
        this->mark[v] = val;
    }
    int get_mark(int v) {
        return this->mark[v];
    }
    void DFS(int v) {
        // previsit()
        this->set_mark(v, true);
        int w = this->first(v);
        while (w < this->n()) {
            if (this->get_mark(w) == false) {
                this->DFS(w);
            }
            w = this->next(v, w);
        }
        // posvisit
    }
    void graph_traverse() {
        stack<int> s;
        for (int v = 0; v < this->n(); v++) {
            this->set_mark(v, false); // false = nao visitado e true = visitado
        }
        for (int v = 0; v < this->n(); v++) {
            if (this->get_mark(v) == false) {
                // traverse
                //this->DFS(v);
                this->toposort(v, s);
            }
        }
        while (!s.empty()) {
            int v = s.top();
            cout << v << ' ';
            s.pop();
        }
        cout << endl;
    }
    void toposort(int v, stack<int> &s) {
        this->set_mark(v, true);
        int w = this->first(v);
        while (w < this->n()) {
            if (this->get_mark(w) == false) {
                this->toposort(w, s);
            }
            w = this->next(v, w);
        }
        s.push(v);
    }
    void print() {
        int v = 0;
        for (auto i : this->list) {
            cout << v << ": ";
            for (auto j : i) {
                cout << j.first << ' ';
            }
            cout << endl;
            v++;
        }
    }
};

int main() {

    Graph g(6);
    // graph.set_edge(0, 1, 1);
    // graph.set_edge(0, 2, 1);
    // graph.set_edge(0, 4, 1);
    // graph.set_edge(0, 3, 1);
    // graph.set_edge(0, 5, 1);
    g.set_edge(0, 1, 1);
    g.set_edge(3, 2, 1);
    g.set_edge(1, 5, 1);
    g.set_edge(5, 0, 6);
    g.set_edge(2, 1, 3);
    g.set_edge(0, 3, 1);
    g.set_edge(0, 4, 1);
    g.set_edge(2, 4, 1);
    g.set_edge(1, 3, 1);
    //g.graph_traverse();
    g.print();

    return 0;
}
