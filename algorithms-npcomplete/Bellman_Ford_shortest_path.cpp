#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int u, v;
    int weight;

    Edge(int u, int v, int w) {
        this->u = u;
        this->v = v;
        this->weight = w;
    }
};

/* @param edges, edge list
 * @param n, vertex number
 * @param s, source vertex
 * @return, false means there exists negative cycle, true means compute successfully
 */ 
bool Bellman_Ford(vector<Edge> edges, int n, int s) {
    vector<int> dist(n, INT_MAX);
    dist[s] = 0;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < edges.size(); ++j)
            if (dist[edges[j].u] < INT_MAX && dist[edges[j].v] > dist[edges[j].u] + edges[j].weight)
                dist[edges[j].v] = dist[edges[j].u] + edges[j].weight;
    }

    for (int j = 0; j < edges.size(); ++j) {
        if (dist[edges[j].u] == INT_MAX || dist[edges[j].v] == INT_MAX) {
            cout << "It can't reach all other vertexes from start vetex: " << s << "\n";
            return false;
        }

        if (dist[edges[j].v] > dist[edges[j].u] + edges[j].weight) {
            cout << "Input graph has negative cycle, abort..." << endl;
            return false;
        }
    }

    cout << "Shortest path:\n";
    for (int i = 0; i < n; ++i)
        cout << s << "-->" << i << ": " << dist[i] << "\n";
    return true;
}

int main() {
    int n = 5, s = 0;
    vector<Edge> edges;
    edges.push_back(Edge(0, 1, 2));
    edges.push_back(Edge(0, 2, 4));
    edges.push_back(Edge(1, 2, 1));
    edges.push_back(Edge(1, 3, 2));
    edges.push_back(Edge(2, 4, 4));
    edges.push_back(Edge(3, 4, 2));

    Bellman_Ford(edges, n, s);
}