// Source: https://leetcode.com/problems/ones-and-zeroes
// Title: Ones and Zeroes
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of binary strings `strs` and two integers `m` and `n`.
//
// Return the size of the largest subset of `strs` such that there are **at most** `m` `0`'s and `n` `1`'s in the subset.
//
// A set `x` is a **subset** of a set `y` if all elements of `x` are also elements of `y`.
//
// **Example 1:**
//
// ```
// Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
// Output: 4
// Explanation: The largest subset with at most 5 0's and 3 1's is {"10", "0001", "1", "0"}, so the answer is 4.
// Other valid but smaller subsets include {"0001", "1"} and {"10", "1", "0"}.
// {"111001"} is an invalid subset because it contains 4 1's, greater than the maximum of 3.
// ```
//
// **Example 2:**
//
// ```
// Input: strs = ["10","0","1"], m = 1, n = 1
// Output: 2
// <b>Explanation:</b> The largest subset is {"0", "1"}, so the answer is 2.
// ```
//
// **Constraints:**
//
// - `1 <= strs.length <= 600`
// - `1 <= strs[i].length <= 100`
// - `strs[i]` consists only of digits `'0'` and `'1'`.
// - `1 <= m, n <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Use DP
//
// DP[i, j] be the  maximum length of the subset containing exactly i 1's and j 0's.
class Solution {
 public:
  int findMaxForm(vector<string>& strs, int m, int n) {
    auto curr = vector(m + 1, vector(n + 1, 0));

    for (auto str : strs) {
      auto zeros = count(str.begin(), str.end(), '0');
      auto ones = count(str.begin(), str.end(), '1');

      auto next = curr;
      for (auto i = zeros; i <= m; ++i) {
        for (auto j = ones; j <= n; ++j) {
          next[i][j] = max(next[i][j], curr[i - zeros][j - ones] + 1);
        }
      }

      swap(curr, next);
    }

    auto ans = 0;
    for (auto i = 0; i <= m; ++i) {
      for (auto j = 0; j <= n; ++j) {
        ans = max(ans, curr[i][j]);
      }
    }

    return ans;
  }
};

// Use DP
//
// DP[i, j] be the  maximum length of the subset containing exactly i 1's and j 0's.
// We don't need copy if we loop from i, j from large to small
class Solution2 {
 public:
  int findMaxForm(vector<string>& strs, int m, int n) {
    auto dp = vector(m + 1, vector(n + 1, 0));

    for (auto str : strs) {
      auto zeros = count(str.begin(), str.end(), '0');
      auto ones = count(str.begin(), str.end(), '1');

      for (auto i = m; i >= zeros; --i) {
        for (auto j = n; j >= ones; --j) {
          dp[i][j] = max(dp[i][j], dp[i - zeros][j - ones] + 1);
        }
      }
    }

    auto ans = 0;
    for (auto i = 0; i <= m; ++i) {
      for (auto j = 0; j <= n; ++j) {
        ans = max(ans, dp[i][j]);
      }
    }

    return ans;
  }
};
