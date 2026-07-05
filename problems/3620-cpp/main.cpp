// Source: https://leetcode.com/problems/network-recovery-pathways
// Title: Network Recovery Pathways
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a directed acyclic graph of `n` nodes numbered from 0 to `n-1`. This is represented by a 2D array `edges` of length `m`, where `edges[i] = [u_i, v_i, cost_i]` indicates a one‑way communication from node `u_i` to node `v_i` with a recovery cost of `cost_i`.
//
// Some nodes may be offline. You are given a boolean array `online` where `online[i] = true` means node `i` is online. Nodes 0 and `n-1` are always online.
//
// A path from 0 to `n-1` is **valid** if:
//
// - All intermediate nodes on the path are online.
// - The total recovery cost of all edges on the path does not exceed `k`.
//
// For each valid path, define its **score** as the minimum edge‑cost along that path.
//
// Return the **maximum** path score (i.e., the largest **minimum**-edge cost) among all valid paths. If no valid path exists, return -1.
//
// **Example 1:**
//
// ```
// Input: edges = [[0,1,5],[1,3,10],[0,2,3],[2,3,4]], online = [true,true,true,true], k = 10
// Output: 3
// Explanation:
// https://assets.leetcode.com/uploads/2025/06/06/graph-10.png
//
// - The graph has two possible routes from node 0 to node 3:
//   - Path `0 → 1 → 3`
//     - Total cost = `5 + 10 = 15`, which exceeds k (`15 > 10`), so this path is invalid.
//   - Path `0 → 2 → 3`
//     - Total cost = `3 + 4 = 7 <= k`, so this path is valid.
//     - The minimum edge‐cost along this path is `min(3, 4) = 3`.
// - There are no other valid paths. Hence, the maximum among all valid path‐scores is 3.
// ```
//
// **Example 2:**
//
// ```
// Input: edges = [[0,1,7],[1,4,5],[0,2,6],[2,3,6],[3,4,2],[2,4,6]], online = [true,true,true,false,true], k = 12
// Output: 6
// Explanation:
// https://assets.leetcode.com/uploads/2025/06/06/graph-11.png
//
// - Node 3 is offline, so any path passing through 3 is invalid.
// - Consider the remaining routes from 0 to 4:
//   - Path `0 → 1 → 4`
//     - Total cost = `7 + 5 = 12 <= k`, so this path is valid.
//     - The minimum edge‐cost along this path is `min(7, 5) = 5`.
//   - Path `0 → 2 → 3 → 4`
//     - Node 3 is offline, so this path is invalid regardless of cost.
//   - Path `0 → 2 → 4`
//     - Total cost = `6 + 6 = 12 <= k`, so this path is valid.
//     - The minimum edge‐cost along this path is `min(6, 6) = 6`.
// - Among the two valid paths, their scores are 5 and 6. Therefore, the answer is 6.
// ```
//
// **Constraints:**
//
// - `n == online.length`
// - `2 <= n <= 5 * 10^4`
// - `0 <= m == edges.length <= ``min(10^5, n * (n - 1) / 2)`
// - `edges[i] = [u_i, v_i, cost_i]`
// - `0 <= u_i, v_i < n`
// - `u_i != v_i`
// - `0 <= cost_i <= 10^9`
// - `0 <= k <= 5 * 10^13`
// - `online[i]` is either `true` or `false`, and both `online[0]` and `online[n − 1]` are `true`.
// - The given graph is a directed acyclic graph.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <queue>
#include <vector>

using namespace std;

// Binary Search + Dijkstra
//
// We first remove all offline node from the graph.
//
// The problem ask use o maximize the minimum value.
// It often exhibit a monotonic property, making binary search a natural solution.
//
// Suppose there exist a path such that
// - total weight is at most k,
// - minimal edge is at least x.
// For any y <= x, the same same path also satisfies
// - total weight is at most k, (since its the same path)
// - minimal edge is at least x. (since x >= y)
//
// Therefore, if check(x) is true, then check(y) is true for any y <= x.
// Also, if check(x) is false, then check(z) is false for any z >= x.
// This monotonicity allows us to use binary search to find x.
//
// To implement check, apply Dijkstra to find the minimal path,
// with forbidding any path less than x.
class Solution {
  using Edge = pair<int, int>;         // weight, node
  using State = pair<long long, int>;  // cost, node

  using Heap = priority_queue<State, vector<State>, greater<>>;  // min-heap

 public:
  int findMaxPathScore(const vector<vector<int>>& edges, const vector<bool>& online, const long long k) {
    const int n = online.size();

    // Build graph
    auto graph = vector<vector<Edge>>(n);
    for (const auto& edge : edges) {
      int u = edge[0], v = edge[1], w = edge[2];
      if (!online[u] || !online[v]) continue;
      graph[u].push_back({w, v});
    }

    // BFS, find path with all edge >= x
    auto costs = vector<long long>(n);
    const auto check = [n, k, &graph, &costs](long long x) -> bool {
      fill(costs.begin(), costs.end(), LLONG_MAX);
      Heap heap;
      costs[0] = 0;
      heap.push(State{0, 0});

      while (!heap.empty()) {
        auto [cost, node] = heap.top();
        heap.pop();

        // Early stop
        if (cost > k) return false;      // shortest path too long
        if (node == n - 1) return true;  // reachable

        // Relax
        if (costs[node] < cost) continue;

        // Traverse
        for (const auto [weight, nextNode] : graph[node]) {
          if (weight < x) continue;  // forbidden
          long long nextCost = cost + weight;
          if (costs[nextNode] <= nextCost) continue;  // Relax
          costs[nextNode] = nextCost;
          heap.push(State{nextCost, nextNode});
        }
      }

      return false;  // unreachable
    };

    // Edge case, check path existence
    if (!check(0)) return -1;

    // Binary search
    // check(lo-1) = true, check(lo=hi) = false.
    long long lo = 0, hi = k + 1;  // [0, k] is unknown
    while (lo < hi) {              // [lo, hi) is unknown
      long long mid = lo + (hi - lo) / 2;
      if (check(mid)) {
        lo = mid + 1;  // [mid+1, hi) is unknown
      } else {
        hi = mid;  // [lo, mid) is unknown
      }
    }

    return lo - 1;
  }
};

// Binary Search + Topology Sort + BFS
//
// Since the graph is a DAG,
// we can use topology sort instead of Dijkstra.
class Solution2 {
  using Edge = pair<int, int>;  // weight, node

 public:
  int findMaxPathScore(const vector<vector<int>>& edges, const vector<bool>& online, const long long k) {
    const int n = online.size();

    // Build graph
    auto graph = vector<vector<Edge>>(n);
    auto inDeg = vector<int>(n);
    for (const auto& edge : edges) {
      int u = edge[0], v = edge[1], w = edge[2];
      if (!online[u] || !online[v]) continue;
      graph[u].push_back({w, v});
      ++inDeg[v];
    }

    // Topology Sort
    auto order = vector<int>();
    order.reserve(n);
    for (int u = 0; u < n; ++u) {
      if (inDeg[u] == 0) order.push_back(u);
    }
    for (int i = 0; i < order.size(); ++i) {
      // Early stop
      if (order.size() == n) break;

      int u = order[i];
      for (auto [_, v] : graph[u]) {
        if (--inDeg[v] == 0) order.push_back(v);
      }
    }

    // BFS, find path with all edge >= x
    auto costs = vector<long long>(n);
    const auto check = [n, k, &graph, &order, &costs](long long x) -> bool {
      fill(costs.begin(), costs.end(), LLONG_MAX);
      costs[0] = 0;

      for (int node : order) {
        long long cost = costs[node];

        // Skip non-reachable node
        if (cost > k) continue;

        // Early stop
        if (node == n - 1) return cost <= k;

        // Relax
        if (costs[node] < cost) continue;

        // Traverse
        for (const auto [weight, nextNode] : graph[node]) {
          if (weight < x) continue;  // forbidden
          long long nextCost = cost + weight;
          if (costs[nextNode] <= nextCost) continue;  // Relax
          costs[nextNode] = nextCost;
        }
      }

      return false;  // unreachable
    };

    // Edge case, check path existence
    if (!check(0)) return -1;

    // Binary search
    // check(lo-1) = true, check(lo=hi) = false.
    long long lo = 0, hi = k + 1;  // [0, k] is unknown
    while (lo < hi) {              // [lo, hi) is unknown
      long long mid = lo + (hi - lo) / 2;
      if (check(mid)) {
        lo = mid + 1;  // [mid+1, hi) is unknown
      } else {
        hi = mid;  // [lo, mid) is unknown
      }
    }

    return lo - 1;
  }
};
