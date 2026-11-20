// Source: https://leetcode.com/problems/special-positions-in-a-binary-matrix
// Title: Special Positions in a Binary Matrix
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an `m x n` binary matrix `mat`, return the number of special positions in `mat`.
//
// A position `(i, j)` is called **special** if `mat[i][j] == 1` and all other elements in row `i` and column `j` are `0` (rows and columns are **0-indexed**).
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/12/23/special1.jpg
//
// ```
// Input: mat = [[1,0,0],[0,0,1],[1,0,0]]
// Output: 1
// Explanation: (1, 2) is a special position because mat[1][2] == 1 and all other elements in row 1 and column 2 are 0.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/12/24/special-grid.jpg
//
// ```
// Input: mat = [[1,0,0],[0,1,0],[0,0,1]]
// Output: 3
// Explanation: (0, 0), (1, 1) and (2, 2) are special positions.
// ```
//
// **Constraints:**
//
// - `m == mat.length`
// - `n == mat[i].length`
// - `1 <= m, n <= 100`
// - `mat[i][j]` is either `0` or `1`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Count
//
// We first count the number of 1 in each row / column.
// A position is special if that row and column only has a single 1.
class Solution {
 public:
  int numSpecial(const vector<vector<int>>& mat) {
    const int m = mat.size(), n = mat[0].size();

    // Count ones
    auto rowCounts = vector<int>(m);
    auto colCounts = vector<int>(n);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        rowCounts[i] += mat[i][j];
        colCounts[j] += mat[i][j];
      }
    }

    // Count specials
    int ans = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        ans += (mat[i][j] == 1 && rowCounts[i] == 1 && colCounts[j] == 1);
      }
    }

    return ans;
  }
};
