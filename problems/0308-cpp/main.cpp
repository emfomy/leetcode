// Source: https://leetcode.com/problems/range-sum-query-2d-mutable
// Title: Range Sum Query 2D - Mutable
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a 2D matrix `matrix`, handle multiple queries of the following types:
//
// - **Update** the value of a cell in `matrix`.
// - Calculate the **sum** of the elements of `matrix` inside the rectangle defined by its **upper left corner** `(row1, col1)` and **lower right corner** `(row2, col2)`.
//
// Implement the NumMatrix class:
//
// - `NumMatrix(int[][] matrix)` Initializes the object with the integer matrix `matrix`.
// - `void update(int row, int col, int val)` **Updates** the value of `matrix[row][col]` to be `val`.
// - `int sumRegion(int row1, int col1, int row2, int col2)` Returns the **sum** of the elements of `matrix` inside the rectangle defined by its **upper left corner** `(row1, col1)` and **lower right corner** `(row2, col2)`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/03/14/summut-grid.jpg
//
// ```
// Input:
// ["NumMatrix", "sumRegion", "update", "sumRegion"]
// [[[[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]], [2, 1, 4, 3], [3, 2, 2], [2, 1, 4, 3]]
//
// Output:
// [null, 8, null, 10]
//
// Explanation:
// NumMatrix numMatrix = new NumMatrix([[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]);
// numMatrix.sumRegion(2, 1, 4, 3); // return 8 (i.e. sum of the left red rectangle)
// numMatrix.update(3, 2, 2);       // matrix changes from left image to right image
// numMatrix.sumRegion(2, 1, 4, 3); // return 10 (i.e. sum of the right red rectangle)
// ```
//
// **Constraints:**
//
// - `m == matrix.length`
// - `n == matrix[i].length`
// - `1 <= m, n <= 200`
// - `-1000 <= matrix[i][j] <= 1000`
// - `0 <= row < m`
// - `0 <= col < n`
// - `-1000 <= val <= 1000`
// - `0 <= row1 <= row2 < m`
// - `0 <= col1 <= col2 < n`
// - At most `5000` calls will be made to `sumRegion` and `update`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// 2D Fenwick Tree
class NumMatrix {
  int m, n;
  vector<vector<int>> matrix;
  vector<vector<int>> tree;  // tree[i][j] = sum of [i-lowbit(i), i) x [j-lowbit(j), j)

 public:
  NumMatrix(vector<vector<int>>& matrix) : matrix(matrix) {
    m = matrix.size(), n = matrix[0].size();
    tree.assign(m + 1, vector<int>(n + 1, 0));

    // Build: O(MN)
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        tree[i + 1][j + 1] = matrix[i][j];
      }
    }

    // Update row-wise parent
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        int p = j + (j & -j);
        if (p <= n) tree[i][p] += tree[i][j];
      }
    }

    // Update column-wise parent
    for (int j = 1; j <= n; ++j) {
      for (int i = 1; i <= m; ++i) {
        int p = i + (i & -i);
        if (p <= m) tree[p][j] += tree[i][j];
      }
    }
  }

  // Update: O(logM logN); matrix[row][col] = val
  void update(int row, int col, int val) {
    const int delta = val - matrix[row][col];
    matrix[row][col] = val;

    for (int i = row + 1; i <= m; i += (i & -i)) {
      for (int j = col + 1; j <= n; j += (j & -j)) {
        tree[i][j] += delta;
      }
    }
  }

  // Query: O(logM logN); sum of [0, row) x [0, col)
  int query(int row, int col) {
    int sum = 0;
    for (int i = row; i >= 1; i -= (i & -i)) {
      for (int j = col; j >= 1; j -= (j & -j)) {
        sum += tree[i][j];
      }
    }
    return sum;
  }

  // Query: O(logM logN); sum of [row1, row2] x [col1, col2]
  int sumRegion(int row1, int col1, int row2, int col2) {
    ++row2, ++col2;  // convert to close-open range
    return query(row2, col2) + query(row1, col1) - query(row2, col1) - query(row1, col2);
  }
};

// 2D Segment Tree
class NumMatrix2 {
  int m, n;
  vector<vector<int>> tree;

 public:
  NumMatrix2(const vector<vector<int>>& matrix) {
    m = matrix.size(), n = matrix[0].size();
    tree.assign(2 * m, vector<int>(2 * n, 0));

    // Build: O(MN)

    // Set leaves; [m, 2m) x [n, 2n)
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        tree[i + m][j + n] = matrix[i][j];
      }
    }

    // Update row-wise; [m, 2m) x [1, n)
    for (int i = m; i < 2 * m; ++i) {
      for (int j = n - 1; j >= 1; --j) {
        tree[i][j] = tree[i][2 * j] + tree[i][2 * j + 1];
      }
    }

    // Update column-wise; [1, m) x [1, 2n)
    for (int i = m - 1; i >= 1; --i) {
      for (int j = 1; j < 2 * n; ++j) {
        tree[i][j] = tree[2 * i][j] + tree[2 * i + 1][j];
      }
    }
  }

  // Update: O(logM logN); matrix[r][c] = val
  void update(int r, int c, int val) {
    // Update leaf; [r][c] in [m, 2m) x [n, 2n)
    r += m, c += n;
    tree[r][c] = val;

    // Update row-wise; [r][j] in [m, 2m) x [1, n)
    for (int j = c / 2; j >= 1; j /= 2) {
      tree[r][j] = tree[r][2 * j] + tree[r][2 * j + 1];
    }

    // Update column-wise; [i][j] in [1, m) x [1, 2n)
    for (int i = r / 2; i >= 1; i /= 2) {
      for (int j = c; j >= 1; j /= 2) {
        tree[i][j] = tree[2 * i][j] + tree[2 * i + 1][j];
      }
    }
  }

  // Query Row: O(logN); sum of [r) x [c0, c1)
  int queryRow(int r, int c0, int c1) const {
    int sum = 0;
    for (c0 += n, c1 += n; c0 < c1; c0 /= 2, c1 /= 2) {
      if (c0 & 1) sum += tree[r][c0++];
      if (c1 & 1) sum += tree[r][--c1];
    }
    return sum;
  }

  // Query: O(logM logN); sum of [0, row) x [0, col)
  int query(int r0, int c0, int r1, int c1) const {
    int sum = 0;
    for (r0 += m, r1 += m; r0 < r1; r0 /= 2, r1 /= 2) {
      if (r0 & 1) sum += queryRow(r0++, c0, c1);
      if (r1 & 1) sum += queryRow(--r1, c0, c1);
    }
    return sum;
  }

  // Query: O(logM logN); sum of [row1, row2] x [col1, col2]
  int sumRegion(int row1, int col1, int row2, int col2) const {  //
    return query(row1, col1, row2 + 1, col2 + 1);
  }
};
