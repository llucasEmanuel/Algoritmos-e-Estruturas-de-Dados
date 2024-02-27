void Dijkstra(Graph &g, int s, vector<int> &dist) {
    vector<int> pred(g.n());
    for (int i = 0; i < g.n(); i++) {
        dist[i] = INF;
        pred[i] = -1; // -1 marca o vazio
        g.set_mark(i, false);
    }
    // greater compara o primeiro elemento das tuplas (adotar ele como sendo o weight), se forem iguais vai pro segundo, ...
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> heap;
    heap.push(make_tuple(0, s, s)); dist[s] = 0;
    for (int i = 0; i < g.n(); i++) {
        tuple<int, int, int> t; // (w:0, p:1, v:2)
        do {
            if (heap.empty()) return;
            t = heap.top();
            heap.pop();
        } while (g.get_mark(get<2>(t)) == true);
        g.set_mark(get<2>(t), true);
        pred[get<2>(t)] = get<1>(t);
        int w = g.first(get<2>(t));
        while (w < g.n()) {
            if (g.get_mark(w) != true && dist[w] > dist[get<2>(t)] + g.weight(get<2>(t), w)) {
                dist[w] = dist[get<2>(t)] + g.weight(get<2>(t), w);
                heap.push(make_tuple(dist[w], get<2>(t), w));
            }
            w = g.next(get<2>(t), w);
        }
    }
}
