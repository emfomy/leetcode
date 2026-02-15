// Source: https://leetcode.com/problems/n-queens-ii
// Title: N-Queens II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The **n-queens** puzzle is the problem of placing `n` queens on an `n x n` chessboard such that no two queens attack each other.
//
// Given an integer `n`, return the number of distinct solutions to the**n-queens puzzle**.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/11/13/queens.jpg
//
// ```
// Input: n = 4
// Output: 2
// Explanation: There are two distinct solutions to the 4-queens puzzle as shown.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 1
// Output: 1
// ```
//
// **Constraints:**
//
// - `1 <= n <= 9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

// Permutation
class Solution {
 public:
  int totalNQueens(const int n) {
    // Init indexs
    auto rows = vector<int>(n);  // row of each col
    iota(rows.begin(), rows.end(), 0);

    // Count N-Queens
    int count = 0;
    do {
      count += checkNQueens(n, rows);
    } while (next_permutation(rows.begin(), rows.end()));

    return count;
  }

  bool checkNQueens(const int n, vector<int> &rows) {
    int m = 2 * n - 1;
    auto diags = vector<bool>(m);  // diagonals
    auto antis = vector<bool>(m);  // anti-diagonals

    for (int col = 0; col < n; ++col) {
      int row = rows[col];
      int diag = row - col + n - 1, anti = row + col;
      if (diags[diag]) return false;
      if (antis[anti]) return false;
      diags[diag] = true;
      antis[anti] = true;
    }

    return true;
  }
};

// Back Tracking
class Solution2 {
 public:
  int totalNQueens(const int n) {
    auto cols = vector<int>(n);  // column of each row
    return dfs(n, 0, cols);
  }

  int dfs(const int n, const int currRow, vector<int> &cols) {
    if (currRow == n) {
      return 1;
    }

    int count = 0;
    for (int currCol = 0; currCol < n; ++currCol) {
      // Check if not contradict to previous queen
      int isValid = true;
      for (int prevRow = 0; prevRow < currRow && isValid; ++prevRow) {
        const int prevCol = cols[prevRow];
        const int currDiag = currCol - currRow, prevDiag = prevCol - prevRow;  // diagonal
        const int currAnti = currCol + currRow, prevAnti = prevCol + prevRow;  // anti-diagonal

        if (currRow == prevRow || currCol == prevCol || currDiag == prevDiag || currAnti == prevAnti) {
          isValid = false;
        }
      }

      if (isValid) {
        cols[currRow] = currCol;
        count += dfs(n, currRow + 1, cols);
      }
    }

    return count;
  }
};

// Back Tracking + Hash Set
class Solution3 {
  struct Board {
    vector<bool> seenRows;
    vector<bool> seenCols;
    vector<bool> seenDiags;  // diagonals
    vector<bool> seenAntis;  // anti-diagonals

    Board(const int n) : seenCols(n), seenRows(n), seenDiags(2 * n - 1), seenAntis(2 * n - 1) {}

    bool check(const int row, const int col) {
      int n = seenRows.size();
      return !seenRows[row] && !seenCols[col] && !seenDiags[row - col + n - 1] && !seenAntis[row + col];
    }

    void set(const int row, const int col, const bool flag) {
      int n = seenRows.size();
      seenRows[row] = flag;
      seenCols[col] = flag;
      seenDiags[row - col + n - 1] = flag;
      seenAntis[row + col] = flag;
    }
  };

 public:
  int totalNQueens(const int n) {
    auto board = Board(n);

    return dfs(n, 0, board);
  }

  int dfs(const int n, const int currRow, Board &board) {
    if (currRow == n) {
      return 1;
    }

    int count = 0;
    for (int currCol = 0; currCol < n; ++currCol) {
      if (board.check(currRow, currCol)) {
        board.set(currRow, currCol, true);
        count += dfs(n, currRow + 1, board);
        board.set(currRow, currCol, false);
      }
    }

    return count;
  }
};
