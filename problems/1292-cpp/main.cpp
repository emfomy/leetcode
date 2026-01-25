// Source: https://leetcode.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold
// Title: Maximum Side Length of a Square with Sum Less than or Equal to Threshold
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a `m x n` matrix `mat` and an integer `threshold`, return the maximum side-length of a square with a sum less than or equal to `threshold` or return `0` if there is no such square.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2019/12/05/e1.png
//
// ```
// Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
// Output: 2
// Explanation: The maximum side length of square with sum less than 4 is 2 as shown.
// ```
//
// **Example 2:**
//
// ```
// Input: mat = [[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2]], threshold = 1
// Output: 0
// ```
//
// **Constraints:**
//
// - `m == mat.length`
// - `n == mat[i].length`
// - `1 <= m, n <= 300`
// - `0 <= mat[i][j] <= 10^4`
// - `0 <= threshold <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// 2D Prefix Sum
class Solution {
 public:
  int maxSideLength(vector<vector<int>>& mat, int threshold) {
    int m = mat.size(), n = mat[0].size();
    auto mn = min(m, n);
    auto prefix = vector(m + 1, vector(n + 1, 0));

    // Prefix sum
    for (auto i = 0; i < m; ++i) {
      for (auto j = 0; j < n; ++j) {
        prefix[i + 1][j + 1] = mat[i][j] + prefix[i + 1][j] + prefix[i][j + 1] - prefix[i][j];
      }
    }

    // Loop for squares start at i, j with size l
    for (auto l = mn; l >= 1; --l) {
      for (auto i = 0; i <= m - l; ++i) {
        for (auto j = 0; j <= n - l; ++j) {
          if (prefix[i + l][j + l] - prefix[i + l][j] - prefix[i][j + l] + prefix[i][j] <= threshold) return l;
        }
      }
    }

    return 0;
  }
};

// 2D Prefix Sum + Binary Search
class Solution2 {
 public:
  int maxSideLength(vector<vector<int>>& mat, int threshold) {
    int m = mat.size(), n = mat[0].size();
    auto mn = min(m, n);
    auto prefix = vector(m + 1, vector(n + 1, 0));

    // Prefix sum
    for (auto i = 0; i < m; ++i) {
      for (auto j = 0; j < n; ++j) {
        prefix[i + 1][j + 1] = mat[i][j] + prefix[i + 1][j] + prefix[i][j + 1] - prefix[i][j];
      }
    }

    // Helper
    auto check = [&](int l) -> bool {
      for (auto i = 0; i <= m - l; ++i) {
        for (auto j = 0; j <= n - l; ++j) {
          if (prefix[i + l][j + l] - prefix[i + l][j] - prefix[i][j + l] + prefix[i][j] <= threshold) return true;
        }
      }
      return false;
    };

    // Binary Search
    // check(lo-1)=true, check(hi)=false
    auto lo = 1, hi = mn + 1;
    while (lo < hi) {
      auto mid = lo + (hi - lo) / 2;
      if (check(mid)) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    return lo - 1;
  }
};
