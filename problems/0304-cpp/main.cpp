// Source: https://leetcode.com/problems/range-sum-query-2d-immutable
// Title: Range Sum Query 2D - Immutable
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a 2D matrix `matrix`, handle multiple queries of the following type:
//
// - Calculate the **sum** of the elements of `matrix` inside the rectangle defined by its **upper left corner** `(row1, col1)` and **lower right corner** `(row2, col2)`.
//
// Implement the `NumMatrix` class:
//
// - `NumMatrix(int[][] matrix)` Initializes the object with the integer matrix `matrix`.
// - `int sumRegion(int row1, int col1, int row2, int col2)` Returns the **sum** of the elements of `matrix` inside the rectangle defined by its **upper left corner** `(row1, col1)` and **lower right corner** `(row2, col2)`.
//
// You must design an algorithm where `sumRegion` works on `O(1)` time complexity.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/03/14/sum-grid.jpg
//
// ```
// Input:
// ["NumMatrix", "sumRegion", "sumRegion", "sumRegion"]
// [[[[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]], [2, 1, 4, 3], [1, 1, 2, 2], [1, 2, 2, 4]]
//
// Output:
// [null, 8, 11, 12]
//
// Explanation:
// NumMatrix numMatrix = new NumMatrix([[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]);
// numMatrix.sumRegion(2, 1, 4, 3); // return 8 (i.e sum of the red rectangle)
// numMatrix.sumRegion(1, 1, 2, 2); // return 11 (i.e sum of the green rectangle)
// numMatrix.sumRegion(1, 2, 2, 4); // return 12 (i.e sum of the blue rectangle)
// ```
//
// **Constraints:**
//
// - `m == matrix.length`
// - `n == matrix[i].length`
// - `1 <= m, n <= 200`
// - `-10^4 <= matrix[i][j] <= 10^4`
// - `0 <= row1 <= row2 < m`
// - `0 <= col1 <= col2 < n`
// - At most `10^4` calls will be made to `sumRegion`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Prefix Sum
class NumMatrix {
  vector<vector<int>> data;  // data[i][j] = sum of [0, i) x [0, j)

 public:
  NumMatrix(const vector<vector<int>>& matrix) {
    const int m = matrix.size(), n = matrix[0].size();
    data.assign(m + 1, vector<int>(n + 1, 0));

    // Build: O(MN)
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        data[i + 1][j + 1] = matrix[i][j] + data[i][j + 1] + data[i + 1][j] - data[i][j];
      }
    }
  }

  // Query O(1); sum of [row1, row2] x [col1 x col2]
  int sumRegion(int row1, int col1, int row2, int col2) const {
    ++row2, ++col2;  // convert to closed-open range
    return data[row2][col2] + data[row1][col1] - data[row2][col1] - data[row1][col2];
  }
};
