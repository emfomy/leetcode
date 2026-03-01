// Source: https://leetcode.com/problems/network-delay-time
// Title: Network Delay Time
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a network of `n` nodes, labeled from `1` to `n`. You are also given `times`, a list of travel times as directed edges `times[i] = (u_i, v_i, w_i)`, where `u_i` is the source node, `v_i` is the target node, and `w_i` is the time it takes for a signal to travel from source to target.
//
// We will send a signal from a given node `k`. Return the **minimum** time it takes for all the `n` nodes to receive the signal. If it is impossible for all the `n` nodes to receive the signal, return `-1`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2019/05/23/931_example_1.png
//
// ```
// Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
// Output: 2
// ```
//
// **Example 2:**
//
// ```
// Input: times = [[1,2,1]], n = 2, k = 1
// Output: 1
// ```
//
// **Example 3:**
//
// ```
// Input: times = [[1,2,1]], n = 2, k = 2
// Output: -1
// ```
//
// **Constraints:**
//
// - `1 <= k <= n <= 100`
// - `1 <= times.length <= 6000`
// - `times[i].length == 3`
// - `1 <= u_i, v_i <= n`
// - `u_i != v_i`
// - `0 <= w_i <= 100`
// - All the pairs `(u_i, v_i)` are **unique**. (i.e., no multiple edges.)
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <climits>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

// BFS + Heap (Dijkstra), O(E logN)
class Solution {
  struct Edge {
    int dest;    // dest node
    int weight;  // edge weight
  };

  using HeapItem = pair<int, int>;  // cost, node

 public:
  int networkDelayTime(const vector<vector<int>>& times, const int n, int k) {
    // Convert to 0-indexed
    --k;

    // Guard
    if (n <= 0 || k < 0 || k >= n) return -1;

    // Init Graph
    auto graph = vector(n, vector<Edge>());
    for (const auto& edge : times) {
      const int u = edge[0] - 1, v = edge[1] - 1, w = edge[2];
      graph[u].push_back({v, w});
    }

    // BFS
    auto heap = priority_queue<HeapItem, vector<HeapItem>, greater<HeapItem>>();  // min-heap
    auto costs = vector<int>(n, INT_MAX);                                         // min-cost for all nodes
    heap.emplace(0, k);
    costs[k] = 0;
    while (!heap.empty()) {
      auto [cost, node] = heap.top();
      heap.pop();

      // Relax
      if (costs[node] < cost) continue;

      // Traversal
      for (auto [nextNode, weight] : graph[node]) {
        int nextCost = cost + weight;
        if (costs[nextNode] <= nextCost) continue;  // Relax
        costs[nextNode] = nextCost;
        heap.emplace(nextCost, nextNode);
      }
    }

    // Answer
    int maxCost = *max_element(costs.cbegin(), costs.cend());
    return maxCost == INT_MAX ? -1 : maxCost;
  }
};

// Floyd–Warshall, O(N^3)
class Solution2 {
  constexpr static int kInf = INT_MAX / 2;

 public:
  int networkDelayTime(const vector<vector<int>>& times, const int n, int k) {
    // Convert to 0-indexed
    --k;

    // Guard
    if (n <= 0 || k < 0 || k >= n) return -1;

    // Init Graph
    auto graph = vector(n, vector<int>(n, kInf));
    for (auto u = 0; u < n; ++u) {
      graph[u][u] = 0;
    }
    for (const auto& edge : times) {
      const int u = edge[0] - 1, v = edge[1] - 1, w = edge[2];
      graph[u][v] = min(graph[u][v], w);
    }

    // Floyd–Warshall
    for (int i = 0; i < n; ++i) {
      for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
          graph[u][v] = min(graph[u][v], graph[u][i] + graph[i][v]);
        }
      }
    }

    // Answer
    int maxCost = *max_element(graph[k].cbegin(), graph[k].cend());
    return maxCost >= kInf ? -1 : maxCost;
  }
};

// BFS (Dense Dijkstra), O(N^2), used when E ~= N^2
class Solution3 {
  constexpr static int kInf = INT_MAX / 2;

 public:
  int networkDelayTime(const vector<vector<int>>& times, const int n, int k) {
    // Convert to 0-indexed
    --k;

    // Guard
    if (n <= 0 || k < 0 || k >= n) return -1;

    // Init Graph
    auto graph = vector(n, vector<int>(n, kInf));
    for (auto u = 0; u < n; ++u) {
      graph[u][u] = 0;
    }
    for (const auto& edge : times) {
      const int u = edge[0] - 1, v = edge[1] - 1, w = edge[2];
      graph[u][v] = min(graph[u][v], w);
    }

    // BFS
    auto costs = vector<int>(n, kInf);
    auto dones = vector<bool>(n, false);
    costs[k] = 0;
    for (int step = 0; step < n; ++step) {
      // Find minimal non-finished node
      int u = -1;
      int cost = kInf;
      for (int i = 0; i < n; ++i) {
        if (!dones[i] && costs[i] < cost) {
          u = i;
          cost = costs[i];
        }
      }

      // Guard
      if (u == -1) break;

      // Update
      dones[u] = true;

      // Traversal
      for (int v = 0; v < n; ++v) {
        if (!dones[v]) {
          costs[v] = min(costs[v], costs[u] + graph[u][v]);
        }
      }
    }

    // Answer
    int maxCost = *max_element(costs.cbegin(), costs.cend());
    return maxCost >= kInf ? -1 : maxCost;
  }
};
