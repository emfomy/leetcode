// Source: https://leetcode.com/problems/matrix-block-sum
// Title: Matrix Block Sum
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a `m x n` matrix `mat` and an integer `k`, return a matrix `answer` where each `answer[i][j]` is the sum of all elements `mat[r][c]` for:
//
// - `i - k <= r <= i + k,`
// - `j - k <= c <= j + k`, and
// - `(r, c)` is a valid position in the matrix.
//
// **Example 1:**
//
// ```
// Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 1
// Output: [[12,21,16],[27,45,33],[24,39,28]]
// ```
//
// **Example 2:**
//
// ```
// Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 2
// Output: [[45,45,45],[45,45,45],[45,45,45]]
// ```
//
// **Constraints:**
//
// - `m ==mat.length`
// - `n ==mat[i].length`
// - `1 <= m, n, k <= 100`
// - `1 <= mat[i][j] <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Prefix Sum
//
// Define Pre[i, j] = Sum Mat in [0, i) x [0, j)
//
// Mat[i, j] = Pre[i+1, j+1] + Pre[i, j] - Pre[i, j+1] - Pre[i+1, j]
// Pre[i+1, j+1] = Mat[i, j] + Pre[i, j+1] + Pre[i+1, j] - Pre[i, j]
//
// Ans[i, j] = Sum Mat in [i-k, i+k+1) x [j-k, j+k+1)
//           = Pre[i+k+1, j+k+1] + Pre[i-k, j-k] - Pre[i+k+1, j-k] - Pre[i-k, j+k+1]
class Solution {
 public:
  vector<vector<int>> matrixBlockSum(const vector<vector<int>>& mat, int k) {
    const int m = mat.size(), n = mat[0].size();

    // Prefix Sum
    auto pre = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        pre[i + 1][j + 1] = mat[i][j] + pre[i][j + 1] + pre[i + 1][j] - pre[i][j];
      }
    }

    // Answer
    auto ans = vector<vector<int>>(m, vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        int i0 = max(i - k, 0);
        int j0 = max(j - k, 0);
        int i1 = min(i + k + 1, m);
        int j1 = min(j + k + 1, n);
        ans[i][j] = pre[i1][j1] + pre[i0][j0] - pre[i1][j0] - pre[i0][j1];
      }
    }

    return ans;
  }
};
