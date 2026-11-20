// Source: https://leetcode.com/problems/rotating-the-box
// Title: Rotating the Box
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` matrix of characters `boxGrid` representing a side-view of a box. Each cell of the box is one of the following:
//
// - A stone `'#'`
// - A stationary obstacle `'*'`
// - Empty `'.'`
//
// The box is rotated **90 degrees clockwise**, causing some of the stones to fall due to gravity. Each stone falls down until it lands on an obstacle, another stone, or the bottom of the box. Gravity **does not** affect the obstacles' positions, and the inertia from the box's rotation **does not **affect the stones' horizontal positions.
//
// It is **guaranteed** that each stone in `boxGrid` rests on an obstacle, another stone, or the bottom of the box.
//
// Return an `n x m` matrix representing the box after the rotation described above.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2021/04/08/rotatingtheboxleetcodewithstones.png
//
// ```
// Input: boxGrid = [["#",".","#"]]
// Output: [["."],
//          ["#"],
//          ["#"]]
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2021/04/08/rotatingtheboxleetcode2withstones.png
//
// ```
// Input: boxGrid = [["#",".","*","."],
//                   ["#","#","*","."]]
// Output: [["#","."],
//          ["#","#"],
//          ["*","*"],
//          [".","."]]
// ```
//
// **Example 3:**
//
// https://assets.leetcode.com/uploads/2021/04/08/rotatingtheboxleetcode3withstone.png
//
// ```
// Input: boxGrid = [["#","#","*",".","*","."],
//                   ["#","#","#","*",".","."],
//                   ["#","#","#",".","#","."]]
// Output: [[".","#","#"],
//          [".","#","#"],
//          ["#","#","*"],
//          ["#","*","."],
//          ["#",".","*"],
//          ["#",".","."]]
// ```
//
// **Constraints:**
//
// - `m == boxGrid.length`
// - `n == boxGrid[i].length`
// - `1 <= m, n <= 500`
// - `boxGrid[i][j]` is either `'#'`, `'*'`, or `'.'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Two Pointer
class Solution {
 public:
  vector<vector<char>> rotateTheBox(const vector<vector<char>>& boxGrid) {
    const int m = boxGrid.size(), n = boxGrid[0].size();
    auto out = vector<vector<char>>(n, vector<char>(m, '.'));

    for (int i = 0; i < m; ++i) {
      int k = n;
      for (int j = n - 1; j >= 0; --j) {
        if (boxGrid[i][j] == '#') {
          out[--k][m - i - 1] = '#';
        } else if (boxGrid[i][j] == '*') {
          out[j][m - i - 1] = '*';
          k = j;
        }
      }
    }

    return out;
  }
};
