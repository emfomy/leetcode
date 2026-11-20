// Source: https://leetcode.com/problems/number-of-paths-with-max-score
// Title: Number of Paths with Max Score
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a square `board` of characters. You can move on the board starting at the bottom right square marked with the character`'S'`.
//
// You needto reach the top left square marked with the character `'E'`. The rest of the squares are labeled either with a numeric character`1, 2, ..., 9` or with an obstacle `'X'`. In one move you can go up, left or up-left (diagonally) only if there is no obstacle there.
//
// Return a list of two integers: the first integer is the maximum sum of numeric characters you can collect, and the second is the number of such paths that you can take to get that maximum sum, **taken modulo `10^9 + 7`**.
//
// In case there is no path, return`[0, 0]`.
//
// **Example 1:**
//
// ```
// Input: board = ["E23","2X2","12S"]
// Output: [7,1]
// ```
//
// **Example 2:**
//
// ```
// Input: board = ["E12","1X1","21S"]
// Output: [4,2]
// ```
//
// **Example 3:**
//
// ```
// Input: board = ["E11","XXX","11S"]
// Output: [0,0]
// ```
//
// **Constraints:**
//
// - `2 <= board.length == board[i].length <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Dijkstra
//
// First use a BFS to find the maximum score.
// For each cell, store the max score to that cell,
// and the number of path with that score.
class Solution {
  constexpr static int modulo = 1e9 + 7;

 public:
  vector<int> pathsWithMaxScore(const vector<string>& board) {
    const int m = board.size(), n = board[0].size();

    // BFS
    auto scores = vector<vector<int>>(m, vector<int>(n));
    auto freqs = vector<vector<int>>(m, vector<int>(n));
    freqs[0][0] = 1;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (board[i][j] == 'X' || board[i][j] == 'E') continue;  // obstacle or start

        int num = (board[i][j] == 'S') ? 0 : (board[i][j] - '0');

        if (i > 0 && freqs[i - 1][j] > 0) {
          int newScore = scores[i - 1][j] + num;
          if (scores[i][j] < newScore) {
            scores[i][j] = newScore;
            freqs[i][j] = freqs[i - 1][j];
          } else if (scores[i][j] == newScore) {
            freqs[i][j] = (freqs[i][j] + freqs[i - 1][j]) % modulo;
          }
        }

        if (j > 0 && freqs[i][j - 1] > 0) {
          int newScore = scores[i][j - 1] + num;
          if (scores[i][j] < newScore) {
            scores[i][j] = newScore;
            freqs[i][j] = freqs[i][j - 1];
          } else if (scores[i][j] == newScore) {
            freqs[i][j] = (freqs[i][j] + freqs[i][j - 1]) % modulo;
          }
        }

        if (i > 0 && j > 0 && freqs[i - 1][j - 1] > 0) {
          int newScore = scores[i - 1][j - 1] + num;
          if (scores[i][j] < newScore) {
            scores[i][j] = newScore;
            freqs[i][j] = freqs[i - 1][j - 1];
          } else if (scores[i][j] == newScore) {
            freqs[i][j] = (freqs[i][j] + freqs[i - 1][j - 1]) % modulo;
          }
        }
      }
    }

    return {scores.back().back(), freqs.back().back()};
  }
};
