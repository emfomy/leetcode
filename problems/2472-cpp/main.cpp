// Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-palindrome-substrings
// Title: Maximum Number of Non-overlapping Palindrome Substrings
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` and a **positive** integer `k`.
//
// Select a set of **non-overlapping** substrings from the string `s` that satisfy the following conditions:
//
// - The **length** of each substring is **at least** `k`.
// - Each substring is a **palindrome**.
//
// Return the **maximum** number of substrings in an optimal selection.
//
// A **substring** is a contiguous sequence of characters within a string.
//
// **Example 1:**
//
// ```
// Input: s = "abaccdbbd", k = 3
// Output: 2
// Explanation: We can select the substrings underlined in s = "**aba**cc**dbbd**". Both "aba" and "dbbd" are palindromes and have a length of at least k = 3.
// It can be shown that we cannot find a selection with more than two valid substrings.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "adbcda", k = 2
// Output: 0
// Explanation: There is no palindrome substring of length at least 2 in the string.
// ```
//
// **Constraints:**
//
// - `1 <= k <= s.length <= 2000`
// - `s` consists of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <string_view>
#include <vector>

using namespace std;

// DP
//
// DP[i] is the the answer for s[i:].
// Loop i from right to left.
// For each i, we go right and find the first palindromes with length k.
//
// Note that since DP is increasing (from right to left),
// we always choose the shortest palindrome.
class Solution {
  bool isPalindrome(const string_view sv) {
    int n = sv.size();
    for (int l = 0, r = n - 1; l < r; ++l, --r) {
      if (sv[l] != sv[r]) return false;
    }
    return true;
  }

 public:
  int maxPalindromes(const string_view s, const int k) {
    const int n = s.size();
    auto dp = vector<int>(n + 1, 0);

    for (int i = n - 1; i >= 0; --i) {
      dp[i] = dp[i + 1];
      for (int j = i + k; j <= n; ++j) {
        if (isPalindrome(s.substr(i, j - i))) {
          dp[i] = max(dp[i], dp[j] + 1);
          break;
        }
      }
    }

    return dp[0];
  }
};

// DP + Rolling Hash
//
// Use rolling hash to check palindrome.
// We first compute the prefix hash for both direction.
// To check palindrome, we simply compare the hash for both direction.
//
// PreHash[0, i) = s[i-1] + s[i-2]B + s[i-3]B^2 + ...
// PreHash[i, j) = s[j-1] + ... + s[i]B^(j-i-1)
//               = PreHash[0, j) - PreHash[0, i) * B^(j-i)
//
// SufHash[i, n) = s[i] + s[i+1]B + s[i+2]B^2 + ...
// SufHash[i, j) = s[i] + ... + s[j-1]B^(j-i-1)
//               = SufHash[i, n) - SufHash[j, n) * B^(j-i)
class Solution2 {
  constexpr static int64_t M = 1e9 + 7;  // modulo
  constexpr static int64_t B = 13331;    // base

  int64_t mod(int64_t x) {
    return ((x % M) + M) % M;  //
  }

 public:
  int maxPalindromes(const string_view s, const int k) {
    const int n = s.size();

    // Hash
    auto bPows = vector<int64_t>(n + 1, 0);     // B^i
    auto preHashs = vector<int64_t>(n + 1, 0);  // hash of [0, i)
    auto sufHashs = vector<int64_t>(n + 1, 0);  // hash of [i, n)
    bPows[0] = 1;
    for (int i = 0; i < n; ++i) {
      bPows[i + 1] = mod(bPows[i] * B);
    }
    for (int i = 0; i < n; ++i) {
      preHashs[i + 1] = mod(preHashs[i] * B + s[i]);
    }
    for (int i = n - 1; i >= 0; --i) {
      sufHashs[i] = mod(sufHashs[i + 1] * B + s[i]);
    }

    // DP
    auto dp = vector<int>(n + 1, 0);
    for (int i = n - 1; i >= 0; --i) {
      dp[i] = dp[i + 1];
      for (int j = i + k; j <= n; ++j) {
        int64_t preHash = mod(preHashs[j] - preHashs[i] * bPows[j - i]);
        int64_t sufHash = mod(sufHashs[i] - sufHashs[j] * bPows[j - i]);
        if (preHash == sufHash) {
          dp[i] = max(dp[i], dp[j] + 1);
          break;
        }
      }
    }

    return dp[0];
  }
};
