// Source: https://leetcode.com/problems/word-search-ii
// Title: Word Search II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an `m x n` `board`of characters and a list of strings `words`, return all words on the board.
//
// Each word must be constructed from letters of sequentially adjacent cells, where **adjacent cells** are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2020/11/07/search1.jpg
//
// ```
// Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
// Output: ["eat","oath"]
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2020/11/07/search2.jpg
//
// ```
// Input: board = [["a","b"],["c","d"]], words = ["abcb"]
// Output: []
// ```
//
// **Constraints:**
//
// - `m == board.length`
// - `n == board[i].length`
// - `1 <= m, n <= 12`
// - `board[i][j]` is a lowercase English letter.
// - `1 <= words.length <= 3 * 10^4`
// - `1 <= words[i].length <= 10`
// - `words[i]` consists of lowercase English letters.
// - All the strings of `words` are unique.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// DFS + Backtracking (TLE)
class Solution {
 public:
  vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    int m = board.size(), n = board[0].size();

    // Backtracking state, use uint8_t to avoid vector<bool>
    auto visited = vector(m, vector(n, uint8_t(0)));

    // DFS, Use Y-combinator
    auto dfs = [&](auto&& self, string& word, int i, int j, int k) -> bool {
      if (k == word.size()) return true;
      if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || board[i][j] != word[k]) return false;

      visited[i][j] = true;
      auto done = false;
      if (!done && self(self, word, i - 1, j, k + 1)) done = true;
      if (!done && self(self, word, i + 1, j, k + 1)) done = true;
      if (!done && self(self, word, i, j - 1, k + 1)) done = true;
      if (!done && self(self, word, i, j + 1, k + 1)) done = true;
      visited[i][j] = false;

      return done;
    };

    // Find word
    auto findWord = [&](string& word) -> bool {
      for (auto i = 0; i < m; ++i) {
        for (auto j = 0; j < n; ++j) {
          if (dfs(dfs, word, i, j, 0)) return true;
        }
      }
      return false;
    };

    // Loop
    auto ans = vector<string>();
    for (auto& word : words) {
      if (findWord(word)) ans.push_back(word);
    }
    return ans;
  }
};

// DFS + Backtracking + Prefix Set
class Solution2 {
 public:
  vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    int m = board.size(), n = board[0].size();

    // World set
    auto wordSet = unordered_set<string>();    // word set
    auto prefixSet = unordered_set<string>();  // prefix set
    for (auto& word : words) {
      wordSet.insert(word);
      for (auto k = 1; k <= word.size(); ++k) {
        prefixSet.insert(word.substr(0, k));
      }
    }

    // Backtracking state, use uint8_t to avoid vector<bool>
    auto visited = vector(m, vector(n, uint8_t(0)));

    // DFS, Use Y-combinator
    auto ansSet = unordered_set<string>();
    auto dfs = [&](auto&& self, int i, int j, string str) {
      if (visited[i][j]) return;
      str += board[i][j];
      if (!prefixSet.contains(str)) return;
      if (wordSet.contains(str)) ansSet.insert(str);

      visited[i][j] = true;
      if (i > 0) self(self, i - 1, j, str);
      if (i < m - 1) self(self, i + 1, j, str);
      if (j > 0) self(self, i, j - 1, str);
      if (j < n - 1) self(self, i, j + 1, str);
      visited[i][j] = false;

      return;
    };

    // Loop
    for (auto i = 0; i < m; ++i) {
      for (auto j = 0; j < n; ++j) {
        dfs(dfs, i, j, "");
      }
    }

    return vector(ansSet.cbegin(), ansSet.cend());
  }
};
