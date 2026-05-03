// Source: https://leetcode.com/problems/maximum-score-from-grid-operations
// Title: Maximum Score From Grid Operations
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a 2D matrix `grid` of size `n x n`. Initially, all cells of the grid are colored white. In one operation, you can select any cell of indices `(i, j)`, and color black all the cells of the `j^th` column starting from the top row down to the `i^th` row.
//
// The grid score is the sum of all `grid[i][j]` such that cell `(i, j)` is white and it has a horizontally adjacent black cell.
//
// Return the **maximum** score that can be achieved after some number of operations.
//
// **Example 1:**
//
// ```
// Input: grid = [[0,0,0,0,0],[0,0,3,0,0],[0,1,0,0,0],[5,0,0,3,0],[0,0,0,0,2]]
// Output: 11
// Explanation:
// https://assets.leetcode.com/uploads/2024/05/11/one.png
// In the first operation, we color all cells in column 1 down to row 3, and in the second operation, we color all cells in column 4 down to the last row. The score of the resulting grid is `grid[3][0] + grid[1][2] + grid[3][3]` which is equal to 11.
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[10,9,0,0,15],[7,1,0,8,0],[5,20,0,11,0],[0,0,0,1,2],[8,12,1,10,3]]
// Output: 94
// Explanation:
// https://assets.leetcode.com/uploads/2024/05/11/two-1.png
// We perform operations on 1, 2, and 3 down to rows 1, 4, and 0, respectively. The score of the resulting grid is `grid[0][0] + grid[1][0] + grid[2][1] + grid[4][1] + grid[1][3] + grid[2][3] + grid[3][3] + grid[4][3] + grid[0][4]` which is equal to 94.
// ```
//
// **Constraints:**
//
// - `1 <=n == grid.length <= 100`
// - `n == grid[i].length`
// - `0 <= grid[i][j] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// DP + Prefix Sum, TLE
//
// We run DP on columns.
// Each column has n+1 states (height, number of black cells).
//
// For each column state, compare to the previous two columns.
// Denote the last three columns as c1, c2, c3 (c3 is the last),
// and the heights as h1, h2, h3.
//
// If h3 <= h2,      then includes the score of [h3, h2) cells in c3.
// If h1 < h2 < h3,  then includes the score of [h2, h3) cells in c2.
// If h2 <= h1 < h3, then includes the score of [h1, h3) cells in c2.
// If h2 < h3 <= h1, then no new scores.
//
// We use prefix sum to speed up the score sum.
class Solution {
 public:
  long long maximumScore(const vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    auto prevDp = vector<vector<long long>>(m + 1, vector<long long>(m + 1));
    auto currDp = vector<vector<long long>>(m + 1, vector<long long>(m + 1));
    auto prevSum = vector<long long>(m + 1);
    auto currSum = vector<long long>(m + 1);

    currSum[0] = 0;
    for (int j = 0; j < m; ++j) {
      currSum[j + 1] = currSum[j] + grid[j][0];
    }

    for (int i = 1; i < n; ++i) {
      swap(currDp, prevDp);
      swap(prevSum, currSum);

      currSum[0] = 0;
      for (int j = 0; j < m; ++j) {
        currSum[j + 1] = currSum[j] + grid[j][i];
      }

      for (int h3 = 0; h3 <= m; ++h3) {
        // h2 < h3
        for (int h2 = 0; h2 < h3; ++h2) {
          currDp[h3][h2] = 0;

          // h1 < h2
          for (int h1 = 0; h1 <= h2; ++h1) {
            currDp[h3][h2] = max(currDp[h3][h2], prevDp[h2][h1] + prevSum[h3] - prevSum[h2]);
          }

          // h2 < h1 < h3
          for (int h1 = h2; h1 <= h3; ++h1) {
            currDp[h3][h2] = max(currDp[h3][h2], prevDp[h2][h1] + prevSum[h3] - prevSum[h1]);
          }

          // h3 <= h1
          for (int h1 = h3; h1 <= m; ++h1) {
            currDp[h3][h2] = max(currDp[h3][h2], prevDp[h2][h1]);
          }
        }

        // h2 >= h3
        for (int h2 = h3; h2 <= m; ++h2) {
          currDp[h3][h2] = 0;

          for (int h1 = 0; h1 <= m; ++h1) {
            currDp[h3][h2] = max(currDp[h3][h2], prevDp[h2][h1]);
          }
          currDp[h3][h2] += currSum[h2] - currSum[h3];
        }
      }
    }

    // Answer
    long long ans = 0;
    for (int h3 = 0; h3 <= m; ++h3) {
      for (int h2 = 0; h2 <= m; ++h2) {
        ans = max(ans, currDp[h3][h2]);
      }
    }

    return ans;
  }
};

// DP + Prefix Sum
//
// If h3 <= h2,      then includes the score of [h3, h2) cells in c3.
// If h1 < h2 < h3,  then includes the score of [h2, h3) cells in c2.
// If h2 <= h1 < h3, then includes the score of [h1, h3) cells in c2.
// If h2 < h3 <= h1, then no new scores.
//
// Let DPA[h] = max DP[h][h1]  for all h1
// Let DPB[h] = max DP[h2][h1] with max(h1, h2) = h
class Solution2 {
 public:
  long long maximumScore(const vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    auto prevDpA = vector<long long>(m + 1);
    auto currDpA = vector<long long>(m + 1);
    auto prevDpB = vector<long long>(m + 1);
    auto currDpB = vector<long long>(m + 1);
    auto prevSum = vector<long long>(m + 1);
    auto currSum = vector<long long>(m + 1);

    currSum[0] = 0;
    for (int j = 0; j < m; ++j) {
      currSum[j + 1] = currSum[j] + grid[j][0];
    }

    for (int i = 1; i < n; ++i) {
      swap(currDpA, prevDpA);
      swap(currDpB, prevDpB);
      swap(prevSum, currSum);

      currSum[0] = 0;
      for (int j = 0; j < m; ++j) {
        currSum[j + 1] = currSum[j] + grid[j][i];
      }

      fill(currDpA.begin(), currDpA.end(), 0);
      fill(currDpB.begin(), currDpB.end(), 0);

      for (int h3 = 0; h3 <= m; ++h3) {
        // h2 >= h3
        for (int h2 = h3; h2 <= m; ++h2) {
          long long score = prevDpA[h2] + currSum[h2] - currSum[h3];
          currDpA[h3] = max(currDpA[h3], score);
          currDpB[h2] = max(currDpB[h2], score);
        }

        // max(h1, h2) < h3
        for (int h12 = 0; h12 < h3; ++h12) {
          long long score = prevDpB[h12] + prevSum[h3] - prevSum[h12];
          currDpA[h3] = max(currDpA[h3], score);
          currDpB[h3] = max(currDpB[h3], score);
        }

        // h2 < h3 (covering h2 < h3 <= h1)
        for (int h2 = 0; h2 < h3; ++h2) {
          long long score = prevDpA[h2];
          currDpA[h3] = max(currDpA[h3], score);
          currDpB[h3] = max(currDpB[h3], score);
        }
      }
    }

    return max(*max_element(currDpA.cbegin(), currDpA.cend()), *max_element(currDpB.cbegin(), currDpB.cend()));
  }
};

// DP + Prefix Sum, Optimized
//
// Instead of initialize DPA and DPB zero, we initialize it using h2 < h3 condition.
//
// In the last column:
// If h2 >= h3, then h3=0 is the best (include most cells in c3).
// If h2 < h3, then h3=m is the best (include most cells in c2).
// Since there is no further columns, we can simply choose h3=0 or h3=m.
// Also, DPA[0] >= DPB[0] and DPA[m] <= DPB[m] (since the smaller one is included in the larger one).
class Solution3 {
 public:
  long long maximumScore(const vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    auto prevDpA = vector<long long>(m + 1);
    auto currDpA = vector<long long>(m + 1);
    auto prevDpB = vector<long long>(m + 1);
    auto currDpB = vector<long long>(m + 1);
    auto prevSum = vector<long long>(m + 1);
    auto currSum = vector<long long>(m + 1);

    currSum[0] = 0;
    for (int j = 0; j < m; ++j) {
      currSum[j + 1] = currSum[j] + grid[j][0];
    }

    for (int i = 1; i < n; ++i) {
      swap(currDpA, prevDpA);
      swap(currDpB, prevDpB);
      swap(prevSum, currSum);

      // Prefix sum
      currSum[0] = 0;
      for (int j = 0; j < m; ++j) {
        currSum[j + 1] = currSum[j] + grid[j][i];
      }

      // Init
      {
        long long score = 0;
        for (int h3 = 0; h3 <= m; ++h3) {
          currDpA[h3] = score;
          currDpB[h3] = score;
          score = max(score, prevDpA[h3]);
        }
      }

      // Loop
      for (int h3 = 0; h3 <= m; ++h3) {
        // h2 >= h3
        for (int h2 = h3; h2 <= m; ++h2) {
          long long score = prevDpA[h2] + currSum[h2] - currSum[h3];
          currDpA[h3] = max(currDpA[h3], score);
          currDpB[h2] = max(currDpB[h2], score);
        }

        // max(h1, h2) < h3
        for (int h12 = 0; h12 < h3; ++h12) {
          long long score = prevDpB[h12] + prevSum[h3] - prevSum[h12];
          currDpA[h3] = max(currDpA[h3], score);
          currDpB[h3] = max(currDpB[h3], score);
        }
      }
    }

    return max(currDpA.front(), currDpB.back());
  }
};
