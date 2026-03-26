// Source: https://leetcode.com/problems/count-submatrices-with-top-left-element-and-sum-less-than-k
// Title: Count Submatrices with Top-Left Element and Sum Less Than k
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** integer matrix `grid` and an integer `k`.
//
// Return the **number** of <button>submatrices</button> that contain the top-left element of the `grid`, and have a sum less than or equal to `k`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2024/01/01/example1.png
//
// ```
// Input: grid = [[7,6,3],[6,6,1]], k = 18
// Output: 4
// Explanation: There are only 4 submatrices, shown in the image above, that contain the top-left element of grid, and have a sum less than or equal to 18.```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2024/01/01/example21.png
//
// ```
// Input: grid = [[7,2,9],[1,5,0],[2,6,6]], k = 20
// Output: 6
// Explanation: There are only 6 submatrices, shown in the image above, that contain the top-left element of grid, and have a sum less than or equal to 20.
// ```
//
// **Constraints:**
//
// - `m == grid.length `
// - `n == grid[i].length`
// - `1 <= n, m <= 1000 `
// - `0 <= grid[i][j] <= 1000`
// - `1 <= k <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Prefix Sum
class Solution {
 public:
  int countSubmatrices(const vector<vector<int>>& grid, const int k) {
    const int m = grid.size(), n = grid[0].size();

    // Prefix sum
    auto sums = vector<vector<int>>(m + 1, vector<int>(n + 1));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        sums[i + 1][j + 1] = grid[i][j] + sums[i][j + 1] + sums[i + 1][j] - sums[i][j];
      }
    }

    // Count
    int count = 0;
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        count += sums[i][j] <= k;
      }
    }

    return count;
  }
};

// Prefix Sum
//
// Use 1D array
class Solution2 {
 public:
  int countSubmatrices(const vector<vector<int>>& grid, const int k) {
    const int m = grid.size(), n = grid[0].size();

    // Loop
    int count = 0;
    auto prev = vector<int>(n + 1);
    auto curr = vector<int>(n + 1);
    for (int i = 0; i < m; ++i) {
      swap(curr, prev);
      for (int j = 0; j < n; ++j) {
        curr[j + 1] = grid[i][j] + prev[j + 1] + curr[j] - prev[j];
        count += (curr[j + 1] <= k);
      }
    }

    return count;
  }
};

// Prefix Sum
//
// Use 1D array. Do early stop.
class Solution3 {
 public:
  int countSubmatrices(const vector<vector<int>>& grid, const int k) {
    const int m = grid.size(), n = grid[0].size();

    // Loop
    int count = 0;
    auto prev = vector<int>(n + 1);
    auto curr = vector<int>(n + 1);
    int maxJ = n;
    for (int i = 0; i < m; ++i) {
      swap(curr, prev);
      for (int j = 0; j < maxJ; ++j) {
        curr[j + 1] = grid[i][j] + prev[j + 1] + curr[j] - prev[j];
        if (curr[j + 1] > k) {
          maxJ = j;
          break;
        }
        ++count;
      }
      if (maxJ == 0) break;
    }

    return count;
  }
};

// Prefix Sum
//
// Use prefix sum for each column.
class Solution4 {
 public:
  int countSubmatrices(const vector<vector<int>>& grid, const int k) {
    const int m = grid.size(), n = grid[0].size();

    // Loop
    int count = 0;
    auto colSums = vector<int>(n);
    int maxJ = n;
    for (int i = 0; i < m; ++i) {
      int rowSum = 0;
      for (int j = 0; j < maxJ; ++j) {
        colSums[j] += grid[i][j];
        rowSum += colSums[j];
        if (rowSum > k) {
          maxJ = j;
          break;
        }
        ++count;
      }
      if (maxJ == 0) break;
    }

    return count;
  }
};
