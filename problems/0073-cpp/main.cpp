// Source: https://leetcode.com/problems/set-matrix-zeroes
// Title: Set Matrix Zeroes
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an `m x n` `matrix`, return all elements of the `matrix` in spiral order.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/11/13/spiral1.jpg
//
// ```
// Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [1,2,3,6,9,8,7,4,5]
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/11/13/spiral.jpg
//
// ```
// Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
// Output: [1,2,3,4,8,12,11,10,9,5,6,7]
// ```
//
// **Constraints:**
//
// - `m == matrix.length`
// - `n == matrix[i].length`
// - `1 <= m, n <= 10`
// - `-100 <= matrix[i][j] <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// O(n) space
class Solution {
 public:
  void setZeroes(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    vector<bool> rows(m);
    vector<bool> cols(n);

    // Check zeros
    for (auto i = 0; i < m; i++) {
      for (auto j = 0; j < n; j++) {
        if (matrix[i][j] == 0) {
          rows[i] = true;
          cols[j] = true;
        }
      }
    }

    // Update rows
    for (auto i = 0; i < m; i++) {
      if (rows[i]) {
        for (auto j = 0; j < n; j++) {
          matrix[i][j] = 0;
        }
      }
    }

    // Update columns
    for (auto j = 0; j < n; j++) {
      if (cols[j]) {
        for (auto i = 0; i < m; i++) {
          matrix[i][j] = 0;
        }
      }
    }
  }
};

// O(1) space
//
// We first check the first row and column.
// Then use the first row & column to store the zeros for other rows/columns.
class Solution2 {
 public:
  void setZeroes(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    // Row 0
    bool row0 = 1;
    for (auto j = 0; j < n; j++) {
      if (matrix[0][j] == 0) {
        row0 = 0;
        break;
      }
    }

    // Column 0
    bool col0 = 1;
    for (auto i = 0; i < m; i++) {
      if (matrix[i][0] == 0) {
        col0 = 0;
        break;
      }
    }

    // Check zeros
    for (auto i = 1; i < m; i++) {
      for (auto j = 1; j < n; j++) {
        if (matrix[i][j] == 0) {
          matrix[i][0] = 0;
          matrix[0][j] = 0;
        }
      }
    }

    // Update rows
    for (auto i = 1; i < m; i++) {
      if (matrix[i][0] == 0) {
        for (auto j = 1; j < n; j++) {
          matrix[i][j] = 0;
        }
      }
    }

    // Update columns
    for (auto j = 1; j < n; j++) {
      if (matrix[0][j] == 0) {
        for (auto i = 1; i < m; i++) {
          matrix[i][j] = 0;
        }
      }
    }

    // Update row 0
    if (row0 == 0) {
      for (auto j = 0; j < n; j++) {
        matrix[0][j] = 0;
      }
    }

    // Update column 0
    if (col0 == 0) {
      for (auto i = 0; i < m; i++) {
        matrix[i][0] = 0;
      }
    }
  }
};
