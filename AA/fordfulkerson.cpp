#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <iomanip>

using namespace std;

void printResidualGraph(const vector<vector<int>>& residualGraph) {
    int n = residualGraph.size();
    cout << "Residual Graph:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(3) << residualGraph[i][j] << " ";
        }
        cout << endl;
    }
    cout << "---------------------------------" << endl;
}

// BFS to check if there's an augmenting path from source to sink
bool bfs(const vector<vector<int>>& residualGraph, int source, int sink, vector<int>& parent) {
    int n = residualGraph.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; v++) {
            // If v is not visited and u-v edge has residual capacity
            if (!visited[v] && residualGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;

                // If sink is reached, return true
                if (v == sink) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Ford-Fulkerson algorithm using BFS
int fordFulkerson(vector<vector<int>>& graph, int source, int sink) {
    int n = graph.size();
    vector<vector<int>> residualGraph = graph;  // Initial residual graph is the original graph
    vector<int> parent(n);  // To store the path

    int maxFlow = 0;  

    // Augment the flow while there is a path from source to sink
    while (bfs(residualGraph, source, sink, parent)) {
        // Find the maximum flow through the path found by BFS
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        // Update residual capacities of the edges and reverse edges along the path
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        // Add path flow to overall flow
        maxFlow += pathFlow;

        // Print the residual graph after each augmentation
        printResidualGraph(residualGraph);
    }

    return maxFlow;
}

int main() {
    // Example graph with 6 vertices
    vector<vector<int>> graph = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };

    int source = 0;
    int sink = 5;

    cout << "Calculating maximum flow from source " << source << " to sink " << sink << "..." << endl;
    int maxFlow = fordFulkerson(graph, source, sink);
    cout << "The maximum possible flow is " << maxFlow << endl;

    return 0;
}

