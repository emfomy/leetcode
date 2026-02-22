// Source: https://leetcode.com/problems/map-of-highest-peak
// Title: Map of Highest Peak
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer matrix `isWater` of size `m x n` that represents a map of **land** and **water** cells.
//
// - If `isWater[i][j] == 0`, cell `(i, j)` is a **land** cell.
// - If `isWater[i][j] == 1`, cell `(i, j)` is a **water** cell.
//
// You must assign each cell a height in a way that follows these rules:
//
// - The height of each cell must be non-negative.
// - If the cell is a **water** cell, its height must be `0`.
// - Any two adjacent cells must have an absolute height difference of **at most** `1`. A cell is adjacent to another cell if the former is directly north, east, south, or west of the latter (i.e., their sides are touching).
//
// Find an assignment of heights such that the maximum height in the matrix is **maximized**.
//
// Return an integer matrix `height` of size `m x n` where `height[i][j]` is cell `(i, j)`'s height. If there are multiple solutions, return **any** of them.
//
// **Example 1:**
//
// **https://assets.leetcode.com/uploads/2021/01/10/screenshot-2021-01-11-at-82045-am.png**
//
// ```
// Input: isWater = [[0,1],[0,0]]
// Output: [[1,0],[2,1]]
// Explanation: The image shows the assigned heights of each cell.
// The blue cell is the water cell, and the green cells are the land cells.
// ```
//
// **Example 2:**
//
// **https://assets.leetcode.com/uploads/2021/01/10/screenshot-2021-01-11-at-82050-am.png**
//
// ```
// Input: isWater = [[0,0,1],[1,0,0],[0,0,0]]
// Output: [[1,1,0],[0,1,1],[1,2,2]]
// Explanation: A height of 2 is the maximum possible height of any assignment.
// Any height assignment that has a maximum height of 2 while still meeting the rules will also be accepted.
// ```
//
// **Constraints:**
//
// - `m == isWater.length`
// - `n == isWater[i].length`
// - `1 <= m, n <= 1000`
// - `isWater[i][j]` is `0` or `1`.
// - There is at least **one** water cell.
//
// **Note:** This question is the same as 542: https://leetcode.com/problems/01-matrix
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <vector>

using namespace std;

// BFS
//
// Set the value of each cell as the distance to the nearest water.
// Note that we don't need priority queue here.
//
// Now we prove that this is the maximum solution.
// Let `c` be a cell in the matrix.
// Define H(c) be the best solution, and D(c) be the minimal distance to the nearest water.
// We have 1. H(water) = 0 and 2. |H(a) - H(b)| <= 1 for any neighbor `a` and `b`.
//
// Say the nearest water of cell `c` is water `w`. then |H(c) - H(w)| <= D(c) (by condition 2).
// Since H(w) = 0 (condition 1), then H(c) <= D(c).
//
// It is clear that D satisfies condition 1.
// For any cell `a` and any of its neighbor `b`,
// we have D(b) >= D(a) + 1 (a path from b to the nearest water passing `a`).
// Similarly, D(a) >= D(b) + 1; that is |D(a) - D(b)| <= 1.
// Therfore, D() is a valid solution.
//
// Hence, D() is the best solution.
class Solution {
  constexpr static int DIRS[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

 public:
  vector<vector<int>> highestPeak(const vector<vector<int>>& isWater) {
    const int m = isWater.size(), n = isWater[0].size();

    // Init the queue with water cells
    auto que = queue<pair<int, int>>();          // row, col
    auto dists = vector(m, vector<int>(n, -1));  // -1 means not visited
    for (int row = 0; row < m; ++row) {
      for (int col = 0; col < n; ++col) {
        if (isWater[row][col]) {
          que.emplace(row, col);
          dists[row][col] = 0;
        }
      }
    }

    // BFS
    while (!que.empty()) {
      const auto [row, col] = que.front();
      que.pop();

      const int dist2 = dists[row][col] + 1;
      for (auto [dRow, dCol] : DIRS) {
        auto row2 = row + dRow, col2 = col + dCol;
        if (0 <= row2 && row2 < m && 0 <= col2 && col2 < n && dists[row2][col2] == -1) {
          que.emplace(row2, col2);
          dists[row2][col2] = dist2;
        }
      }
    }

    return dists;
  }
};
