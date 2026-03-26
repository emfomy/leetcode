// Source: https://leetcode.com/problems/number-of-islands
// Title: Number of Islands
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an `m x n` 2D binary grid `grid` which represents a map of `'1'`s (land) and `'0'`s (water), return the number of islands.
//
// An **island** is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
//
// **Example 1:**
//
// ```
// Input: grid = [
//   ["1","1","1","1","0"],
//   ["1","1","0","1","0"],
//   ["1","1","0","0","0"],
//   ["0","0","0","0","0"]
// ]
// Output: 1
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [
//   ["1","1","0","0","0"],
//   ["1","1","0","0","0"],
//   ["0","0","1","0","0"],
//   ["0","0","0","1","1"]
// ]
// Output: 3
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 300`
// - `grid[i][j]` is `'0'` or `'1'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// Union-Find
//
// Loop for each cell, and compare the connectivity.
//
// Note that we treat all zeros as 1x1 islands in union find.
class Solution {
  struct UnionFind {
    mutable vector<int> parents;
    mutable vector<int> ranks;
    int count;  // connected components

    UnionFind(int n) : parents(n), ranks(n), count(n) {
      iota(parents.begin(), parents.end(), 0);  //
    }

    int find(int x) const {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
    }

    void unite(int x, int y) {
      x = find(x);
      y = find(y);
      if (x == y) return;

      // Ensure rank(x) >= rank(y)
      if (ranks[x] < ranks[y]) swap(x, y);

      // Merge y into x
      if (ranks[x] == ranks[y]) ++ranks[x];
      parents[y] = x;
      --count;
    }
  };

 public:
  int numIslands(const vector<vector<char>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    auto uf = UnionFind(m * n);
    const auto key = [n](int i, int j) -> int { return i * n + j; };

    // Merge islands
    int zeros = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == '0') {
          ++zeros;
          continue;
        }
        if (i > 0 && grid[i - 1][j] == '1') uf.unite(key(i, j), key(i - 1, j));
        if (j > 0 && grid[i][j - 1] == '1') uf.unite(key(i, j), key(i, j - 1));
      }
    }

    return uf.count - zeros;
  }
};
