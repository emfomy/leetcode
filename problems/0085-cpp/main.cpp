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
  int maximalRectangle(const vector<vector<char>>& matrix) {
    const int m = matrix.size(), n = matrix[0].size();
    auto dp = vector(m + 1, vector(m + 1, vector(n + 1, 0)));
    auto ans = 0;

    // k = 1
    for (int i = m - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 0; --j) {
        if (matrix[i][j] == '1') {
          dp[1][i][j] = dp[1][i][j + 1] + 1;
          ans = max(ans, dp[1][i][j]);
        }
      }
    }

    // k > 1
    for (int k = 2; k <= m; ++k) {
      for (int i = m - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
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

// Monotonic Stack
//
// Loop for rows. For each row:
// First update the height above this row (including).
// Next compute the maximum area using monotonic stack.
//
// We put (height, position) in the stack, both of them are increasing.
// It represent the leftmost possible rectangle of each height.
//
// We loop the bars from the left.
// If the new bar is shorter than the top height,
// then pop it and compute the maximum rectangle,
// and then push the new bar height with the previous top position (since it can reach this far).
// We only push the new bar if it is taller than the top height.
class Solution2 {
  struct State {
    int height;
    int pos;
  };

 public:
  int maximalRectangle(const vector<vector<char>>& matrix) {
    const int n = matrix[0].size();

    // Loop
    int maxArea = 0;
    auto heights = vector(n, 0);
    for (const auto& row : matrix) {
      // Height
      for (int j = 0; j < n; ++j) {
        if (row[j] == '1') {
          ++heights[j];
        } else {
          heights[j] = 0;
        }
      }

      // Area
      auto st = stack<State>();  // leftmost possible rectangle of each height.
      st.push(State{0, 0});      // first sentinel
      for (int j = 0; j <= n; ++j) {
        int height = j < n ? heights[j] : 0;  // sentinel at i=n
        int pos = j;

        // Pop
        while (st.top().height > height) {
          maxArea = max(maxArea, st.top().height * (j - st.top().pos));
          pos = st.top().pos;
          st.pop();
        }

        // Push
        if (st.top().height < height) {
          st.push(State{height, pos});
        }
      }
    }

    return maxArea;
  }
};
