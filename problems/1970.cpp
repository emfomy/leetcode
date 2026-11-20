// Source: https://leetcode.com/problems/last-day-where-you-can-still-cross
// Title: Last Day Where You Can Still Cross
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a **1-based** binary matrix where `0` represents land and `1` represents water. You are given integers `row` and `col` representing the number of rows and columns in the matrix, respectively.
//
// Initially on day `0`, the **entire** matrix is **land**. However, each day a new cell becomes flooded with **water**. You are given a **1-based** 2D array `cells`, where `cells[i] = [r_i, c_i]` represents that on the `i^th` day, the cell on the `r_i^th` row and `c_i^th` column (**1-based** coordinates) will be covered with **water** (i.e., changed to `1`).
//
// You want to find the **last** day that it is possible to walk from the **top** to the **bottom** by only walking on land cells. You can start from **any** cell in the top row and end at **any** cell in the bottom row. You can only travel in the** four** cardinal directions (left, right, up, and down).
//
// Return the **last** day where it is possible to walk from the **top** to the **bottom** by only walking on land cells.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/07/27/1.png
//
// ```
// Input: row = 2, col = 2, cells = [[1,1],[2,1],[1,2],[2,2]]
// Output: 2
// Explanation: The above image depicts how the matrix changes each day starting from day 0.
// The last day where it is possible to cross from top to bottom is on day 2.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/07/27/2.png
//
// ```
// Input: row = 2, col = 2, cells = [[1,1],[1,2],[2,1],[2,2]]
// Output: 1
// Explanation: The above image depicts how the matrix changes each day starting from day 0.
// The last day where it is possible to cross from top to bottom is on day 1.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/07/27/3.png
//
// ```
// Input: row = 3, col = 3, cells = [[1,2],[2,1],[3,3],[2,2],[1,1],[1,3],[2,3],[3,2],[3,1]]
// Output: 3
// Explanation: The above image depicts how the matrix changes each day starting from day 0.
// The last day where it is possible to cross from top to bottom is on day 3.
// ```
//
// **Constraints:**
//
// - `2 <= row, col <= 2 * 10^4`
// - `4 <= row * col <= 2 * 10^4`
// - `cells.length == row * col`
// - `1 <= r_i <= row`
// - `1 <= c_i <= col`
// - All the values of `cells` are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <utility>
#include <vector>

using namespace std;

// Union-Find
//
// Loop from the last day to the first day.
// Use union-find to check if the top row is connected to the last row.
class Solution {
  struct UnionFind {
    vector<int> parents;
    vector<int> ranks;

    UnionFind(int n) : parents(n), ranks(n) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    bool connected(int x, int y) {  //
      return find(x) == find(y);
    }

    int find(int x) {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
    }

    void merge(int x, int y) {
      x = find(x);
      y = find(y);

      // Skip
      if (x == y) return;

      // Ensure rank(x) >= rank(y)
      if (ranks[x] < ranks[y]) swap(x, y);

      // Merge y into x
      if (ranks[x] == ranks[y]) ++ranks[x];
      parents[y] = x;
    }
  };

 public:
  int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
    int n = cells.size();

    auto uf = UnionFind((row + 2) * (col + 2));  // use extra padding
    auto grid = vector(row + 2, vector(col + 2, false));

    // Helper
    auto idx = [=](int r, int c) { return r * (col + 2) + c; };

    // Merge first/last row
    for (auto c = 1; c <= col; ++c) {
      grid[0][c] = true;
      grid[row + 1][c] = true;
      uf.merge(idx(0, 1), idx(0, c));
      uf.merge(idx(row + 1, 1), idx(row + 1, c));
    }

    // Loop
    for (auto t = n - 1; t >= 0; --t) {
      auto r = cells[t][0], c = cells[t][1];

      if (grid[r - 1][c]) uf.merge(idx(r, c), idx(r - 1, c));
      if (grid[r + 1][c]) uf.merge(idx(r, c), idx(r + 1, c));
      if (grid[r][c - 1]) uf.merge(idx(r, c), idx(r, c - 1));
      if (grid[r][c + 1]) uf.merge(idx(r, c), idx(r, c + 1));

      grid[r][c] = true;

      if (uf.connected(idx(0, 1), idx(row + 1, 1))) return t;
    }

    return -1;  // won't reach
  }
};
