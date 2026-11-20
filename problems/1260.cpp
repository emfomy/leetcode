// Source: https://leetcode.com/problems/shift-2d-grid
// Title: Shift 2D Grid
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a 2D `grid` of size `m x n`and an integer `k`. You need to shift the `grid``k` times.
//
// In one shift operation:
//
// - Element at `grid[i][j]` moves to `grid[i][j + 1]`.
// - Element at `grid[i][n - 1]` moves to `grid[i + 1][0]`.
// - Element at `grid[m- 1][n - 1]` moves to `grid[0][0]`.
//
// Return the 2D grid after applying shift operation `k` times.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2019/11/05/e1.png
//
// ```
// Input: `grid` = [[1,2,3],[4,5,6],[7,8,9]], k = 1
// Output: [[9,1,2],[3,4,5],[6,7,8]]
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2019/11/05/e2.png
//
// ```
// Input: `grid` = [[3,8,1,9],[19,7,2,5],[4,6,11,10],[12,0,21,13]], k = 4
// Output: [[12,0,21,13],[3,8,1,9],[19,7,2,5],[4,6,11,10]]
// ```
//
// **Example 3:**
//
// ```
// Input: `grid` = [[1,2,3],[4,5,6],[7,8,9]], k = 9
// Output: [[1,2,3],[4,5,6],[7,8,9]]
// ```
//
// **Constraints:**
//
// - `m ==grid.length`
// - `n ==grid[i].length`
// - `1 <= m <= 50`
// - `1 <= n <= 50`
// - `-1000 <= grid[i][j] <= 1000`
// - `0 <= k <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// Juggling Algorithm
//
// Treat the grid as an 1-D array of length mn.
// WLOG, say k < mn (otherwise, just take the modulo).
//
// All cell are shifted right k steps.
// The orbit for cell 0 is:
// 0 -> k -> 2k -> ... -> 0.
//
// Notice that, in the orbit, the smallest nonzero number is g=gcd(k, mn).
// Therefore, there are total g orbits.
class Solution {
 public:
  vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
    const int m = grid.size(), n = grid[0].size();
    const int mn = m * n;
    k %= mn;

    // Trivial
    if (k == 0) return grid;

    // Loop
    const auto cell = [n, &grid](int i) -> int& { return grid[i / n][i % n]; };
    const int g = gcd(mn, k);
    for (int d = 0; d < g; ++d) {
      int tmp;
      int i = d;
      do {
        swap(tmp, cell(i));
        i = (i + k) % mn;
      } while (i != d);
      cell(d) = tmp;
    }

    return grid;
  }
};

// The orbit size is mn/g.
class Solution2 {
 public:
  vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
    const int m = grid.size(), n = grid[0].size();
    const int mn = m * n;
    k %= mn;

    // Trivial
    if (k == 0) return grid;

    // Loop
    const auto cell = [n, &grid](int i) -> int& { return grid[i / n][i % n]; };
    const int g = gcd(mn, k);
    const int orbit = mn / g;  // orbit size
    for (int d = 0; d < g; ++d) {
      int i = d, tmp = cell(i);
      for (int j = 1; j <= orbit; ++j) {
        swap(tmp, cell(i));
        i = (i + k) % mn;
      }
    }

    return grid;
  }
};
