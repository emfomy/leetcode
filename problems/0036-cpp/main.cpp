// Source: https://leetcode.com/problems/valid-sudoku
// Title: Valid Sudoku
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Determine if a`9 x 9` Sudoku boardis valid.Only the filled cells need to be validated**according to the following rules**:
//
// - Each rowmust contain thedigits`1-9` without repetition.
// - Each column must contain the digits`1-9`without repetition.
// - Each of the nine`3 x 3` sub-boxes of the grid must contain the digits`1-9`without repetition.
//
// **Note:**
//
// - A Sudoku board (partially filled) could be valid but is not necessarily solvable.
// - Only the filled cells need to be validated according to the mentionedrules.
//
// **Example 1:**
// https://upload.wikimedia.org/wikipedia/commons/thumb/f/ff/Sudoku-by-L2G-20050714.svg/250px-Sudoku-by-L2G-20050714.svg.png
//
// ```
// Input: board =
// [["5","3",".",".","7",".",".",".","."]
// ,["6",".",".","1","9","5",".",".","."]
// ,[".","9","8",".",".",".",".","6","."]
// ,["8",".",".",".","6",".",".",".","3"]
// ,["4",".",".","8",".","3",".",".","1"]
// ,["7",".",".",".","2",".",".",".","6"]
// ,[".","6",".",".",".",".","2","8","."]
// ,[".",".",".","4","1","9",".",".","5"]
// ,[".",".",".",".","8",".",".","7","9"]]
// Output: true
// ```
//
// **Example 2:**
//
// ```
// Input: board =
// [["8","3",".",".","7",".",".",".","."]
// ,["6",".",".","1","9","5",".",".","."]
// ,[".","9","8",".",".",".",".","6","."]
// ,["8",".",".",".","6",".",".",".","3"]
// ,["4",".",".","8",".","3",".",".","1"]
// ,["7",".",".",".","2",".",".",".","6"]
// ,[".","6",".",".",".",".","2","8","."]
// ,[".",".",".","4","1","9",".",".","5"]
// ,[".",".",".",".","8",".",".","7","9"]]
// Output: false
// Explanation: Same as Example 1, except with the **5** in the top left corner being modified to **8**. Since there are two 8's in the top left 3x3 sub-box, it is invalid.
// ```
//
// **Constraints:**
//
// - `board.length == 9`
// - `board[i].length == 9`
// - `board[i][j]` is a digit `1-9` or `'.'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Use Bit-mask
class Solution {
 public:
  bool isValidSudoku(vector<vector<char>>& board) {
    // Rows
    for (auto r = 0; r < 9; r++) {
      auto bits = 0;
      for (auto c = 0; c < 9; c++) {
        auto cell = board[r][c];
        if (cell != '.') {
          auto bit = 1 << (cell - '0');
          if (bits & bit) {
            return false;
          }
          bits |= bit;
        }
      }
    }

    // Columns
    for (auto c = 0; c < 9; c++) {
      auto bits = 0;
      for (auto r = 0; r < 9; r++) {
        auto cell = board[r][c];
        if (cell != '.') {
          auto bit = 1 << (cell - '0');
          if (bits & bit) {
            return false;
          }
          bits |= bit;
        }
      }
    }

    // Boxes
    for (auto br = 0; br < 9; br += 3) {
      for (auto bc = 0; bc < 9; bc += 3) {
        auto bits = 0;
        for (auto r = br; r < br + 3; r++) {
          for (auto c = bc; c < bc + 3; c++) {
            auto cell = board[r][c];
            if (cell != '.') {
              auto bit = 1 << (cell - '0');
              if (bits & bit) {
                return false;
              }
              bits |= bit;
            }
          }
        }
      }
    }

    return true;
  }
};
