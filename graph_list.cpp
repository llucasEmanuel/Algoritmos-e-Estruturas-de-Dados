#include <iostream>
#include <vector>
#include <forward_list>
#define endl '\n'

using namespace std;

class LinkedList {
public:
    forward_list<pair<int, int>> link_list;
    int num_links;

    LinkedList() {
        this->num_links = 0;
    }
};

class Graph {
private:
    vector<LinkedList> list;
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
        auto it = list[i].link_list.begin();
        for (; it != list[i].link_list.end(); ++it) {
            if ((*it).first >= j) {
                break;
            }
        }
        list[i].link_list.insert_after(it, make_pair(j, weight)); // insere dps do elemento
        // tem q adicionar antes aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    }
    int first(int v) { // primeiro vertice dps de v

    }

};

int main() {



    return 0;
}
