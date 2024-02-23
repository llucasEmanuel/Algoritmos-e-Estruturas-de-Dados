#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <algorithm>
#define endl '\n'

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
