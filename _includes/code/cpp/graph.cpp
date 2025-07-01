#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <climits>
#include <algorithm>

using namespace std;

// 图的邻接矩阵表示
class AdjMatrixGraph {
private:
    int V; // 顶点数
    vector<vector<int>> adj; // 邻接矩阵

public:
    AdjMatrixGraph(int V) : V(V) {
        adj.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int w) {
        adj[u][v] = w;
        adj[v][u] = w; // 无向图
    }

    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "BFS traversal starting from vertex " << start << ":\n";
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (int i = 0; i < V; ++i) {
                if (adj[v][i] && !visited[i]) {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
        cout << endl;
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        stack<int> s;
        s.push(start);
        visited[start] = true;

        cout << "DFS traversal starting from vertex " << start << ":\n";
        while (!s.empty()) {
            int v = s.top();
            s.pop();
            cout << v << " ";

            for (int i = 0; i < V; ++i) {
                if (adj[v][i] && !visited[i]) {
                    s.push(i);
                    visited[i] = true;
                }
            }
        }
        cout << endl;
    }
};

// 图的邻接表表示
class AdjListGraph {
private:
    int V; // 顶点数
    vector<list<pair<int, int>>> adj; // 邻接表

public:
    AdjListGraph(int V) : V(V) {
        adj.resize(V);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // 无向图
    }

    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "BFS traversal starting from vertex " << start << ":\n";
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (auto &neighbor : adj[v]) {
                int w = neighbor.first;
                if (!visited[w]) {
                    q.push(w);
                    visited[w] = true;
                }
            }
        }
        cout << endl;
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        stack<int> s;
        s.push(start);
        visited[start] = true;

        cout << "DFS traversal starting from vertex " << start << ":\n";
        while (!s.empty()) {
            int v = s.top();
            s.pop();
            cout << v << " ";

            for (auto &neighbor : adj[v]) {
                int w = neighbor.first;
                if (!visited[w]) {
                    s.push(w);
                    visited[w] = true;
                }
            }
        }
        cout << endl;
    }
};

// 最小生成树（普利姆算法）
void PrimMST(vector<vector<int>>& graph, int V) {
    vector<int> parent(V, -1);
    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false);

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; ++count) {
        int u = minKey(key, inMST, V);
        inMST[u] = true;

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    cout << "Prim's MST:\n";
    for (int i = 1; i < V; ++i) {
        cout << parent[i] << " - " << i << " weight " << graph[i][parent[i]] << endl;
    }
}

// 最小生成树（克鲁斯卡尔算法）
void KruskalMST(vector<vector<int>>& graph, int V) {
    vector<pair<int, pair<int, int>>> edges;
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            if (graph[u][v] != 0) {
                edges.push_back({graph[u][v], {u, v}});
            }
        }
    }

    sort(edges.begin(), edges.end());

    vector<int> parent(V);
    for (int i = 0; i < V; ++i) {
        parent[i] = i;
    }

    cout << "Kruskal's MST:\n";
    for (auto &edge : edges) {
        int u = edge.second.first;
        int v = edge.second.second;
        int set_u = find(parent, u);
        int set_v = find(parent, v);

        if (set_u != set_v) {
            cout << u << " - " << v << " weight " << edge.first << endl;
            parent[set_u] = set_v;
        }
    }
}

// 查找并查集的根节点
int find(vector<int>& parent, int i) {
    if (parent[i] == i) {
        return i;
    }
    return find(parent, parent[i]);
}

// 最短路径（迪杰斯特拉算法）
void Dijkstra(vector<vector<int>>& graph, int src, int V) {
    vector<int> dist(V, INT_MAX);
    vector<bool> visited(V, false);

    dist[src] = 0;

    for (int count = 0; count < V - 1; ++count) {
        int u = minDistance(dist, visited, V);
        visited[u] = true;

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    cout << "Dijkstra's shortest paths from vertex " << src << ":\n";
    for (int i = 0; i < V; ++i) {
        cout << "To " << i << " distance " << dist[i] << endl;
    }
}

// 拓扑排序
void topologicalSort(vector<vector<int>>& graph, int V) {
    vector<int> inDegree(V, 0);
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            if (graph[u][v]) {
                inDegree[v]++;
            }
        }
    }

    queue<int> q;
    for (int i = 0; i < V; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";

        for (int v = 0; v < V; ++v) {
            if (graph[u][v]) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }
    }
}

// 辅助函数：找到距离最小的顶点
int minDistance(vector<int>& dist, vector<bool>& visited, int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; ++v) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// 辅助函数：找到邻接矩阵中的最小键
int minKey(vector<int>& key, vector<bool>& inMST, int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; ++v) {
        if (!inMST[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

int main() {
    int V = 5;
    vector<vector<int>> graph = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    AdjMatrixGraph adjMatrixGraph(V);
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            if (graph[u][v] != 0) {
                adjMatrixGraph.addEdge(u, v, graph[u][v]);
            }
        }
    }

    AdjListGraph adjListGraph(V);
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            if (graph[u][v] != 0) {
                adjListGraph.addEdge(u, v, graph[u][v]);
            }
        }
    }

    cout << "Adjacency Matrix Graph:\n";
    adjMatrixGraph.BFS(0);
    adjMatrixGraph.DFS(0);

    cout << "Adjacency List Graph:\n";
    adjListGraph.BFS(0);
    adjListGraph.DFS(0);

    PrimMST(graph, V);
    KruskalMST(graph, V);
    Dijkstra(graph, 0, V);
    topologicalSort(graph, V);

    return 0;
}
