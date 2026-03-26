// Source: https://leetcode.com/problems/largest-submatrix-with-rearrangements
// Title: Largest Submatrix With Rearrangements
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a binary matrix `matrix` of size `m x n`, and you are allowed to rearrange the **columns** of the `matrix` in any order.
//
// Return the area of the largest submatrix within `matrix` where **every** element of the submatrix is `1` after reordering the columns optimally.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/12/29/screenshot-2020-12-30-at-40536-pm.png
//
// ```
// Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
// Output: 4
// Explanation: You can rearrange the columns as shown above.
// The largest submatrix of 1s, in bold, has an area of 4.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/12/29/screenshot-2020-12-30-at-40852-pm.png
//
// ```
// Input: matrix = [[1,0,1,0,1]]
// Output: 3
// Explanation: You can rearrange the columns as shown above.
// The largest submatrix of 1s, in bold, has an area of 3.
// ```
//
// **Example 3:**
//
// ```
// Input: matrix = [[1,1,0],[1,0,1]]
// Output: 2
// Explanation: Notice that you must rearrange entire columns, and there is no way to make a submatrix of 1s larger than an area of 2.
// ```
//
// **Constraints:**
//
// - `m == matrix.length`
// - `n == matrix[i].length`
// - `1 <= m * n <= 10^5`
// - `matrix[i][j]` is either `0` or `1`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// Sort
//
// For each column, we compute the consecutive ones ending at each position.
// Next for each row, sort the numbers and compute the maximum area.
class Solution {
 public:
  int largestSubmatrix(const vector<vector<int>>& matrix) {
    const int m = matrix.size(), n = matrix[0].size();

    // Prepare
    int maxArea = 0;
    auto heights = vector<int>(n, 0);
    auto idxs = vector<int>(n);
    iota(idxs.begin(), idxs.end(), 0);

    // Loop
    for (int i = 0; i < m; ++i) {
      // Count consecutive ones
      for (int j = 0; j < n; ++j) {
        heights[j] = matrix[i][j] ? heights[j] + 1 : 0;
      }

      // Sort
      auto comp = [&heights](int i, int j) -> bool { return heights[i] > heights[j]; };
      sort(idxs.begin(), idxs.end(), comp);

      // Find max area
      for (int j = 0; j < n; ++j) {
        maxArea = max(maxArea, heights[idxs[j]] * (j + 1));
      }
    }

    return maxArea;
  }
};

// No Sort
//
// For each column, we compute the consecutive ones ending at each position.
// Next for each row, sort the numbers and compute the maximum area.
//
// Note that for each step, the there are only two cases:
// increase by 1 or reset to zero.
//
// Therefore we can use a new array instead of sorting.
// When increate by 1, push into the new array. (The ordering is kept).
// When reset to zero, just skip.
// We will fill the array with zeros.
class Solution2 {
 public:
  int largestSubmatrix(const vector<vector<int>>& matrix) {
    const int m = matrix.size(), n = matrix[0].size();

    // Prepare
    int maxArea = 0;
    auto heights = vector<int>(n, 0);
    auto prevIdxs = vector<int>(n);
    auto currIdxs = vector<int>(n);
    iota(currIdxs.begin(), currIdxs.end(), 0);

    // Loop
    for (int i = 0; i < m; ++i) {
      swap(prevIdxs, currIdxs);

      // Count consecutive ones
      currIdxs.clear();
      for (int j : prevIdxs) {
        if (matrix[i][j]) {
          ++heights[j];
          currIdxs.push_back(j);
        } else {
          heights[j] = 0;
        }
      }

      // Fill zeros
      for (int j = 0; j < n; ++j) {
        if (heights[j] == 0) currIdxs.push_back(j);
      }

      // Find max area
      for (int j = 0; j < n; ++j) {
        maxArea = max(maxArea, heights[currIdxs[j]] * (j + 1));
      }
    }

    return maxArea;
  }
};
