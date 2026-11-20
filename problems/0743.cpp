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
#include <queue>
#include <vector>

using namespace std;

// Bellman-Ford
class Solution {
 public:
  int networkDelayTime(const vector<vector<int>>& times, int n, int k) {
    --k;
    if (n < 0 || k < 0 || k >= n) return -1;

    auto costs = vector<int>(n, INT_MAX);
    costs[k] = 0;

    for (int iter = 0; iter < n - 1; ++iter) {
      bool updated = false;

      for (const vector<int>& edge : times) {
        int u = edge[0] - 1, v = edge[1] - 1, w = edge[2];
        if (costs[u] == INT_MAX) continue;
        int nextCost = costs[u] + w;
        if (costs[v] > nextCost) {
          costs[v] = nextCost;
          updated = true;
        }
      }

      // Early Stop
      if (!updated) break;
    }

    int maxDelay = *max_element(costs.cbegin(), costs.cend());
    return maxDelay == INT_MAX ? -1 : maxDelay;
  }
};

// Dijkstra
class Solution2 {
  using Edge = pair<int, int>;   // weight, node
  using State = pair<int, int>;  // cost, node

  using Heap = priority_queue<State, vector<State>, greater<>>;  // min-heap

 public:
  int networkDelayTime(const vector<vector<int>>& times, int n, int k) {
    --k;
    if (n < 0 || k < 0 || k >= n) return -1;

    // Build graph
    auto graph = vector<vector<Edge>>(n);
    for (const vector<int>& edge : times) {
      int u = edge[0] - 1, v = edge[1] - 1, w = edge[2];
      graph[u].push_back(Edge{w, v});
    }

    // Loop
    auto costs = vector<int>(n, INT_MAX);
    Heap heap;
    costs[k] = 0;
    heap.push(State{0, k});

    while (!heap.empty()) {
      const auto [cost, u] = heap.top();
      heap.pop();

      // Relax
      if (costs[u] < cost) continue;

      // Traversal
      for (const auto [w, v] : graph[u]) {
        int nextCost = cost + w;
        if (costs[v] <= nextCost) continue;  // relax
        costs[v] = nextCost;
        heap.push(State{nextCost, v});
      }
    }

    int maxDelay = *max_element(costs.cbegin(), costs.cend());
    return maxDelay == INT_MAX ? -1 : maxDelay;
  }
};
