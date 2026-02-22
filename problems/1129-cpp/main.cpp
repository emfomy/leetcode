// Source: https://leetcode.com/problems/shortest-path-with-alternating-colors
// Title: Shortest Path with Alternating Colors
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `n`, the number of nodes in a directed graph where the nodes are labeled from `0` to `n - 1`. Each edge is red or blue in this graph, and there could be self-edges and parallel edges.
//
// You are given two arrays `redEdges` and `blueEdges` where:
//
// - `redEdges[i] = [a_i, b_i]` indicates that there is a directed red edge from node `a_i` to node `b_i` in the graph, and
// - `blueEdges[j] = [u_j, v_j]` indicates that there is a directed blue edge from node `u_j` to node `v_j` in the graph.
//
// Return an array `answer` of length `n`, where each `answer[x]` is the length of the shortest path from node `0` to node `x` such that the edge colors alternate along the path, or `-1` if such a path does not exist.
//
// **Example 1:**
//
// ```
// Input: n = 3, redEdges = [[0,1],[1,2]], blueEdges = []
// Output: [0,1,-1]
// ```
//
// **Example 2:**
//
// ```
// Input: n = 3, redEdges = [[0,1]], blueEdges = [[2,1]]
// Output: [0,1,-1]
// ```
//
// **Constraints:**
//
// - `1 <= n <= 100`
// - `0 <= redEdges.length,blueEdges.length <= 400`
// - `redEdges[i].length == blueEdges[j].length == 2`
// - `0 <= a_i, b_i, u_j, v_j < n`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <queue>
#include <vector>

using namespace std;

// BFS
class Solution {
  enum Color { RED = 0, BLUE = 1 };

 public:
  vector<int> shortestAlternatingPaths(     //
      const int n,                          //
      const vector<vector<int>>& redEdges,  //
      const vector<vector<int>>& blueEdges  //
  ) {
    // Init graph
    vector<vector<int>> graphs[2];  // graph for each node & color;
    graphs[RED].resize(n);
    graphs[BLUE].resize(n);
    for (const auto& edge : redEdges) {
      const int a = edge[0], b = edge[1];
      graphs[RED][a].push_back(b);
    }
    for (const auto& edge : blueEdges) {
      const int a = edge[0], b = edge[1];
      graphs[BLUE][a].push_back(b);
    }

    // BFS
    vector<int> dists[2];  // distances for each node & color
    dists[RED].assign(n, -1);
    dists[BLUE].assign(n, -1);

    auto que = queue<pair<int, Color>>();  // node, previous color
    dists[RED][0] = 0;
    dists[BLUE][0] = 0;
    que.emplace(0, RED);
    que.emplace(0, BLUE);

    while (!que.empty()) {
      const auto [node, color] = que.front();
      que.pop();

      const int nextDist = dists[color][node] + 1;
      const Color nextColor = Color(1 - color);  // flip the color
      for (const int nextNode : graphs[nextColor][node]) {
        if (dists[nextColor][nextNode] == -1) {
          dists[nextColor][nextNode] = nextDist;
          que.emplace(nextNode, nextColor);
        }
      }
    }

    // Answer
    auto ans = vector<int>(n);
    for (int i = 0; i < n; ++i) {
      const int redDist = dists[RED][i] == -1 ? INT_MAX : dists[RED][i];
      const int blueDist = dists[BLUE][i] == -1 ? INT_MAX : dists[BLUE][i];
      ans[i] = min(redDist, blueDist);
      if (ans[i] == INT_MAX) ans[i] = -1;
    }

    return ans;
  }
};
