// Source: https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix
// Title: Count Negative Numbers in a Sorted Matrix
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a `m x n` matrix `grid` which is sorted in non-increasing order both row-wise and column-wise, return the number of **negative** numbers in `grid`.
//
// **Example 1:**
//
// ```
// Input: grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
// Output: 8
// Explanation: There are 8 negatives number in the matrix.
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[3,2],[1,0]]
// Output: 0
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 100`
// - `-100 <= grid[i][j] <= 100`
//
// **Follow up:** Could you find an `O(n + m)` solution?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Binary Search
class Solution {
 public:
  int countNegatives(vector<vector<int>>& grid) {
    auto ans = 0;
    for (auto& row : grid) {
      ans += lower_bound(row.crbegin(), row.crend(), 0) - row.crbegin();
    }

    return ans;
  }
};

// Linear Traversal
class Solution2 {
 public:
  int countNegatives(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    auto ans = 0;
    auto j = n - 1;  // column index
    for (auto& row : grid) {
      while (j >= 0 && row[j] < 0) --j;
      ans += (n - 1) - j;
    }

    return ans;
  }
};
