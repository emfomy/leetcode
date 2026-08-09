// Source: https://leetcode.com/problems/find-the-lexicographically-smallest-valid-sequence
// Title: Find the Lexicographically Smallest Valid Sequence
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two strings `word1` and `word2`.
//
// A string `x` is called **almost equal** to `y` if you can change **at most** one character in `x` to make it identical to `y`.
//
// A sequence of indices `seq` is called **valid** if:
//
// - The indices are sorted in **ascending** order.
// - Concatenating the characters at these indices in `word1` in **the same** order results in a string that is **almost equal** to `word2`.
//
// Return an array of size `word2.length` representing the **lexicographically smallest** **valid** sequence of indices. If no such sequence of indices exists, return an **empty** array.
//
// **Note** that the answer must represent the lexicographically smallest array, **not** the corresponding string formed by those indices.
//
// **Example 1:**
//
// Input: word1 = "vbcca", word2 = "abc"
//
// Output: [0,1,2]
//
// Explanation:
//
// ```
// The lexicographically smallest valid sequence of indices is `[0, 1, 2]`:
// - Change `word1[0]` to `'a'`.
// - `word1[1]` is already `'b'`.
// - `word1[2]` is already `'c'`.
// ```
//
// **Example 2:**
//
// ```
// Input: word1 = "bacdc", word2 = "abc"
// Output: [1,2,4]
// Explanation:
// The lexicographically smallest valid sequence of indices is `[1, 2, 4]`:
// - `word1[1]` is already `'a'`.
// - Change `word1[2]` to `'b'`.
// - `word1[4]` is already `'c'`.
// ```
//
// **Example 3:**
//
// ```
// Input: word1 = "aaaaaa", word2 = "aaabc"
// Output: []
// Explanation:
// There is no valid sequence of indices.
// ```
//
// **Example 4:**
//
// ```
// Input: word1 = "abc", word2 = "ab"
// Output: [0,1]
// ```
//
// **Constraints:**
//
// - `1 <= word2.length < word1.length <= 3 * 10^5`
// - `word1` and `word2` consist only of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <string>
#include <vector>

using namespace std;

// Greedy
//
// The problem is equal to match word2 in word1 (as subsequence),
// but we have a free quota to choose a not-matching character.
// So the problem is: where should we use this quota.
//
// Here is a greedy idea:
// We loop i in word1. Say we already chose j indices.
// Now if word1[i] == word2[j], we can freely choose it.
// Otherwise, we might want to use the quota here (for lexicographically smallest).
// However, we must ensure that we don't need this quota later.
//
// Therefore, we use DP to speed up the process.
// Let DP[i] be the smallest j s.t. word2[j:] is a subsequence of word1[i:].
// (i.e. longest suffix of word2)
//
// DP[n] = m since word1[n:] is empty
// If DP[i+1] == 0, then DP[i] = 0 (i.e. word2 is already a subsequence).
// If word1[i] == word2[DP[i+1]-1], then DP[i] = DP[i+1] -1(i.e. we found a longer subsequence)
// Otherwise, DP[i] = DP[i+1] (keeping the subsequence)
//
// Now back to the greedy.
// If DP[i+1] <= j+1 (i.e. exists valid subsequence), we can use quota here.
class Solution {
 public:
  vector<int> validSequence(const string &word1, const string &word2) {
    const int n = word1.size(), m = word2.size();

    // DP
    auto dp = vector<int>(n + 1);
    dp[n] = m;
    for (int i = n - 1; i >= 0; --i) {
      if (dp[i + 1] > 0 && word1[i] == word2[dp[i + 1] - 1]) {
        dp[i] = dp[i + 1] - 1;
      } else {
        dp[i] = dp[i + 1];
      }
    }

    // Greedy
    auto ans = vector<int>(m);
    int j = 0;
    bool quota = true;  // still have quota
    for (int i = 0; i < n && j < m; ++i) {
      // Find matching, use it
      if (word1[i] == word2[j]) {
        ans[j++] = i;
        continue;
      }

      // Try to use quota here
      if (quota && dp[i + 1] <= j + 1) {
        ans[j++] = i;
        quota = false;
      }
    }

    // No solution
    if (j < m) return {};

    return ans;
  }
};
