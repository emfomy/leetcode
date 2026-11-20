// Source: https://leetcode.com/problems/add-edges-to-make-degrees-of-all-nodes-even
// Title: Add Edges to Make Degrees of All Nodes Even
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is an **undirected** graph consisting of `n` nodes numbered from `1` to `n`. You are given the integer `n` and a **2D** array `edges` where `edges[i] = [a_i, b_i]` indicates that there is an edge between nodes `a_i` and `b_i`. The graph can be disconnected.
//
// You can add **at most** two additional edges (possibly none) to this graph so that there are no repeated edges and no self-loops.
//
// Return `true` if it is possible to make the degree of each node in the graph even, otherwise return `false`.
//
// The degree of a node is the number of edges connected to it.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2022/10/26/agraphdrawio.png
//
// ```
// Input: n = 5, edges = [[1,2],[2,3],[3,4],[4,2],[1,4],[2,5]]
// Output: true
// Explanation: The above diagram shows a valid way of adding an edge.
// Every node in the resulting graph is connected to an even number of edges.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2022/10/26/aagraphdrawio.png
//
// ```
// Input: n = 4, edges = [[1,2],[3,4]]
// Output: true
// Explanation: The above diagram shows a valid way of adding two edges.```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2022/10/26/aaagraphdrawio.png
//
// ```
// Input: n = 4, edges = [[1,2],[1,3],[1,4]]
// Output: false
// Explanation: It is not possible to obtain a valid graph with adding at most 2 edges.```
//
// **Constraints:**
//
// - `3 <= n <= 10^5`
// - `2 <= edges.length <= 10^5`
// - `edges[i].length == 2`
// - `1 <= a_i, b_i <= n`
// - `a_i != b_i`
// - There are no repeated edges.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

// First count the degree of all nodes.
//
// If all are even, then it's done.
// If more than 4 nodes are odd, then it's impossible.
//
// If only 2 odds, then check if they already has an edge.
// If not, then connect that edge;
// otherwise, find a common non-connected node and add two edges to that node.
// If there is such node, then the union of the two node's neighbor must be all the node.
//
// If 4 odds, then check if there is two distinct pairs without edges.
// If so, then connect that edges; otherwise, it is impossible.
class Solution {
 public:
  bool isPossible(int n, vector<vector<int>>& edges) {
    // Init graph
    auto graph = vector<unordered_set<int>>(n);
    for (auto& edge : edges) {
      auto u = edge[0] - 1, v = edge[1] - 1;
      graph[u].insert(v);
      graph[v].insert(u);
    }

    // Find node with odd degrees
    auto oddNodes = vector<int>();
    oddNodes.reserve(4);
    for (int i = 0; i < n; ++i) {
      if (graph[i].size() % 2 == 1) {
        if (oddNodes.size() >= 4) return false;  // to many odd nodes
        oddNodes.push_back(i);
      }
    }

    // Try to connect
    const int oddCount = oddNodes.size();
    if (oddCount == 0) {  // count = 0
      return true;
    } else if (oddCount == 2) {  // count = 2
      int a = oddNodes[0], b = oddNodes[1];

      // (a, b) has no edge
      if (!graph[a].contains(b)) return true;

      // Find 3rd node
      for (int i = 0; i < n; ++i) {
        if (a == i || b == i) continue;
        if (!graph[a].contains(i) && !graph[b].contains(i)) return true;
      }
    } else if (oddCount == 4) {  // count = 4
      int a = oddNodes[0], b = oddNodes[1], c = oddNodes[2], d = oddNodes[3];
      if (!graph[a].contains(b) && !graph[c].contains(d)) return true;
      if (!graph[a].contains(c) && !graph[b].contains(d)) return true;
      if (!graph[a].contains(d) && !graph[b].contains(c)) return true;
    }

    return false;
  }
};
