#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

// Kruskal, O(E logE); Good for sparse graph.
class Kruskal {
  using Edge = tuple<int, int, int>;  // weight, node, node

  struct UnionFind {
    UnionFind(int n);
    int find(int x) const;
    bool isConnected(int x, int y) const;
    void unite(int x, int y);
  };

  void solve(int n, vector<Edge>& edges) {
    // Sort by weight
    sort(edges.begin(), edges.end());

    // Loop
    UnionFind uf(n);
    for (auto [w, u, v] : edges) {
      // Merge
      if (uf.isConnected(u, v)) continue;
      uf.unite(u, v);

      // Add edge into MST

      // Early stop, check #edge(MST) == n-1
    }

    // check connectivity by #edge(MST) == n-1
  }
};

// Dense Prim, O(V^2); Good for dense graph.
class Prim {
  // Graph: [i][j] -> edge weight
  void solve(const vector<vector<int>>& graph) {
    const int n = graph.size();

    // Prepare data
    auto visited = vector<bool>(n);
    auto dists = vector<int>(n, INT_MAX);
    dists[0] = 0;

    // Loop
    for (int iter = 0; iter < n; ++iter) {  // only n nodes
      // Find nearest unvisited point
      int u = min_element(dists.cbegin(), dists.cend()) - dists.cbegin();

      // Check connectivity
      if (dists[u] == INT_MAX) return;

      // Update
      visited[u] = true;
      dists[u] = INT_MAX;  // remove from target set

      // Add edge into MST

      // Update target set
      for (int v = 0; v < n; ++v) {
        if (visited[v]) continue;
        dists[v] = min(dists[v], graph[u][v]);
      }
    }
  }
};
