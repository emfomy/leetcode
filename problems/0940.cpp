// Source: https://leetcode.com/problems/distinct-subsequences-ii
// Title: Distinct Subsequences II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string s, return the number of **distinct non-empty subsequences** of `s`. Since the answer may be very large, return it **modulo** `10^9 + 7`.
// A **subsequence** of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., `"ace"` is a subsequence of `"abcde"` while `"aec"` is not.
//
// **Example 1:**
//
// ```
// Input: s = "abc"
// Output: 7
// Explanation: The 7 distinct subsequences are "a", "b", "c", "ab", "ac", "bc", and "abc".
// ```
//
// **Example 2:**
//
// ```
// Input: s = "aba"
// Output: 6
// Explanation: The 6 distinct subsequences are "a", "b", "ab", "aa", "ba", and "aba".
// ```
//
// **Example 3:**
//
// ```
// Input: s = "aaa"
// Output: 3
// Explanation: The 3 distinct subsequences are "a", "aa" and "aaa".
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 2000`
// - `s` consists of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <string>
#include <vector>

using namespace std;

// DP
//
// Let DP[i] be the number of distinct subseq of s[:i].
//
// DP[0] = 0 (empty string)
//
// If s[i] is distinct from all previous letters, then DP[i+1] = 2DP[i].
// (For each previous subseq, we can create a new subseq by appending s[i])
//
// If s[i] appears before, (say the last position is j),
// then DP[i+1] = 2DP[i] - DP[j].
// (Same as above, but exclude the subseq's only using letters before j).
class Solution {
  static constexpr int modulo = 1e9 + 7;

  inline int mod(int x) { return (x % modulo + modulo) % modulo; }

 public:
  int distinctSubseqII(const string &s) {
    const int n = s.size();
    auto dp = vector<int>(n + 1);
    auto seenDp = array<int, 128>();

    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
      char ch = s[i];
      dp[i + 1] = mod(dp[i] * 2 - seenDp[ch]);
      seenDp[ch] = dp[i];
    }

    return mod(dp.back() - 1);  // exclude DP[0] (empty string)
  }
};
