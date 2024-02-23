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
    while (!heap.empty()) {
        Triple t = heap.top(); // atribui o topo
        heap.pop();
        if (g.get_mark(t.second) == true) continue;
        g.set_mark(t.second, true); 
        pred[t.second] = t.first;
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
