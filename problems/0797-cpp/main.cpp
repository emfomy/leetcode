// Source: https://leetcode.com/problems/all-paths-from-source-to-target
// Title: All Paths From Source to Target
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a directed acyclic graph (**DAG**) of `n` nodes labeled from `0` to `n - 1`, find all possible paths from node `0` to node `n - 1` and return them in **any order**.
//
// The graph is given as follows: `graph[i]` is a list of all nodes you can visit from node `i` (i.e., there is a directed edge from node `i` to node `graph[i][j]`).
//
// **Example 1:**
// <img alt="" src="https://assets.leetcode.com/uploads/2020/09/28/all_1.jpg" style="width: 242px; height: 242px;">
//
// ```
// Input: graph = [[1,2],[3],[3],[]]
// Output: [[0,1,3],[0,2,3]]
// Explanation: There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.
// ```
//
// **Example 2:**
// <img alt="" src="https://assets.leetcode.com/uploads/2020/09/28/all_2.jpg" style="width: 423px; height: 301px;">
//
// ```
// Input: graph = [[4,3,1],[3,2,4],[3],[4],[]]
// Output: [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]
// ```
//
// **Constraints:**
//
// - `n == graph.length`
// - `2 <= n <= 15`
// - `0 <= graph[i][j] < n`
// - `graph[i][j] != i` (i.e., there will be no self-loops).
// - All the elements of `graph[i]` are **unique**.
// - The input graph is **guaranteed** to be a **DAG**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// DFS (Recursion)
class Solution {
 public:
  vector<vector<int>> allPathsSourceTarget(const vector<vector<int>>& graph) {
    const int n = graph.size();
    if (n == 0) return {};

    auto path = vector<int>();
    auto allPaths = vector<vector<int>>();
    dfs(0, n - 1, path, allPaths, graph);

    return allPaths;
  }

 private:
  void dfs(int curr, int target, vector<int>& path, vector<vector<int>>& allPaths, const vector<vector<int>>& graph) {
    path.push_back(curr);

    if (curr == target) {
      // Reach target
      allPaths.push_back(path);  // copy
    } else {
      // Find next
      for (int next : graph[curr]) {
        dfs(next, target, path, allPaths, graph);
      }
    }

    path.pop_back();
  }
};
