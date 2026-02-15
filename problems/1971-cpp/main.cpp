// Source: https://leetcode.com/problems/find-if-path-exists-in-graph
// Title: Find if Path Exists in Graph
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a **bi-directional** graph with `n` vertices, where each vertex is labeled from `0` to `n - 1` (**inclusive**). The edges in the graph are represented as a 2D integer array `edges`, where each `edges[i] = [u_i, v_i]` denotes a bi-directional edge between vertex `u_i` and vertex `v_i`. Every vertex pair is connected by **at most one** edge, and no vertex has an edge to itself.
//
// You want to determine if there is a **valid path** that exists from vertex `source` to vertex `destination`.
//
// Given `edges` and the integers `n`, `source`, and `destination`, return `true` if there is a **valid path** from `source` to `destination`, or `false` otherwise.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/08/14/validpath-ex1.png
//
// ```
// Input: n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
// Output: true
// Explanation: There are two paths from vertex 0 to vertex 2:
// - 0 → 1 → 2
// - 0 → 2
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/08/14/validpath-ex2.png
//
// ```
// Input: n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
// Output: false
// Explanation: There is no path from vertex 0 to vertex 5.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 2 * 10^5`
// - `0 <= edges.length <= 2 * 10^5`
// - `edges[i].length == 2`
// - `0 <= u_i, v_i <= n - 1`
// - `u_i != v_i`
// - `0 <= source, destination <= n - 1`
// - There are no duplicate edges.
// - There are no self edges.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <vector>

using namespace std;

// BFS
class Solution {
 public:
  bool validPath(const int n, const vector<vector<int>>& edges, const int source, const int destination) {
    // Edge case
    if (source == destination) return true;

    // Init graph
    auto graph = vector<vector<int>>(n);
    for (auto& edge : edges) {
      const int u = edge[0], v = edge[1];
      graph[u].push_back(v);
      graph[v].push_back(u);
    }

    // BFS
    auto visited = vector<bool>(n);
    auto que = queue<int>();
    que.push(source);
    visited[source] = true;

    while (!que.empty()) {
      const int curr = que.front();
      que.pop();

      for (const int next : graph[curr]) {
        // Found
        if (next == destination) return true;

        // Visited
        if (visited[next]) continue;

        // Next
        visited[next] = true;
        que.push(next);
      }
    }

    return false;
  }
};
