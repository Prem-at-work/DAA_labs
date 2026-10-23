
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int INF = INT_MAX;

void dijkstra(int V, vector<vector<pair<int, int>>>& adj,
              int source) {
    vector<int> dist(V, INF);

    // Min-priority queue: {distance, vertex}
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Ignore outdated entries
        if (d != dist[u])
            continue;

        // Visit adjacent vertices
        for (auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (d <= INF - weight &&
                dist[v] > d + weight) {
                dist[v] = d + weight;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "\nShortest distances from source "
         << source << ":\n";

    for (int i = 0; i < V; i++) {
        cout << "Vertex " << i << " : ";

        if (dist[i] == INF)
            cout << "Unreachable";
        else
            cout << dist[i];

        cout << '\n';
    }
}

int main() {
    int V, E;

    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    if (V <= 0 || E < 0) {
        cout << "Invalid graph size\n";
        return 1;
    }

    vector<vector<pair<int, int>>> adj(V);

    cout << "Enter edges (u v weight):\n";

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        if (u < 0 || u >= V ||
            v < 0 || v >= V || w < 0) {
            cout << "Invalid edge or negative weight\n";
            return 1;
        }

        // Undirected graph
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int source;
    cout << "Enter source vertex: ";
    cin >> source;

    if (source < 0 || source >= V) {
        cout << "Invalid source vertex\n";
        return 1;
    }

    dijkstra(V, adj, source);

    return 0;
}
