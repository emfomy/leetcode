// Source: https://leetcode.com/problems/maximum-path-quality-of-a-graph
// Title: Maximum Path Quality of a Graph
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is an **undirected** graph with `n` nodes numbered from `0` to `n - 1` (**inclusive**). You are given a **0-indexed** integer array `values` where `values[i]` is the **value **of the `i^th` node. You are also given a **0-indexed** 2D integer array `edges`, where each `edges[j] = [u_j, v_j, time_j]` indicates that there is an undirected edge between the nodes `u_j` and `v_j`,_ and it takes `time_j` seconds to travel between the two nodes. Finally, you are given an integer `maxTime`.
//
// A **valid** **path** in the graph is any path that starts at node `0`, ends at node `0`, and takes **at most** `maxTime` seconds to complete. You may visit the same node multiple times. The **quality** of a valid path is the **sum** of the values of the **unique nodes** visited in the path (each node's value is added **at most once** to the sum).
//
// Return the **maximum** quality of a valid path.
//
// **Note:** There are **at most four** edges connected to each node.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/10/19/ex1drawio.png
//
// ```
// Input: values = [0,32,10,43], edges = [[0,1,10],[1,2,15],[0,3,10]], maxTime = 49
// Output: 75
// Explanation:
// One possible path is 0 -> 1 -> 0 -> 3 -> 0. The total time taken is 10 + 10 + 10 + 10 = 40 <= 49.
// The nodes visited are 0, 1, and 3, giving a maximal path quality of 0 + 32 + 43 = 75.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/10/19/ex2drawio.png
//
// ```
// Input: values = [5,10,15,20], edges = [[0,1,10],[1,2,10],[0,3,10]], maxTime = 30
// Output: 25
// Explanation:
// One possible path is 0 -> 3 -> 0. The total time taken is 10 + 10 = 20 <= 30.
// The nodes visited are 0 and 3, giving a maximal path quality of 5 + 20 = 25.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/10/19/ex31drawio.png
//
// ```
// Input: values = [1,2,3,4], edges = [[0,1,10],[1,2,11],[2,3,12],[1,3,13]], maxTime = 50
// Output: 7
// Explanation:
// One possible path is 0 -> 1 -> 3 -> 1 -> 0. The total time taken is 10 + 13 + 13 + 10 = 46 <= 50.
// The nodes visited are 0, 1, and 3, giving a maximal path quality of 1 + 2 + 4 = 7.
// ```
//
// **Constraints:**
//
// - `n == values.length`
// - `1 <= n <= 1000`
// - `0 <= values[i] <= 10^8`
// - `0 <= edges.length <= 2000`
// - `edges[j].length == 3 `
// - `0 <= u_j < v_j <= n - 1`
// - `10 <= time_j, maxTime <= 100`
// - All the pairs `[u_j, v_j]` are **unique**.
// - There are **at most four** edges connected to each node.
// - The graph may not be connected.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Backtracking + DFS
//
// Since 10 <= time_j, maxTime <= 100, we will go at most 10 steps.
// We just loop through all possible path within `maxTime` limit.
class Solution {
 public:
  int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
    int n = values.size();

    // Init graph
    auto graph = vector<vector<pair<int, int>>>(n);  // from -> (to, time)
    for (const auto& edge : edges) {
      const int u = edge[0], v = edge[1], t = edge[2];
      graph[u].emplace_back(v, t);
      graph[v].emplace_back(u, t);
    }

    // DFS
    int maxVal = 0;
    vector<int> visitCount(n, 0);
    dfs(0, 0, 0, visitCount, maxVal, maxTime, values, graph);

    return maxVal;
  }

 private:
  void dfs(const int currNode, int currVal, const int currTime,                    //
           vector<int>& visitCount,                                                //
           int& maxVal, const int maxTime,                                         //
           const vector<int>& values, const vector<vector<pair<int, int>>>& graph  //
  ) {
    // Run out of time
    if (currTime > maxTime) return;

    // Gain value
    if (visitCount[currNode] == 0) {
      currVal += values[currNode];
    }
    visitCount[currNode]++;

    // Go back to start
    if (currNode == 0) {
      maxVal = max(maxVal, currVal);
    }

    // Traverse
    for (auto [nextNode, edgeCost] : graph[currNode]) {
      dfs(nextNode, currVal, currTime + edgeCost, visitCount, maxVal, maxTime, values, graph);
    }

    visitCount[currNode]--;
  }
};
