#include <climits>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

// Dijkstra, O(E logV)
// Sparse, Single Source, No Negative Cycle
class Dijkstra {
  using Edge = pair<int, int>;  // weight, node

  using Heap = priority_queue<Edge, vector<Edge>, greater<>>;  // min-heap

  // Graph: from -> (weight, to) pairs
  int solve(const vector<vector<Edge>>& graph, int source, int target) {
    const int n = graph.size();

    // Loop
    auto costs = vector<int>(n, INT_MAX);
    Heap heap;
    costs[source] = 0;
    heap.emplace(0, source);

    while (!heap.empty()) {
      auto [cost, node] = heap.top();
      heap.pop();

      // Early stop
      if (node == target) return cost;

      // Relax
      if (costs[node] < cost) continue;

      // Traverse
      for (const auto [weight, nextNode] : graph[node]) {
        int nextCost = cost + weight;
        if (costs[nextNode] <= nextCost) continue;  // Relax
        costs[nextNode] = nextCost;
        heap.emplace(nextCost, nextNode);
      }
    }

    return INT_MAX;  // unreachable
  }
};

// Dense Dijkstra, O(V^2)
// Dense, Single Source, No Negative Cycle
class DijkstraDense {
  using Edge = pair<int, int>;  // weight, node

  using Heap = priority_queue<Edge, vector<Edge>, greater<>>;  // min-heap

  // Graph: (from, to) -> weight, INT_MAX for no edge
  int solve(const vector<vector<int>>& graph, int source, int target) {
    const int n = graph.size();

    // Loop
    auto costs = vector<int>(n, INT_MAX);
    auto dones = vector<bool>(n, false);
    costs[source] = 0;

    for (int iter = 0; iter < n - 1; ++iter) {  // at most n-1 steps to finalize all nodes
      // Find nearest non-finished node
      int u = -1;
      int cost = INT_MAX;
      for (int i = 0; i < n; ++i) {
        if (!dones[i] && costs[i] < cost) {
          u = i;
          cost = costs[i];
        }
      }

      // Early stop
      if (u == -1) break;
      if (u == target) return cost;

      // Update
      dones[u] = true;

      // Traverse
      for (int v = 0; v < n; ++v) {
        if (dones[v] || graph[u][v] == INT_MAX) continue;
        costs[v] = min(costs[v], cost + graph[u][v]);
      }
    }

    return INT_MAX;  // unreachable
  }
};

// Bellman-Ford, O(EV)
// Sparse, Single Source, Negative Cycle
class BellmanFord {
  using Edge = tuple<int, int, int>;  // weight, from, to

  int solve(const int n, const vector<Edge>& edges, int source, int target) {
    // Loop
    auto costs = vector<int>(n, INT_MAX);
    costs[source] = 0;
    for (int iter = 0; iter < n - 1; ++iter) {  // at most n-1 steps to reach target
      bool updated = false;

      for (auto [w, u, v] : edges) {
        if (costs[u] == INT_MAX) continue;
        int nextCost = costs[u] + w;
        if (costs[v] > nextCost) {
          costs[v] = nextCost;
          updated = true;
        }
      }

      // Early stop
      if (!updated) break;
    }

    // Detect negative cycle
    for (auto [w, u, v] : edges) {
      if (costs[u] == INT_MAX) continue;
      int nextCost = costs[u] + w;
      if (costs[v] > nextCost) {
        return INT_MIN;  // negative cycle detected
      }
    }

    return costs[target];  // INT_MAX as unreachable
  }
};

// Floyd-Warshall, O(V^3)
// Dense, All Pairs, Negative Cycle
class FloydWarshall {
  // Graph: (from, to) -> weight, INT_MAX for no edge
  bool solve(vector<vector<int>>& graph) {
    const int n = graph.size();

    // Add self edges
    for (int i = 0; i < n; ++i) {
      graph[i][i] = 0;
    }

    // Loop
    for (int k = 0; k < n; ++k) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (graph[i][k] < INT_MAX && graph[k][j] < INT_MAX) {
            graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
          }
        }
      }
    }

    // Negative cycle detection
    for (int i = 0; i < n; ++i) {
      if (graph[i][i] < 0) return false;  // i is on negative cycle
    }

    return true;
  }
};
