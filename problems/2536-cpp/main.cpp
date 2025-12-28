// Source: https://leetcode.com/problems/increment-submatrices-by-one
// Title: Increment Submatrices by One
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a positive integer `n`, indicating that we initially have an `n x n`**0-indexed** integer matrix `mat` filled with zeroes.
//
// You are also given a 2D integer array `query`. For each `query[i] = [row1_i, col1_i, row2_i, col2_i]`, you should do the following operation:
//
// - Add `1` to **every element** in the submatrix with the **top left** corner `(row1_i, col1_i)` and the **bottom right** corner `(row2_i, col2_i)`. That is, add `1` to `mat[x][y]` for all `row1_i <= x <= row2_i` and `col1_i <= y <= col2_i`.
//
// Return the matrix `mat` after performing every query.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2022/11/24/p2example11.png
//
// ```
// Input: n = 3, queries = [[1,1,2,2],[0,0,1,1]]
// Output: [[1,1,0],[1,2,1],[0,1,1]]
// Explanation: The diagram above shows the initial matrix, the matrix after the first query, and the matrix after the second query.
// - In the first query, we add 1 to every element in the submatrix with the top left corner (1, 1) and bottom right corner (2, 2).
// - In the second query, we add 1 to every element in the submatrix with the top left corner (0, 0) and bottom right corner (1, 1).
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2022/11/24/p2example22.png
//
// ```
// Input: n = 2, queries = [[0,0,1,1]]
// Output: [[1,1],[1,1]]
// Explanation: The diagram above shows the initial matrix and the matrix after the first query.
// - In the first query we add 1 to every element in the matrix.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 500`
// - `1 <= queries.length <= 10^4`
// - `0 <= row1_i <= row2_i < n`
// - `0 <= col1_i <= col2_i < n`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Use diff array
//
// Use the discrete partial differential d^2f/dxdy.
//
// Define Diff[i][j] = Mat[i][j] - Mat[i-1][j] - Mat[i-1][j] + Mat[i-1][j-1]
// Therefore Mat[i][j] = Diff[i][j] + Mat[i-1][j] + Mat[i-1][j] - Mat[i-1][j-1]
class Solution {
 public:
  vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
    auto diff = vector(n + 1, vector(n + 1, 0));

    // Loop from query
    for (auto& query : queries) {
      auto r1 = query[0], c1 = query[1], r2 = query[2] + 1, c2 = query[3] + 1;
      ++diff[r1][c1];
      --diff[r1][c2];
      --diff[r2][c1];
      ++diff[r2][c2];
    }

    // Answer
    auto ans = vector(n, vector(n, 0));
    for (auto i = 0; i < n; ++i) {
      for (auto j = 0; j < n; ++j) {
        auto top = (i == 0) ? 0 : ans[i - 1][j];
        auto left = (j == 0) ? 0 : ans[i][j - 1];
        auto diag = (i == 0 || j == 0) ? 0 : ans[i - 1][j - 1];
        ans[i][j] = diff[i][j] + top + left - diag;
      }
    }

    return ans;
  }
};
