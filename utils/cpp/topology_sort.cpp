#include <vector>
using namespace std;

// Topology Sort
//
// Use output as queue.
class TopologySort {
  using Edge = pair<int, int>;   // weight, node
  using State = pair<int, int>;  // cost, node

 public:
  vector<int> solve(const int n, const vector<Edge>& edges) {
    auto graph = vector<vector<int>>(n);
    auto inDeg = vector<int>(n);
    for (const auto [u, v] : edges) {
      graph[u].push_back(v);
      ++inDeg[v];
    }

    // Init
    auto order = vector<int>();
    order.reserve(n);
    for (int u = 0; u < n; ++u) {
      if (inDeg[u] == 0) order.push_back(u);
    }

    // BFS
    for (int i = 0; i < order.size(); ++i) {
      // Early stop
      if (order.size() == n) break;

      int u = order[i];
      for (int v : graph[u]) {
        if (--inDeg[v] == 0) order.push_back(v);
      }
    }

    // Not reachable
    if (order.size() < n) return {};

    return order;
  }
};
