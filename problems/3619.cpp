// Source: https://leetcode.com/problems/count-islands-with-total-value-divisible-by-k
// Title: Count Islands With Total Value Divisible by K
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` matrix `grid` and a positive integer `k`. An **island** is a group of **positive** integers (representing land) that are **4-directionally** connected (horizontally or vertically).
//
// The **total value** of an island is the sum of the values of all cells in the island.
//
// Return the number of islands with a total value **divisible by** `k`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2025/03/06/example1griddrawio-1.png
//
// ```
// Input: grid = [[0,2,1,0,0],[0,5,0,0,5],[0,0,1,0,0],[0,1,4,7,0],[0,2,0,0,8]], k = 5
// Output: 2
// Explanation:
// The grid contains four islands. The islands highlighted in blue have a total value that is divisible by 5, while the islands highlighted in red do not.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2025/03/06/example2griddrawio.png
//
// ```
// Input: grid = [[3,0,3,0], [0,3,0,3], [3,0,3,0]], k = 3
// Output: 6
// Explanation:
// The grid contains six islands, each with a total value that is divisible by 3.
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 1000`
// - `1 <= m * n <= 10^5`
// - `0 <= grid[i][j] <= 10^6`
// - `1 <= k <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// Union-Find
class Solution {
  struct UnionFind {
    vector<int> parents;
    vector<int> ranks;
    vector<long long> scores;  // use long long to avoid overflow

    UnionFind(int n) : parents(n), ranks(n, 0), scores(n, 0) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    int find(int x) {
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
      scores[x] += scores[y];
    }
  };

 public:
  int countIslands(const vector<vector<int>>& grid, int k) {
    const int m = grid.size(), n = grid[0].size();

    // Helper
    const auto idx = [m, n](int i, int j) { return i * n + j; };

    // Init scores
    auto uf = UnionFind(m * n);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        uf.scores[idx(i, j)] = grid[i][j];
      }
    }

    // Loop
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        // Skip zero
        if (grid[i][j] == 0) continue;

        // Union
        if (i + 1 < m && grid[i + 1][j] > 0) {
          uf.unite(idx(i, j), idx(i + 1, j));
        }
        if (j + 1 < n && grid[i][j + 1] > 0) {
          uf.unite(idx(i, j), idx(i, j + 1));
        }
      }
    }

    // Count
    int ans = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        // Skip zero
        if (grid[i][j] == 0) continue;

        // Skip non-root
        const int x = idx(i, j);
        if (uf.parents[x] != x) continue;

        // Check division
        if (uf.scores[x] % k == 0) ++ans;
      }
    }

    return ans;
  }
};
