// Source: https://leetcode.com/problems/count-submatrices-with-equal-frequency-of-x-and-y
// Title: Count Submatrices With Equal Frequency of X and Y
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a 2D character matrix `grid`, where `grid[i][j]` is either `'X'`, `'Y'`, or `'.'`, return the number of <button>submatrices</button> that contain:
//
// - `grid[0][0]`
// - an **equal** frequency of `'X'` and `'Y'`.
// - **at least** one `'X'`.
//
// **Example 1:**
//
// ```
// Input: grid = [["X","Y","."],["Y",".","."]]
// Output: 3
// Explanation:
// **https://assets.leetcode.com/uploads/2024/06/07/examplems.png**
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [["X","X"],["X","Y"]]
// Output: 0
// Explanation:
// No submatrix has an equal frequency of `'X'` and `'Y'`.
// ```
//
// **Example 3:**
//
// ```
// Input: grid = [[".","."],[".","."]]
// Output: 0
// Explanation:
// No submatrix has at least one `'X'`.
// ```
//
// **Constraints:**
//
// - `1 <= grid.length, grid[i].length <= 1000`
// - `grid[i][j]` is either `'X'`, `'Y'`, or `'.'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Prefix Sum
//
// Use prefix sum to compute the number of x and y.
class Solution {
 public:
  int numberOfSubmatrices(const vector<vector<char>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    auto xCnt = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
    auto yCnt = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));

    int count = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        xCnt[i + 1][j + 1] = (grid[i][j] == 'X') + xCnt[i][j + 1] + xCnt[i + 1][j] - xCnt[i][j];
        yCnt[i + 1][j + 1] = (grid[i][j] == 'Y') + yCnt[i][j + 1] + yCnt[i + 1][j] - yCnt[i][j];
        count += (xCnt[i + 1][j + 1] > 0 && xCnt[i + 1][j + 1] == yCnt[i + 1][j + 1]);
      }
    }

    return count;
  }
};

// Prefix Sum
//
// Use 1D array.
class Solution2 {
 public:
  int numberOfSubmatrices(const vector<vector<char>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    auto xCurr = vector<int>(n + 1);
    auto xPrev = vector<int>(n + 1);
    auto yCurr = vector<int>(n + 1);
    auto yPrev = vector<int>(n + 1);

    int count = 0;
    for (int i = 0; i < m; ++i) {
      swap(xCurr, xPrev);
      swap(yCurr, yPrev);
      for (int j = 0; j < n; ++j) {
        xCurr[j + 1] = (grid[i][j] == 'X') + xPrev[j + 1] + xCurr[j] - xPrev[j];
        yCurr[j + 1] = (grid[i][j] == 'Y') + yPrev[j + 1] + yCurr[j] - yPrev[j];
        count += (xCurr[j + 1] > 0 && xCurr[j + 1] == yCurr[j + 1]);
      }
    }

    return count;
  }
};
