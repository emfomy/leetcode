// Source: https://leetcode.com/problems/shortest-path-with-at-most-k-consecutive-identical-characters
// Title: Shortest Path With At Most K Consecutive Identical Characters
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `n` representing the number of nodes in a **directed weighted** graph, numbered from 0 to `n - 1`. This is represented by a 2D integer array `edges`, where `edges[i] = [u_i, v_i, w_i]` represents a directed edge from node `u_i` to node `v_i` with weight `w_i`.
//
// You are also given a string `labels` of length `n`, where `labels[i]` is the character assigned to node `i`, and an integer `k`.
//
// Return the **minimum** **total** edge weight of a path from node 0 to node `n - 1` such that the concatenation of the labels of the nodes along the path contains **at most** `k` **consecutive** **identical** characters. If no valid path exists, return -1.
//
// **Example 1:**
//
// ```
// Input: n = 3, edges = [[0,1,1],[1,2,1],[0,2,3]], labels = "aab", k = 1
// Output: 3
// Explanation:
// The optimal valid path from node 0 to node 2 is as follows:
// - Use `edges[2] = [0, 2, 3]` to reach node 2 with a weight `w_i = 3`.
// The corresponding concatenation of labels is `"ab"`, which satisfies at most `k = 1` consecutive identical characters. Thus, the answer is 3.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 3, edges = [[0,1,1],[1,2,1],[0,2,3]], labels = "aab", k = 2
// Output: 2
// Explanation:
// The optimal valid path from node 0 to node 2 is as follows:
// - Use `edges[0] = [0, 1, 1]` to reach node 1 with weight `w_i = 1`.
// - Use `edges[1] = [1, 2, 1]` to reach node 2 with weight `w_i = 1`.
// The corresponding concatenation of labels is `"aab"`, which satisfies at most `k = 2` consecutive identical characters. Thus, the answer is 2.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 3, edges = [[0,1,1],[1,2,1]], labels = "aaa", k = 2
// Output: -1
// Explanation:
// There is no valid path from node 0 to node 2 that satisfies at most `k = 2` consecutive identical characters. Thus, the answer is -1.
// ```
//
// **Constraints:**
//
// - `1 <= n == labels.length <= 5 * 10^4`
// - `0 <= edges.length <= 5 * 10^4`
// - `edges[i] == [u_i, v_i, w_i]`
// - `0 <= u_i, v_i <= n - 1`
// - `u_i != v_i`
// - `1 <= w_i <= 10^4`
// - `labels` consists of lowercase English letters
// - `1 <= k <= 50`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <vector>

using namespace std;

// Dijkstra
//
// We also use trailing consecutive count in the state.
class Solution {
  using Edge = pair<int, int>;         // weight, node
  using State = tuple<int, int, int>;  // cost, node, consecutive count

  using Heap = priority_queue<State, vector<State>, greater<>>;  // min-heap

 public:
  int shortestPath(int n, const vector<vector<int>>& edges, const string& labels, int k) {
    const int src = 0, dst = n - 1;

    // Build graph
    auto graph = vector<vector<Edge>>(n);
    for (auto& edge : edges) {
      int u = edge[0], v = edge[1], w = edge[2];
      graph[u].push_back({w, v});
    }

    // Loop
    auto costs = vector(n, vector<int>(k, INT_MAX));
    Heap heap;
    costs[src][0] = 0;
    heap.push(State{0, src, 0});

    while (!heap.empty()) {
      auto [cost, node, count] = heap.top();
      heap.pop();

      // Early stop
      if (node == dst) return cost;

      // Relax
      if (costs[node][count] < cost) continue;

      // Traverse
      for (const auto [weight, nextNode] : graph[node]) {
        int nextCost = cost + weight;
        int nextCount = (labels[node] == labels[nextNode]) ? count + 1 : 0;
        if (nextCount == k) continue;                          // Too many consecutive
        if (costs[nextNode][nextCount] <= nextCost) continue;  // Relax
        costs[nextNode][nextCount] = nextCost;
        heap.push(State{nextCost, nextNode, nextCount});
      }
    }

    return -1;  // unreachable
  }
};
