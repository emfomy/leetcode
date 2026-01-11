// Source: https://leetcode.com/problems/maximal-rectangle
// Title: Maximal Rectangle
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a `rows x cols`binary `matrix` filled with `0`'s and `1`'s, find the largest rectangle containing only `1`'s and return its area.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/09/14/maximal.jpg
//
// ```
// Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
// Output: 6
// Explanation: The maximal rectangle is shown in the above picture.
// ```
//
// **Example 2:**
//
// ```
// Input: matrix = [["0"]]
// Output: 0
// ```
//
// **Example 3:**
//
// ```
// Input: matrix = [["1"]]
// Output: 1
// ```
//
// **Constraints:**
//
// - `rows == matrix.length`
// - `cols == matrix[i].length`
// - `1 <= rows, cols <= 200`
// - `matrix[i][j]` is `'0'` or `'1'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stack>
#include <vector>

#include "../../utils/cpp/print.hpp"

using namespace std;

// DP
//
// Loop for all possible rectangle height.
// Say the height is k.
//
// DP[k][i][j] is the maximum width of height-k rectangle with (i, j) as bottom-right corner.
// If matrix[i][j] = 0, then DP[k][i][j] = 0
// Otherwise, DP[k][i][j] = min(DP[k-1][i-1][j], DP[k][i][j-1]+1)
class Solution {
 public:
  int maximalRectangle(vector<vector<char>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    auto dp = vector(m + 1, vector(m + 1, vector(n + 1, 0)));
    auto ans = 0;

    // k = 1
    for (auto i = m - 1; i >= 0; --i) {
      for (auto j = n - 1; j >= 0; --j) {
        if (matrix[i][j] == '1') {
          dp[1][i][j] = dp[1][i][j + 1] + 1;
          ans = max(ans, dp[1][i][j]);
        }
      }
    }

    // k > 1
    for (auto k = 2; k <= m; ++k) {
      for (auto i = m - 1; i >= 0; --i) {
        for (auto j = n - 1; j >= 0; --j) {
          if (matrix[i][j] == '1') {
            dp[k][i][j] = min(dp[k - 1][i + 1][j], dp[k][i][j + 1] + 1);
            ans = max(ans, k * dp[k][i][j]);
          }
        }
      }
    }

    return ans;
  }
};

// DP + Monotonic Stack
//
// First use DP to compute the maximum 1-width height of each cell.
//
// Now loop for each row, and use the same idea of problem 84 to find the maximum area.
// We find the how far can a bar reach to the left & right.
//
// Now focus on the right part.
// If the top of the stack is taller than current bar,
// then the top bar can't reach current bar, and we can pop it.
//
// Same as the left part.
class Solution2 {
 public:
  int maximalRectangle(vector<vector<char>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();

    // Loop
    auto ans = 0;
    auto heights = vector(n, 0);
    for (auto i = 0; i < m; ++i) {
      // Height
      for (auto j = 0; j < n; ++j) {
        if (matrix[i][j] == '1') {
          ++heights[j];
        } else {
          heights[j] = 0;
        }
      }

      // Right
      auto rights = vector(n, n);  // rightmost is n, monotonic increase
      {
        auto st = stack<int>();
        for (auto j = 0; j < n; ++j) {
          auto h = heights[j];
          while (!st.empty() && heights[st.top()] > h) {
            rights[st.top()] = j;  // range is [?, j)
            st.pop();
          }
          st.push(j);
        }
      }

      // Left
      auto lefts = vector(n, 0);  // leftmost is 0, monotonic increase
      {
        auto st = stack<int>();
        for (auto j = n - 1; j >= 0; --j) {
          auto h = heights[j];
          while (!st.empty() && heights[st.top()] > h) {
            lefts[st.top()] = j + 1;  // range is [j+1, ?)
            st.pop();
          }
          st.push(j);
        }
      }

      // Answer
      for (auto j = 0; j < n; ++j) {
        ans = max(ans, heights[j] * (rights[j] - lefts[j]));
      }
    }

    return ans;
  }
};
