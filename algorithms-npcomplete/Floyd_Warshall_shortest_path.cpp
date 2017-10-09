#include <iostream>
#include <vector>
using namespace std;

/* @param adjMatrix, graph adjacent matrix
 * @return, null, output all pair shortest path, INT_MAX means no such path
 */ 
void Floyd_Warshall(vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> dist(adjMatrix);

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][k] < INT_MAX && dist[k][j] < INT_MAX && dist[i][j] > dist[i][k] + dist[k][j]) 
                    dist[i][j] = dist[i][k] + dist[k][j];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << dist[i][j] << " ";
        cout << "\n";
    }

    return;
}

int main() {
    int n = 5;
    vector<vector<int>> adjMatrix(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; ++i) adjMatrix[i][i] = 0;
    adjMatrix[0][1] = 2;
    adjMatrix[0][2] = 4;
    adjMatrix[1][2] = 1;
    adjMatrix[1][3] = 2;
    adjMatrix[2][4] = 4;
    adjMatrix[3][4] = 2;

    Floyd_Warshall(adjMatrix);
}