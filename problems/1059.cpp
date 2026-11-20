// Source: https://leetcode.com/problems/all-paths-from-source-lead-to-destination
// Title: All Paths from Source Lead to Destination
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `edges` of a directed graph where `edges[i] = [a_i, b_i]` indicates there is an edge between nodes `a_i` and `b_i`, and two nodes `source` and `destination` of this graph, determine whether or not all paths starting from `source` eventually, end at `destination`, that is:
//
// - At least one path exists from the `source` node to the `destination` node
// - If a path exists from the `source` node to a node with no outgoing edges, then that node is equal to `destination`.
// - The number of possible paths from `source` to `destination` is a finite number.
//
// Return `true` if and only if all roads from `source` lead to `destination`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2019/03/16/485_example_1.png
//
// ```
// Input: n = 3, edges = [[0,1],[0,2]], source = 0, destination = 2
// Output: false
// Explanation: It is possible to reach and get stuck on both node 1 and node 2.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2019/03/16/485_example_2.png
//
// ```
// Input: n = 4, edges = [[0,1],[0,3],[1,2],[2,1]], source = 0, destination = 3
// Output: false
// Explanation: We have two possibilities: to end at node 3, or to loop over node 1 and node 2 indefinitely.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2019/03/16/485_example_3.png
//
// ```
// Input: n = 4, edges = [[0,1],[0,2],[1,3],[2,3]], source = 0, destination = 3
// Output: true
// ```
//
// **Constraints:**
//
// - `1 <= n <= 10^4`
// - `0 <= edges.length <= 10^4`
// - `edges.length == 2`
// - `0 <= a_i, b_i <= n - 1`
// - `0 <= source <= n - 1`
// - `0 <= destination <= n - 1`
// - The given graph may have self-loops and parallel edges.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// DFS
//
// Use three-color algorithm to detect cycle.
// Also check if all dead end is destination.
class Solution {
  enum class Color { WHITE, GRAY, BLACK };
  using enum Color;

  bool dfs(int curr, int dest, bool& found, vector<Color>& colors, const vector<vector<int>>& graph) {
    // Detect cycle
    if (colors[curr] == GRAY) return false;

    // Visited
    if (colors[curr] == BLACK) return true;

    // Check dead end
    if (graph[curr].empty()) {
      colors[curr] = BLACK;
      if (curr == dest) found = true;
      return curr == dest;
    }

    // Traverse
    colors[curr] = GRAY;
    for (int next : graph[curr]) {
      if (!dfs(next, dest, found, colors, graph)) return false;
    }
    colors[curr] = BLACK;

    return true;
  }

 public:
  bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {
    // Build graph
    auto graph = vector<vector<int>>(n);
    for (const auto& edge : edges) {
      graph[edge[0]].push_back(edge[1]);
    }

    // DFS
    auto colors = vector<Color>(n, WHITE);
    bool found = false;
    bool valid = dfs(source, destination, found, colors, graph);

    return valid && found;
  }
};

// DFS
//
// Use three-color algorithm to detect cycle.
// Also check if all dead end is destination.
//
// We don't need to check if the path exist,
// since the DFS only stop when reach a dead end,
class Solution2 {
  enum class Color { WHITE, GRAY, BLACK };
  using enum Color;

  bool dfs(int curr, int dest, vector<Color>& colors, const vector<vector<int>>& graph) {
    // Detect cycle
    if (colors[curr] == GRAY) return false;

    // Visited
    if (colors[curr] == BLACK) return true;

    // Check dead end
    if (graph[curr].empty()) {
      colors[curr] = BLACK;
      return curr == dest;
    }

    // Traverse
    colors[curr] = GRAY;
    for (int next : graph[curr]) {
      if (!dfs(next, dest, colors, graph)) return false;
    }
    colors[curr] = BLACK;

    return true;
  }

 public:
  bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {
    // Build graph
    auto graph = vector<vector<int>>(n);
    for (const auto& edge : edges) {
      graph[edge[0]].push_back(edge[1]);
    }

    // DFS
    auto colors = vector<Color>(n, WHITE);
    return dfs(source, destination, colors, graph);
  }
};
