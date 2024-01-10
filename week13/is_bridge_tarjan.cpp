#include<bits/stdc++.h>
using namespace std;

class Graph {
    int V;
    list<int> *adj;
    void bridgeUtil(int v, bool visited[], int disc[], int low[], int parent[]);
public:
    Graph(int V);
    void addEdge(int v, int w);
    void bridge();
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::bridgeUtil(int u, bool visited[], int disc[], int low[], int parent[]) {
    static int time = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time;
    for (auto v : adj[u]) {
        if (!visited[v]) {
            parent[v] = u;
            bridgeUtil(v, visited, disc, low, parent);
            low[u] = min(low[u], low[v]);
            if (low[v] > disc[u])
                cout << v << endl;
        } else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

void Graph::bridge() {
    bool *visited = new bool[V];
    int *disc = new int[V];
    int *low = new int[V];
    int *parent = new int[V];
    for (int i = 0; i < V; i++) {
        parent[i] = -1;
        visited[i] = false;
    }
    for (int i = 0; i < V; i++)
        if (!visited[i])
            bridgeUtil(i, visited, disc, low, parent);
}

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.bridge();

    return 0;
}
