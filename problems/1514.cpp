// Source: https://leetcode.com/problems/path-with-maximum-probability
// Title: Path with Maximum Probability
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an undirected weighted graph of`n`nodes (0-indexed), represented by an edge list where`edges[i] = [a, b]`is an undirected edge connecting the nodes`a`and`b`with a probability of success of traversing that edge`succProb[i]`.
//
// Given two nodes`start`and`end`, find the path with the maximum probability of success to go from`start`to`end`and return its success probability.
//
// If there is no path from`start`to`end`, **return0**. Your answer will be accepted if it differs from the correct answer by at most **1e-5**.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2019/09/20/1558_ex1.png
//
// ```
// Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
// Output: 0.25000
// Explanation:There are two paths from start to end, one having a probability of success = 0.2 and the other has 0.5 * 0.5 = 0.25.
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2019/09/20/1558_ex2.png
//
// ```
// Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.3], start = 0, end = 2
// Output: 0.30000
// ```
//
// **Example 3:**
//
// https://assets.leetcode.com/uploads/2019/09/20/1558_ex3.png
//
// ```
// Input: n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
// Output: 0.00000
// Explanation:There is no path between 0 and 2.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 10^4`
// - `0 <= start, end < n`
// - `start != end`
// - `0 <= a, b < n`
// - `a != b`
// - `0 <= succProb.length == edges.length <= 2*10^4`
// - `0 <= succProb[i] <= 1`
// - There is at most one edge between every two nodes.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <vector>

using namespace std;

// Dijkstra
class Solution {
  using Edge = pair<double, int>;      // weight, to
  using BFSState = pair<double, int>;  // prob, node

  using Heap = priority_queue<BFSState>;  // max-heap

 public:
  double maxProbability(                 //
      const int n,                       //
      const vector<vector<int>>& edges,  //
      const vector<double>& succProb,    //
      const int startNode,               //
      const int endNode                  //
  ) {
    const int m = edges.size();

    // Build graph
    auto graph = vector<vector<Edge>>(n);
    for (int i = 0; i < m; ++i) {
      int u = edges[i][0], v = edges[i][1];
      double w = succProb[i];
      graph[u].push_back(Edge{w, v});
      graph[v].push_back(Edge{w, u});
    }

    // Prepare
    auto probs = vector<double>(n, 0.0);
    Heap heap;
    probs[startNode] = 1.0;
    heap.push(BFSState{1.0, startNode});

    // Loop
    while (!heap.empty()) {
      const auto [prob, u] = heap.top();
      heap.pop();

      // Early Stop
      if (u == endNode) return prob;

      // Relax
      if (probs[u] > prob) continue;

      // Traversal
      for (const auto [w, v] : graph[u]) {
        double nextProb = prob * w;
        if (probs[v] >= nextProb) continue;  // relax
        probs[v] = nextProb;
        heap.push(BFSState{nextProb, v});
      }
    }

    return 0.0;  // unreachable
  }
};

// Bellman-Ford
class Solution2 {
 public:
  double maxProbability(                 //
      const int n,                       //
      const vector<vector<int>>& edges,  //
      const vector<double>& succProb,    //
      const int startNode,               //
      const int endNode                  //
  ) {
    const int m = edges.size();

    // Prepare
    auto probs = vector<double>(n, 0.0);
    probs[startNode] = 1.0;

    // Loop
    for (int iter = 0; iter < n - 1; ++iter) {
      bool updated = false;

      for (int i = 0; i < m; ++i) {
        int u = edges[i][0], v = edges[i][1];
        double w = succProb[i];

        // Skip
        if (probs[u] == probs[v]) continue;

        // Ensure prob(u) > prob(v)
        if (probs[u] < probs[v]) swap(u, v);

        // Update
        if (probs[v] < probs[u] * w) {
          updated = true;
          probs[v] = probs[u] * w;
        }
      }

      if (!updated) break;
    }

    return probs[endNode];
  }
};
