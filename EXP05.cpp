
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
};

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.assign(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y)
            return false;

        if (rank[x] < rank[y])
            swap(x, y);

        parent[y] = x;

        if (rank[x] == rank[y])
            rank[x]++;

        return true;
    }
};

int main() {
    int V, E;

    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);

    cout << "Enter edges (u v weight), vertices 0 to V-1:\n";
    for (int i = 0; i < E; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;

    sort(edges.begin(), edges.end(), compare);

    DSU dsu(V);
    int totalWeight = 0;
    int edgeCount = 0;

    cout << "\nEdges in Minimum Spanning Tree:\n";

    for (const Edge& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            cout << e.u << " - " << e.v
                 << " : " << e.weight << '\n';

            totalWeight += e.weight;
            edgeCount++;

            if (edgeCount == V - 1)
                break;
        }
    }

    if (edgeCount != V - 1) {
        cout << "Graph is disconnected; no spanning tree exists.\n";
    } else {
        cout << "Total MST weight: " << totalWeight << '\n';
    }

    return 0;
}
