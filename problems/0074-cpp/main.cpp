// Source: https://leetcode.com/problems/search-a-2d-matrix
// Title: Search a 2D Matrix
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` integer matrix `matrix` with the following two properties:
//
// - Each row is sorted in non-decreasing order.
// - The first integer of each row is greater than the last integer of the previous row.
//
// Given an integer `target`, return `true` if `target` is in `matrix` or `false` otherwise.
//
// You must write a solution in `O(log(m * n))` time complexity.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/10/05/mat.jpg
//
// ```
// Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
// Output: true
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/10/05/mat2.jpg
//
// ```
// Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
// Output: false
// ```
//
// **Constraints:**
//
// - `m == matrix.length`
// - `n == matrix[i].length`
// - `1 <= m, n <= 100`
// - `-10^4 <= matrix[i][j], target <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Binary Search
class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int mn = m * n;

    // Binary search
    auto lo = 0, hi = mn;  // [0, mn) unknown range
    while (lo < hi) {
      auto mid = lo + (hi - lo) / 2;
      auto val = matrix[mid / n][mid % n];
      if (val == target) return true;
      if (val < target) {
        lo = mid + 1;  // [mid+1, hi) unknown range
      } else {
        hi = mid;  // [lo, mid) unknown range
      }
    }
    return false;
  }
};
