#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph {
public:
    Graph(int n) {
        this->n = n;
        this->adjList = vector<vector<int>>(n, vector<int>{});
    }

    void addEdge(int s, int e) {
        adjList[s].push_back(e);
    }

    // reverse graph
    void reverse() {
        vector<vector<int>> newAdjList = vector<vector<int>>(n, vector<int>{});
        for (int i = 0; i < n; ++i)
            for (int e : adjList[i])
                newAdjList[e].push_back(i);
        this->adjList = newAdjList;
    }

    // adjcent list
    vector<vector<int>> adjList;
    // number of vertices
    int n;
};

class Kosaraju {
public:
    Kosaraju(Graph gg) : g(gg) {}

    void printSCCs() {
        stack<int> st;
        vector<bool> visited(g.n, false);

        for (int i = 0; i < g.n; ++i)
            if (!visited[i]) firstDFS(i, visited, st);

        g.reverse();
        visited = vector<bool>(g.n, false);
        while (!st.empty()) {
            if (!visited[st.top()]) {
                secondDFS(st.top(), visited);
                cout << "\n";
            }
            st.pop();
        }
    }

private:
    // first dfs to compute the order, saved by the stack
    void firstDFS(int s, vector<bool>& visited, stack<int>& st) {
        visited[s] = true;
        for (int e : g.adjList[s])
            if (!visited[e]) firstDFS(e, visited, st);
        st.push(s);
    }

    // second dfs based on reversed graph, output SCCs
    void secondDFS(int s, vector<bool>& visited) {
        visited[s] = true;
        cout << s << " ";

        for (int e : g.adjList[s])
            if (!visited[e]) secondDFS(e, visited);
    }

    Graph g;
};

int main() {
    Graph g(5);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);

    Kosaraju k(g);
    k.printSCCs();
}