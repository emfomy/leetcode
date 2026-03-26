// Source: https://leetcode.com/problems/interleaving-string
// Title: Interleaving String
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given strings `s1`, `s2`, and `s3`, find whether `s3` is formed by an **interleaving** of `s1` and `s2`.
//
// An **interleaving** of two strings `s` and `t` is a configuration where `s` and `t` are divided into `n` and `m` <button>substrings</button> respectively, such that:
//
// - `s = s_1 + s_2 + ... + s_n`
// - `t = t_1 + t_2 + ... + t_m`
// - `|n - m| <= 1`
// - The **interleaving** is `s_1 + t_1 + s_2 + t_2 + s_3 + t_3 + ...` or `t_1 + s_1 + t_2 + s_2 + t_3 + s_3 + ...`
//
// **Note:** `a + b` is the concatenation of strings `a` and `b`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/09/02/interleave.jpg
//
// ```
// Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
// Output: true
// Explanation: One way to obtain s3 is:
// Split s1 into s1 = "aa" + "bc" + "c", and s2 into s2 = "dbbc" + "a".
// Interleaving the two splits, we get "aa" + "dbbc" + "bc" + "a" + "c" = "aadbbcbcac".
// Since s3 can be obtained by interleaving s1 and s2, we return true.
// ```
//
// **Example 2:**
//
// ```
// Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
// Output: false
// Explanation: Notice how it is impossible to interleave s2 with any other string to obtain s3.
// ```
//
// **Example 3:**
//
// ```
// Input: s1 = "", s2 = "", s3 = ""
// Output: true
// ```
//
// **Constraints:**
//
// - `0 <= s1.length, s2.length <= 100`
// - `0 <= s3.length <= 200`
// - `s1`, `s2`, and `s3` consist of lowercase English letters.

// **Follow up:** Could you solve it using only `O(s2.length)` additional memory space?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <string>
#include <vector>

using namespace std;

// 2D-DP
//
// Let DP[i][j] = true if s3[:(i+j)] can be form by s1[:i] and s2[:j].
//
// DP[0][0] = true
// DP[i][j] = (DP[i-1][j] AND s3[i+j-1] == s1[i-1])
//         OR (DP[i][j-1] AND s3[i+j-1] == s2[j-1])
class Solution {
  using Bool = uint8_t;

 public:
  bool isInterleave(const string &s1, const string &s2, const string &s3) {
    const int m = s1.size(), n = s2.size();

    // Guard
    if (s3.size() != m + n) return false;

    // DP
    auto dp = vector<vector<Bool>>(m + 1, vector<Bool>(n + 1, false));
    dp[0][0] = true;

    for (int j = 1; j <= n; ++j) {
      dp[0][j] = (dp[0][j - 1] && (s3[j - 1] == s2[j - 1]));
    }
    for (int i = 1; i <= m; ++i) {
      dp[i][0] = (dp[i - 1][0] && (s3[i - 1] == s1[i - 1]));
    }
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        dp[i][j] = (dp[i - 1][j] && (s3[i + j - 1] == s1[i - 1])) ||  //
                   (dp[i][j - 1] && (s3[i + j - 1] == s2[j - 1]));    //
      }
    }

    return dp[m][n];
  }
};

// 1D-DP
class Solution2 {
  using Bool = uint8_t;

 public:
  bool isInterleave(const string &s1, const string &s2, const string &s3) {
    const int m = s1.size(), n = s2.size();

    // Guard
    if (s3.size() != m + n) return false;

    // DP
    auto prev = vector<Bool>(n + 1, false);
    auto curr = vector<Bool>(n + 1, false);
    curr[0] = true;

    for (int j = 1; j <= n; ++j) {
      curr[j] = (curr[j - 1] && (s3[j - 1] == s2[j - 1]));
    }

    for (int i = 1; i <= m; ++i) {
      swap(curr, prev);
      curr[0] = (prev[0] && (s3[i - 1] == s1[i - 1]));
      for (int j = 1; j <= n; ++j) {
        curr[j] = (prev[j] && (s3[i + j - 1] == s1[i - 1])) ||    //
                  (curr[j - 1] && (s3[i + j - 1] == s2[j - 1]));  //
      }
    }

    return curr[n];
  }
};
