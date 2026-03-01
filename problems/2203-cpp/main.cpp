// Source: https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths
// Title: Minimum Weighted Subgraph With the Required Paths
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `n` denoting the number of nodes of a **weighted directed** graph. The nodes are numbered from `0` to `n-1`.
//
// You are also given a 2D integer array `edges` where `edges[i] = [from_i, to_i, weight_i]` denotes that there exists a **directed** edge from `from_i` to `to_i` with weight `weight_i`.
//
// Lastly, you are given three **distinct** integers `src1`, `src2`, and `dest` denoting three distinct nodes of the graph.
//
// Return the **minimum weight** of a subgraph of the graph such that it is **possible** to reach `dest` from both `src1` and `src2` via a set of edges of this subgraph. In case such a subgraph does not exist, return `-1`.
//
// A **subgraph** is a graph whose vertices and edges are subsets of the original graph. The **weight** of a subgraph is the sum of weights of its constituent edges.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2022/02/17/example1drawio.png
//
// ```
// Input: n = 6, edges = [[0,2,2],[0,5,6],[1,0,3],[1,4,5],[2,1,1],[2,3,3],[2,3,4],[3,4,2],[4,5,1]], src1 = 0, src2 = 1, dest = 5
// Output: 9
// Explanation:
// The above figure represents the input graph.
// The blue edges represent one of the subgraphs that yield the optimal answer.
// Note that the subgraph [[1,0,3],[0,5,6]] also yields the optimal answer. It is not possible to get a subgraph with less weight satisfying all the constraints.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2022/02/17/example2-1drawio.png
//
// ```
// Input: n = 3, edges = [[0,1,1],[2,1,1]], src1 = 0, src2 = 1, dest = 2
// Output: -1
// Explanation:
// The above figure represents the input graph.
// It can be seen that there does not exist any path from node 1 to node 2, hence there are no subgraphs satisfying all the constraints.
// ```
//
// **Constraints:**
//
// - `3 <= n <= 10^5`
// - `0 <= edges.length <= 10^5`
// - `edges[i].length == 3`
// - `0 <= from_i, to_i, src1, src2, dest <= n-1`
// - `from_i != to_i`
// - `src1`, `src2`, and `dest` are pairwise distinct.
// - `1 <= weight[i] <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

// BFS + Heap (Dijkstra)
//
// First run two Dijkstra to find the min cost from both source to all nodes.
//
// Next add both cost (as the initial cost) and run Dijkstra again.
// This cost represent the min cost of the subgraph to each nodes.
class Solution {
  constexpr static int64_t kInf = 1e11;

  struct Edge {
    int dest;  // dest node
    int64_t weight;
  };

  using HeapItem = pair<int64_t, int>;  // cost, node
  using Heap = priority_queue<HeapItem, vector<HeapItem>, greater<HeapItem>>;

 public:
  int64_t minimumWeight(int n, const vector<vector<int>>& edges, int src1, int src2, int dest) {
    // Guard
    if (n < 0) return 0;

    // Init graph
    auto graph = vector(n, vector<Edge>());
    for (const auto& edge : edges) {
      int u = edge[0], v = edge[1], w = edge[2];
      graph[u].push_back({v, w});
    }

    // Dijkstra for src1
    auto cost1 = vector<int64_t>(n, kInf);
    {
      auto heap1 = Heap();
      cost1[src1] = 0;
      heap1.emplace(0, src1);
      dijkstra(graph, cost1, heap1);
      if (cost1[dest] >= kInf) return -1;
    }

    // Dijkstra for src2
    auto cost2 = vector<int64_t>(n, kInf);
    {
      auto heap2 = Heap();
      cost2[src2] = 0;
      heap2.emplace(0, src2);
      dijkstra(graph, cost2, heap2);
      if (cost2[dest] >= kInf) return -1;
    }

    // Dijkstra for both
    auto cost12 = vector<int64_t>(n);
    {
      auto heap12 = Heap();
      for (int u = 0; u < n; ++u) {
        cost12[u] = cost1[u] + cost2[u];
        if (cost12[u] >= kInf) continue;  // skip unreachable nodes
        heap12.emplace(cost12[u], u);
      }
      dijkstra(graph, cost12, heap12, dest);
    }

    return cost12[dest];
  }

 private:
  void dijkstra(const vector<vector<Edge>>& graph, vector<int64_t>& costs, Heap& heap, int target = -1) {
    int n = graph.size();

    while (!heap.empty()) {
      auto [cost, node] = heap.top();
      heap.pop();

      // Early stop
      if (node == target) break;

      // Relax
      if (costs[node] < cost) continue;
      costs[node] = cost;

      // Traversal
      for (auto [nextNode, weight] : graph[node]) {
        int64_t nextCost = cost + weight;
        if (costs[nextNode] <= nextCost) continue;
        costs[nextNode] = nextCost;
        heap.emplace(nextCost, nextNode);
      }
    }
  }
};
