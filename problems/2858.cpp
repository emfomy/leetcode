// Source: https://leetcode.com/problems/minimum-edge-reversals-so-every-node-is-reachable
// Title: Minimum Edge Reversals So Every Node Is Reachable
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a **simple directed graph** with `n` nodes labeled from `0` to `n - 1`. The graph would form a **tree** if its edges were bi-directional.
//
// You are given an integer `n` and a **2D** integer array `edges`, where `edges[i] = [u_i, v_i]` represents a **directed edge** going from node `u_i` to node `v_i`.
//
// An **edge reversal** changes the direction of an edge, i.e., a directed edge going from node `u_i` to node `v_i` becomes a directed edge going from node `v_i` to node `u_i`.
//
// For every node `i` in the range `[0, n - 1]`, your task is to **independently** calculate the **minimum** number of **edge reversals** required so it is possible to reach any other node starting from node `i` through a **sequence** of **directed edges**.
//
// Return an integer array `answer`, where `answer[i]` is the  **minimum** number of **edge reversals** required so it is possible to reach any other node starting from node `i` through a **sequence** of **directed edges**.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2023/08/26/image-20230826221104-3.png
//
// ```
// Input: n = 4, edges = [[2,0],[2,1],[1,3]]
// Output: [1,1,0,2]
// Explanation: The image above shows the graph formed by the edges.
// For node 0: after reversing the edge [2,0], it is possible to reach any other node starting from node 0.
// So, answer[0] = 1.
// For node 1: after reversing the edge [2,1], it is possible to reach any other node starting from node 1.
// So, answer[1] = 1.
// For node 2: it is already possible to reach any other node starting from node 2.
// So, answer[2] = 0.
// For node 3: after reversing the edges [1,3] and [2,1], it is possible to reach any other node starting from node 3.
// So, answer[3] = 2.
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2023/08/26/image-20230826225541-2.png
//
// ```
// Input: n = 3, edges = [[1,2],[2,0]]
// Output: [2,0,1]
// Explanation: The image above shows the graph formed by the edges.
// For node 0: after reversing the edges [2,0] and [1,2], it is possible to reach any other node starting from node 0.
// So, answer[0] = 2.
// For node 1: it is already possible to reach any other node starting from node 1.
// So, answer[1] = 0.
// For node 2: after reversing the edge [1, 2], it is possible to reach any other node starting from node 2.
// So, answer[2] = 1.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 10^5`
// - `edges.length == n - 1`
// - `edges[i].length == 2`
// - `0 <= u_i == edges[i][0] < n`
// - `0 <= v_i == edges[i][1] < n`
// - `u_i != v_i`
// - The input is generated suchthat if the edges were bi-directional, the graph would be a tree.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// DFS, O(N^2)
//
// Run DFS from each node
class Solution {
  using Bool = unsigned char;

  enum class Dir { OUT, IN };
  using enum Dir;

  struct Edge {
    int node;
    Dir direct;
  };

 public:
  vector<int> minEdgeReversals(int n, const vector<vector<int>>& edges) {
    // Build graph
    auto graph = vector<vector<Edge>>(n);
    for (auto& edge : edges) {
      int u = edge[0], v = edge[1];
      graph[u].push_back(Edge{v, OUT});
      graph[v].push_back(Edge{u, IN});
    }

    // DFS
    auto counts = vector<int>(n);
    for (int i = 0; i < n; ++i) {
      counts[i] = dfs(i, -1, graph);
    }

    return counts;
  }

  int dfs(int node, int from, const vector<vector<Edge>>& graph) {
    int count = 0;

    for (auto& [next, dir] : graph[node]) {
      if (next == from) continue;
      if (dir == IN) ++count;
      count += dfs(next, node, graph);
    }
    return count;
  }
};

// DFS, O(N)
//
// Here is the core idea:
// Run DFS on each root, computing the direction of each edge.
// The number of reversals are equal to the number of edges toward this this root.
//
// However, we can reuse the previous result to speed up the process.
// We first run the algorithm on node 0. We also count the inward edges during the algorithm.
// Next run another DFS from node 0.
// Instead of rerunning the algorithm from the new node,
// we update the direction of the edge we just walk through, and also the inward count.
// We also revert the result when we go back during the DFS.
class Solution2 {
  enum class Dir { OUT, IN };
  using enum Dir;

  struct Edge {
    int node;
    Dir direct;
  };

 public:
  vector<int> minEdgeReversals(int n, const vector<vector<int>>& edges) {
    const int m = edges.size();  // =n-1
    auto counts = vector<int>(n);

    // Build graph
    auto graph = vector<vector<Edge>>(n);
    for (int i = 0; i < m; ++i) {
      int u = edges[i][0], v = edges[i][1];
      graph[u].push_back(Edge{v, OUT});
      graph[v].push_back(Edge{u, IN});
    }

    // First DFS
    int count = dfs1(0, -1, graph);

    // Second DFS
    dfs2(0, -1, count, counts, graph);

    return counts;
  }

  int dfs1(int node, int from, const vector<vector<Edge>>& graph) {
    int count = 0;

    for (auto& [next, dir] : graph[node]) {
      if (next == from) continue;
      if (dir == IN) ++count;
      count += dfs1(next, node, graph);
    }
    return count;
  }

  void dfs2(int node, int from, int count, vector<int>& counts, const vector<vector<Edge>>& graph) {
    counts[node] = count;

    for (auto& [next, dir] : graph[node]) {
      if (next == from) continue;

      // Flip
      int nextCount = (dir == IN) ? count - 1 : count + 1;

      // Traversal
      dfs2(next, node, nextCount, counts, graph);
    }
  }
};
