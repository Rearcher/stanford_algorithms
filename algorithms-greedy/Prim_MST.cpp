#include <iostream>
#include <vector>
#include <set>
using namespace std;

/* @param adjacentList, graph adjacent list, the weight of edge(i, g[i].first) is g[i].second
 * @param start, start node of prim algorithm
 * @return, the cost of minimum span tree
 */
int prim(vector<vector<pair<int,int>>>& adjacentList, int start) {
    // node size
    int n = adjacentList.size();

    // pair.first means edge weight, pair.second means vertex
    // use set as heap
    set<pair<int, int>> minHeap;

    // dist[i] = 0 means node i has been added to the MST
    vector<int> dist(n, INT_MAX);
    int cost = 0;
    dist[start] = 0;

    for (pair<int, int> p : adjacentList[start]) {
        if (dist[p.first] != 0) {
            minHeap.insert({p.second, p.first});
            dist[p.first] = p.second;
        }
    }
    
    while (!minHeap.empty()) {
        // extract the minimum edeg
        int v = (*minHeap.begin()).second;
        cost += (*minHeap.begin()).first;
        minHeap.erase(minHeap.begin());
        dist[v] = 0;

        // update heap
        for (pair<int, int> p : adjacentList[v]) {
            if (dist[p.first] == 0) continue;

            if (dist[p.first] > p.second) {
                // remove old edge
                auto iter = minHeap.find({dist[p.first], p.first});
                if (iter != minHeap.end()) minHeap.erase(iter);

                // insert new edge
                minHeap.insert({p.second, p.first});
                dist[p.first] = p.second;
            }
        }
    }

    return cost;
}

int main() {
    vector<vector<pair<int, int>>> adjacentList(5);
    adjacentList[0] = {{1, 7}, {3, 5}};
    adjacentList[1] = {{0, 7}, {2, 8}, {3, 9}, {4, 7}};
    adjacentList[2] = {{1, 8}, {4, 5}};
    adjacentList[3] = {{0, 5}, {1, 9}, {4, 10}};
    adjacentList[4] = {{2, 5}, {1, 7}, {3, 10}};

    cout << prim(adjacentList, 4) << endl;
}