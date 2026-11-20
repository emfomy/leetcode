// Source: https://leetcode.com/problems/detect-cycles-in-2d-grid
// Title: Detect Cycles in 2D Grid
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a 2D array of characters `grid` of size `m x n`, you need to find if there exists any cycle consisting of the **same value** in `grid`.
//
// A cycle is a path of **length 4 or more** in the grid that starts and ends at the same cell. From a given cell, you can move to one of the cells adjacent to it - in one of the four directions (up, down, left, or right), if it has the **same value** of the current cell.
//
// Also, you cannot move to the cell that you visited in your last move. For example, the cycle `(1, 1) -> (1, 2) -> (1, 1)` is invalid because from `(1, 2)` we visited `(1, 1)` which was the last visited cell.
//
// Return `true` if any cycle of the same value exists in `grid`, otherwise, return `false`.
//
// **Example 1:**
//
// **https://assets.leetcode.com/uploads/2020/07/15/1.png**
//
// ```
// Input: grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
// Output: true
// Explanation: There are two valid cycles shown in different colors in the image below:
// https://assets.leetcode.com/uploads/2020/07/15/11.png
// ```
//
// **Example 2:**
//
// **https://assets.leetcode.com/uploads/2020/07/15/22.png**
//
// ```
// Input: grid = [["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]]
// Output: true
// Explanation: There is only one valid cycle highlighted in the image below:
// https://assets.leetcode.com/uploads/2020/07/15/2.png
// ```
//
// **Example 3:**
//
// **https://assets.leetcode.com/uploads/2020/07/15/3.png**
//
// ```
// Input: grid = [["a","b","b"],["b","z","b"],["b","b","a"]]
// Output: false
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 500`
// - `grid` consists only of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// Union-Find
//
// We first create a graph from the grid by connecting adjacent cells with the same letter.
// Next loop for all edges and use union-find to find the connected component.
// If an edges is connected to two cells that are already in the same connected component,
// then there must be a cycle.
class Solution {
  class UnionFind {
    vector<int> parents;
    vector<int> ranks;

   public:
    UnionFind(int n) : parents(n), ranks(n, 0) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    int find(int x) {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
    }

    // Return true if they are already connected
    bool unite(int x, int y) {
      x = find(x);
      y = find(y);
      if (x == y) return true;

      // Ensure rank(x) >= rank(y)
      if (ranks[x] < ranks[y]) swap(x, y);

      // Merge y into x
      if (ranks[x] == ranks[y]) ++ranks[x];
      parents[y] = x;

      return false;
    }
  };

 public:
  bool containsCycle(const vector<vector<char>>& grid) {
    const int m = grid.size(), n = grid[0].size();
    const int mn = m * n;

    // Helper
    const auto getKey = [n](int i, int j) -> int {  //
      return i * n + j;
    };

    // Loop for all edges
    auto uf = UnionFind(mn);
    for (int i = 0; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        if (grid[i][j] != grid[i][j - 1]) continue;
        if (uf.unite(getKey(i, j), getKey(i, j - 1))) return true;
      }
    }
    for (int j = 0; j < n; ++j) {
      for (int i = 1; i < m; ++i) {
        if (grid[i][j] != grid[i - 1][j]) continue;
        if (uf.unite(getKey(i, j), getKey(i - 1, j))) return true;
      }
    }

    return false;
  }
};
