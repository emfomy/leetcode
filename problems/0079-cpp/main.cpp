// Source: https://leetcode.com/problems/word-search
// Title: Word Search
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an `m x n` grid of characters `board` and a string `word`, return `true` if `word` exists in the grid.
//
// The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2020/11/04/word2.jpg
//
// ```
// Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
// Output: true
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2020/11/04/word-1.jp
//
// ```
// Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
// Output: true
// ```
//
// **Example 3:**
//
// https://assets.leetcode.com/uploads/2020/10/15/word3.jpg
//
// ```
// Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
// Output: false
// ```
//
// **Constraints:**
//
// - `m == board.length`
// - `n = board[i].length`
// - `1 <= m, n <= 6`
// - `1 <= word.length <= 15`
// - `board` and `word` consists of only lowercase and uppercase English letters.
//
// **Follow up:** Could you use search pruning to make your solution faster with a larger `board`?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <vector>

using namespace std;

// DFS + Backtracking
class Solution {
 public:
  bool exist(vector<vector<char>>& board, string word) {
    int m = board.size(), n = board[0].size(), l = word.size();

    // Backtracking state, use uint8_t to avoid vector<bool>
    auto visited = vector(m, vector(n, uint8_t(0)));

    // DFS, Use Y-combinator
    auto dfs = [&](auto&& self, int i, int j, int k) -> bool {
      if (k == l) return true;
      if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || board[i][j] != word[k]) return false;

      visited[i][j] = true;
      if (self(self, i - 1, j, k + 1)) return true;
      if (self(self, i + 1, j, k + 1)) return true;
      if (self(self, i, j - 1, k + 1)) return true;
      if (self(self, i, j + 1, k + 1)) return true;
      visited[i][j] = false;

      return false;
    };

    // Loop
    for (auto i = 0; i < m; ++i) {
      for (auto j = 0; j < n; ++j) {
        if (dfs(dfs, i, j, 0)) return true;
      }
    }
    return false;
  }
};
