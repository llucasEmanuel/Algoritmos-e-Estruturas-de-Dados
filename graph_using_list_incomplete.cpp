#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#define endl '\n'

using namespace std;

class Graph {
private:
    vector<list<pair<int, int>>> adj; // adjacency list (vertex, weight)
    vector<bool> mark;
    int num_edges;
public:
    int n() {
        return this->mark.size(); // eh o mesmo q o numero de vertices
    }
    int e() {
        return this->num_edges;
    }
    void add_edge(int i, int j, int wt) {
        auto it = adj[i].begin();
        while (it != adj[i].end()) { // insercao ordenada
            if ((*it).first >= j) {
                break;
            }
            it++;
        }
        adj[i].insert(it, make_pair(j, wt));
    }
};

int main() {


    return 0;
}
