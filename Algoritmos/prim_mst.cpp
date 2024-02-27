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

void Prim(Graph &g,  vector<lli> &dist, vector<int> &pred) {
    for (int i = 0; i < g.n(); i++) {
        dist[i] = INF; // distancia de peso acumulado "infinito"
        pred[i] = -1; // -1 marca como vazio
        g.set_mark(i, false);
    }

    priority_queue<Triple, vector<Triple>, CompareTriple> heap;
    heap.push(Triple(0, 0, 0)); dist[0] = 0;
    for (int i = 0; i < g.n(); i++) {
        Triple t; // inicializou tudo com 0 por padrão
        do {
            if (heap.empty()) return; // encerra a execução do algoritmo
            t = heap.top(); // atribui o topo
            heap.pop();
        } while (g.get_mark(t.second) == true);
        g.set_mark(t.second, true); 
        pred[t.second] = t.first;
        int w = g.first(t.second);
        while (w < g.n()) {
            if (g.get_mark(w) != true && dist[w] > g.weight(t.second, w)) {
                dist[w] = g.weight(t.second, w);
                heap.push(Triple(t.second, w, dist[w]));
            }
            w = g.next(t.second, w);
        }
    }
}
