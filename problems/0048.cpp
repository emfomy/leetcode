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

#include <tuple>
#include <vector>

using namespace std;

// Split the square into four parts by middle vertical/horizontal lines.
// For n odd, we also split these lines by the center into four segments (exclude the center).
// We treat the left segment as top-left part, the top as top-right, ...
//
// The top-left part is 0 <= i < ceil(n/2), 0 <= j < floor(n/2).
// Loop for all (i, j) in top-left part, we swap it in the following order:
// (i, j) -> (n-1-j, i) -> (n-1-i, n-1-j), (j, n-1-i) -> (i, j)
class Solution {
 public:
  void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();

    for (int i = 0; i < (n + 1) / 2; ++i) {
      for (int j = 0; j < n / 2; ++j) {
        int ni = n - 1 - i, nj = n - 1 - j;
        tie(matrix[i][j], matrix[nj][i], matrix[ni][nj], matrix[j][ni]) =
            make_tuple(matrix[nj][i], matrix[ni][nj], matrix[j][ni], matrix[i][j]);
      }
    }
  }
};
