// Source: https://leetcode.com/problems/edit-distance
// Title: Edit Distance
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two strings `word1` and `word2`, return the minimum number of operations required to convert `word1` to `word2`.
//
// You have the following three operations permitted on a word:
//
// - Insert a character
// - Delete a character
// - Replace a character
//
// **Example 1:**
//
// ```
// Input: word1 = "horse", word2 = "ros"
// Output: 3
// Explanation:
// horse -> rorse (replace 'h' with 'r')
// rorse -> rose (remove 'r')
// rose -> ros (remove 'e')
// ```
//
// **Example 2:**
//
// ```
// Input: word1 = "intention", word2 = "execution"
// Output: 5
// Explanation:
// intention -> inention (remove 't')
// inention -> enention (replace 'i' with 'e')
// enention -> exention (replace 'n' with 'x')
// exention -> exection (replace 'n' with 'c')
// exection -> execution (insert 'u')
// ```
//
// **Constraints:**
//
// - `0 <= word1.length, word2.length <= 500`
// - `word1` and `word2` consist of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <string>
#include <vector>

using namespace std;

// Use 2D-DP (Needleman-Wunsch Algorithm)
//
// If word1[i] == word2[j], dp[i+1,j+1] = dp[i,j]
// Otherwise,               dp[i+1,j+1] = min(dp[i,j], dp[i,j+1], dp[i+1,j]) + 1
// Note that dp[i,0] = i, dp[0,j] = j (only insertion / deletion).
class Solution {
 public:
  int minDistance(string word1, string word2) {
    int n1 = word1.size(), n2 = word2.size();

    // DP
    auto dp = vector(n1 + 1, vector(n2 + 1, 0));
    for (auto i = 0; i < n1; ++i) {
      dp[i + 1][0] = i + 1;
    }
    for (auto j = 0; j < n2; ++j) {
      dp[0][j + 1] = j + 1;
    }

    for (auto i = 0; i < n1; ++i) {
      for (auto j = 0; j < n2; ++j) {
        dp[i + 1][j + 1] = (word1[i] == word2[j]) ? dp[i][j] : min({dp[i][j], dp[i][j + 1], dp[i + 1][j]}) + 1;
      }
    }

    return dp[n1][n2];
  }
};

// Use 1D-DP (Needleman-Wunsch Algorithm)
class Solution2 {
 public:
  int minDistance(string word1, string word2) {
    int n1 = word1.size(), n2 = word2.size();

    // DP
    auto curr = vector(n2 + 1, 0);
    auto prev = vector(n2 + 1, 0);
    iota(curr.begin(), curr.end(), 0);

    for (auto i = 0; i < n1; ++i) {
      swap(curr, prev);
      curr[0] = i + 1;
      for (auto j = 0; j < n2; ++j) {
        curr[j + 1] = (word1[i] == word2[j]) ? prev[j] : min({prev[j], prev[j + 1], curr[j]}) + 1;
      }
    }

    return curr[n2];
  }
};
