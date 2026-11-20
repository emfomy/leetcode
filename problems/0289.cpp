// Source: https://leetcode.com/problems/game-of-life
// Title: Game of Life
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

// Use the second bit to represent the next state.
class Solution {
 public:
  void gameOfLife(vector<vector<int>>& board) {
    int m = board.size();
    int n = board[0].size();

    for (auto i = 0; i < m; i++) {
      for (auto j = 0; j < n; j++) {
        // Count neighbors
        auto count = -(board[i][j] & 1);  // exclude self
        for (auto ii = max(i - 1, 0); ii < min(i + 2, m); ii++) {
          for (auto jj = max(j - 1, 0); jj < min(j + 2, n); jj++) {
            if (board[ii][jj] & 1) {
              count++;
            }
          }
        }

        printf("%d %d: %d\n", i, j, count);

        // Next state
        if (count == 2 && (board[i][j] & 1) || count == 3) {
          board[i][j] += 2;
        }
      }
    }

    for (auto i = 0; i < m; i++) {
      for (auto j = 0; j < n; j++) {
        board[i][j] >>= 1;
      }
    }
  }
};
