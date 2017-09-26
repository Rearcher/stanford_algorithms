#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
public:
    UnionFind(int n) {
        for (int i = 0; i < n; ++i)
            parent.push_back(i);
        size = vector<int>(n, 1);
    }

    int find(int i) {
        while (i != parent[i]) {
            // path compression
            parent[i] = parent[parent[i]];
            i = parent[i];
        }
        return i;
    }
    
    void connect(int p, int q) {
        int i = find(p), j = find(q);
        if (i == j) return;
    
        // always make small tree slower
        if (size[i] < size[j]) {
            parent[i] = j;
            size[j] += size[i];
        } else {
            parent[j] = i;
            size[i] += size[j];
        }
    }

private:
    // for quick union-find algorithm
    vector<int> parent;
    // record union-find subtree size
    vector<int> size;
};

struct Edge {
    int u, v, w;
    Edge(int a, int b, int c) : u(a), v(b), w(c) {}
};

/* @param graph, edge list
 * @param n, number of nodes in graph
 * @return, cost of minimum span tree
 */
int kruskal(vector<Edge>& graph, int n) {
    sort(graph.begin(), graph.end(), [&](Edge a, Edge b){ return a.w < b.w; });
    
    UnionFind uf(n);
    int cost = 0;
    for (Edge e : graph) {
        int p1 = uf.find(e.u), p2 = uf.find(e.v);
        if (p1 != p2) {
            cost += e.w;
            uf.connect(p1, p2);
        }
    }
    return cost;
}

int main() {
    vector<Edge> graph;
    graph.push_back(Edge(0, 1, 7));
    graph.push_back(Edge(0, 3, 5));
    graph.push_back(Edge(1, 2, 8));
    graph.push_back(Edge(1, 3, 9));
    graph.push_back(Edge(1, 4, 7));
    graph.push_back(Edge(2, 4, 5));
    graph.push_back(Edge(3, 4, 10));

    cout << kruskal(graph, 5) << endl;
}