// Source: https://leetcode.com/problems/rotate-image
// Title: Rotate Image
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
  void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();

    for (auto i = 0; i < n / 2; i++) {
      for (auto j = i; j < n - i - 1; j++) {
        auto ni1 = n - i - 1;
        auto nj1 = n - j - 1;
        auto tmp = matrix[i][j];
        matrix[i][j] = matrix[nj1][i];
        matrix[nj1][i] = matrix[ni1][nj1];
        matrix[ni1][nj1] = matrix[j][ni1];
        matrix[j][ni1] = tmp;
      }
    }
  }
};
