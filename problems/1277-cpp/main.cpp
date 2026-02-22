// Source: https://leetcode.com/problems/count-square-submatrices-with-all-ones
// Title: Count Square Submatrices with All Ones
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a `m * n` matrix of ones and zeros, return how many **square** submatrices have all ones.
//
// **Example 1:**
//
// ```
// Input: matrix =
// [
//  [0,1,1,1],
//  [1,1,1,1],
//  [0,1,1,1]
// ]
// Output: 15
// Explanation:
// There are **10** squares of side 1.
// There are **4** squares of side 2.
// There is  **1** square of side 3.
// Total number of squares = 10 + 4 + 1 = **15**.
// ```
//
// **Example 2:**
//
// ```
// Input: matrix =
// [
//   [1,0,1],
//   [1,1,0],
//   [1,1,0]
// ]
// Output: 7
// Explanation:
// There are **6** squares of side 1.
// There is **1** square of side 2.
// Total number of squares = 6 + 1 = **7**.
// ```
//
// **Constraints:**
//
// - `1 <= arr.length<= 300`
// - `1 <= arr[0].length<= 300`
// - `0 <= arr[i][j] <= 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// 2D-DP
//
// DP[k, i, j] denotes if there is a square of size k at (i, j) as top left corner.
//
// DP[1, i, j] = matrix[i, j]
// DP[k, i, j] = 1 if DP[k-1] = 1 for (i, j), (i, j+1), (i+1, j), (i+1, j+1)
//
// We reuse the input matrix for DP.
class Solution {
 public:
  int countSquares(vector<vector<int>>& matrix) {
    const int m = matrix.size(), n = matrix[0].size();
    const int minMN = min(m, n);

    // Count for k=1
    int count = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        count += matrix[i][j];
      }
    }

    // Count for k >= 2
    for (int k = 2; k <= minMN; ++k) {
      for (int i = 0; i <= m - k; ++i) {
        for (int j = 0; j <= n - k; ++j) {
          matrix[i][j] = matrix[i][j] && matrix[i][j + 1] && matrix[i + 1][j] && matrix[i + 1][j + 1];
          count += matrix[i][j];
        }
      }
    }

    return count;
  }
};

// 2D-DP
//
// DP[i, j] means the maximum square with (i, j) as top left corner.
//
// DP[i, j] = 0 if matrix[i, j] = 0
// DP[i, j] = max(DP[i, j+1], DP[i+1, j], DP[i+1, j+1]) + 1
//
// Loop from bottom right corner to top left.
class Solution2 {
 public:
  int countSquares(const vector<vector<int>>& matrix) {
    const int m = matrix.size(), n = matrix[0].size();

    auto dp = vector(m + 1, vector<int>(n + 1));

    int ans = 0;
    for (auto i = m - 1; i >= 0; i--) {
      for (auto j = n - 1; j >= 0; j--) {
        if (matrix[i][j]) {
          dp[i][j] = min({dp[i][j + 1], dp[i + 1][j], dp[i + 1][j + 1]}) + 1;
          ans += dp[i][j];
        }
      }
    }

    return ans;
  }
};

// 1D-DP
//
// DP[i, j] means the maximum square with (i, j) as top left corner.
//
// DP[i, j] = 0 if matrix[i, j] = 0
// DP[i, j] = max(DP[i, j+1], DP[i+1, j], DP[i+1, j+1]) + 1
//
// Loop from bottom right corner to top left.
class Solution3 {
 public:
  int countSquares(const vector<vector<int>>& matrix) {
    const int m = matrix.size(), n = matrix[0].size();

    auto prev = vector<int>(n + 1);
    auto curr = vector<int>(n + 1);

    int ans = 0;
    for (auto i = m - 1; i >= 0; i--) {
      swap(curr, prev);
      for (auto j = n - 1; j >= 0; j--) {
        if (matrix[i][j]) {
          curr[j] = min({curr[j + 1], prev[j], prev[j + 1]}) + 1;
          ans += curr[j];
        } else {
          curr[j] = 0;
        }
      }
    }

    return ans;
  }
};
