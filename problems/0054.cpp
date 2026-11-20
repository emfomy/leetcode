// Source: https://leetcode.com/problems/spiral-matrix
// Title: Spiral Matrix
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an `m x n` `matrix`, return all elements of the `matrix` in spiral order.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/11/13/spiral1.jpg
//
// ```
// Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [1,2,3,6,9,8,7,4,5]
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/11/13/spiral.jpg
//
// ```
// Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
// Output: [1,2,3,4,8,12,11,10,9,5,6,7]
// ```
//
// **Constraints:**
//
// - `m == matrix.length`
// - `n == matrix[i].length`
// - `1 <= m, n <= 10`
// - `-100 <= matrix[i][j] <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    vector<int> ans;
    ans.reserve(m * n);

    // boundaries
    auto left = 0;
    auto right = n - 1;
    auto up = 0;
    auto down = m - 1;

    while (true) {
      // Right
      if (left > right) {
        break;
      }
      for (auto i = left; i <= right; i++) {
        ans.push_back(matrix[up][i]);
      }
      up++;

      // Down
      if (up > down) {
        break;
      }
      for (auto j = up; j <= down; j++) {
        ans.push_back(matrix[j][right]);
      }
      right--;

      // Left
      if (left > right) {
        break;
      }
      for (auto i = right; i >= left; i--) {
        ans.push_back(matrix[down][i]);
      }
      down--;

      // Down
      if (up > down) {
        break;
      }
      for (auto j = down; j >= up; j--) {
        ans.push_back(matrix[j][left]);
      }
      left++;
    }

    return ans;
  }
};
