// Source: https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid
// Title: Minimum Swaps to Arrange a Binary Grid
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an `n x n` binary `grid`, in one step you can choose two **adjacent rows** of the grid and swap them.
//
// A grid is said to be **valid** if all the cells above the main diagonal are **zeros**.
//
// Return the minimum number of steps needed to make the grid valid, or **-1** if the grid cannot be valid.
//
// The main diagonal of a grid is the diagonal that starts at cell `(1, 1)` and ends at cell `(n, n)`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/07/28/fw.jpg
//
// ```
// Input: grid = [[0,0,1],[1,1,0],[1,0,0]]
// Output: 3
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/07/16/e2.jpg
//
// ```
// Input: grid = [[0,1,1,0],[0,1,1,0],[0,1,1,0],[0,1,1,0]]
// Output: -1
// Explanation: All rows are similar, swaps have no effect on the grid.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2020/07/16/e3.jpg
//
// ```
// Input: grid = [[1,0,0],[1,1,0],[1,1,1]]
// Output: 0
// ```
//
// **Constraints:**
//
// - `n == grid.length` `== grid[i].length`
// - `1 <= n <= 200`
// - `grid[i][j]` is either `0` or `1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Bubble Sort + Greedy
//
// First count find the rightmost 1 for each row (if no 1, treat it at (-1)-th column).
// Next sort these values and check if the value of i-th row is at most i+1.
// If not, then it is impossible.
//
// We use greedy strategy to solve this.
// We first discover that constraint is monotonic:
// the smaller the row index is, the stricter the constraint is.
// Therefore we can apply greedy strategy from the first row to the last one.
//
// Since we only allow to swap adjacent rows, we can use idea of bubble sort to simulate.
// For each row, find the first row satisfy the constraint, and swap that row to here.
class Solution {
 public:
  int minSwaps(const vector<vector<int>>& grid) {
    const int n = grid.size();

    // Find rightmost 1
    auto oneIdxs = vector<int>(n);
    for (int i = 0; i < n; ++i) {
      const auto& row = grid[i];
      const int oneIdx = row.crend() - find(row.crbegin(), row.crend(), 1) - 1;
      oneIdxs[i] = oneIdx;
    }

    // Bubble sort
    int steps = 0;
    for (int i = 0; i < n; ++i) {
      // Find first row satisfy the constraint
      int j = i;
      for (; j < n; ++j) {
        if (oneIdxs[j] <= i) break;
      }

      // Check feasibility
      if (j == n) return -1;

      // Simulate swap
      steps += j - i;
      for (; j > i; --j) {
        swap(oneIdxs[j], oneIdxs[j - 1]);
      }
    }

    return steps;
  }
};
