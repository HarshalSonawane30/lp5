/*Design and implement Parallel Breadth First Search and Depth First Search based on
existing algorithms using OpenMP. Use a Tree or an undirected graph for BFS and DFS */




#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

vector<vector<int>> graph;
vector<bool> visited;

// ----------- Parallel BFS -----------
void parallelBFS(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    cout << "\nParallel BFS Traversal: ";

    while (!q.empty()) {
        int node;

        #pragma omp critical
        {
            node = q.front();
            q.pop();
            cout << node << " ";
        }

        #pragma omp parallel for
        for (int i = 0; i < graph[node].size(); i++) {
            int adj = graph[node][i];

            if (!visited[adj]) {
                #pragma omp critical
                {
                    if (!visited[adj]) {
                        visited[adj] = true;
                        q.push(adj);
                    }
                }
            }
        }
    }
}

// ----------- Parallel DFS -----------
void parallelDFS(int node) {

    #pragma omp critical
    {
        cout << node << " ";
    }

    visited[node] = true;

    #pragma omp parallel for
    for (int i = 0; i < graph[node].size(); i++) {
        int adj = graph[node][i];

        if (!visited[adj]) {
            parallelDFS(adj);
        }
    }
}

// ----------- Main Function -----------
int main() {
    int n, edges;

    cout << "Enter number of nodes: ";
    cin >> n;

    graph.resize(n);
    visited.resize(n, false);

    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // undirected graph
    }

    int start;
    cout << "Enter starting node: ";
    cin >> start;

    // BFS
    parallelBFS(start);

    // Reset visited for DFS
    fill(visited.begin(), visited.end(), false);

    cout << "\nParallel DFS Traversal: ";
    parallelDFS(start);

    cout << endl;
    return 0;
}