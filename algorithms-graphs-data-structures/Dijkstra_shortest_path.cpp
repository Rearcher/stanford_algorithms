#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/* @param graph: adjacent matrix, graph[i][j] = INT_MAX means there's no direct path from i to j
 * @param s: source vertex
 * @return: shortest path from s to other vertexes
 */
vector<int> dijkstra(vector<vector<int>>& graph, int s) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> dist(n, INT_MAX);
    dist[s] = 0;

    visited[s] = true;
    for (int i = 1; i < n; ++i) {
        int minDist = INT_MAX, minIndex = 0;
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                minIndex = i;
            }
        }

        visited[minIndex] = true;
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && graph[minIndex][i] != INT_MAX)
                dist[i] = min(dist[i], dist[minIndex] + graph[minIndex][i]);
        }
    }

    return dist;
}

vector<int> dijkstra_with_heap(vector<vector<int>>& graph, int s) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    dist[s] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({0, s});
    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        minHeap.pop();

        for (int i = 0; i < n; ++i) {
            if (graph[u][i] != INT_MAX && dist[i] > dist[u] + graph[u][i]) {
                dist[i] = dist[u] + graph[u][i];
                minHeap.push({dist[i], i});
            }
        }
    }
    return dist;
}

int main() {
    int n = 4;
    vector<vector<int>> graph(n, vector<int>(n, INT_MAX));
    graph[0][1] = 1;
    graph[0][2] = 4;
    graph[1][2] = 2;
    graph[1][3] = 6;
    graph[2][3] = 3;
    for (int i = 0; i < n; ++i) graph[i][i] = 0;

    // vector<int> dist = dijkstra(graph, 0);
    vector<int> dist = dijkstra_with_heap(graph, 0);
    for (int d : dist) cout << d << " ";
    cout << "\n";
 }