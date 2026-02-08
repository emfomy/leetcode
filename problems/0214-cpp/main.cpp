// Source: https://leetcode.com/problems/shortest-palindrome
// Title: Shortest Palindrome
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s`. You can convert `s` to a **palindrome** by adding characters in front of it.
//
// Return the shortest palindrome you can find by performing this transformation.
//
// **Example 1:**
//
// ```
// **Input:** s = "aacecaaa"
// **Output:** "aaacecaaa"
// ```
//
// **Example 2:**
//
// ```
// **Input:** s = "abcd"
// **Output:** "dcbabcd"
// ```
//
// **Constraints:**
//
// - `0 <= s.length <= 5 * 10^4`
// - `s` consists of lowercase English letters only.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <string>

using namespace std;

// O(N^2), TLE
//
// We first find the longest palindrome in s starting from 0.
// Then copy and reverse the suffix to to the front.
class Solution {
 public:
  string shortestPalindrome(string s) {
    int n = s.size();

    // check if [0, r] is a palindrome
    auto check = [&](int r) -> bool {
      for (auto i = 0, j = r; i <= j; ++i, --j) {
        if (s[i] != s[j]) return false;
      }
      return true;
    };

    for (auto r = n - 1; r >= 0; --r) {
      if (check(r)) {
        auto s2 = s.substr(r + 1);  // copy
        reverse(s2.begin(), s2.end());
        return s2 + s;
      }
    }
    return "";  // unreachable
  }
};

// Rolling Hash
//
// We first find the longest palindrome in s starting from 0.
// Then copy and reverse the suffix to to the front.
//
// Use rolling hash to speed up string compare.
// We use double hash to avoid string compare as final check.
class Solution2 {
  constexpr static int64_t M1 = 1e9 + 7;  // modulo
  constexpr static int64_t B1 = 131;      // base

  constexpr static int64_t M2 = 1e9 + 7;  // modulo
  constexpr static int64_t B2 = 13331;    // base

 public:
  string shortestPalindrome(string s) {
    int n = s.size();

    // Find longest palindrome
    auto maxLen = 0;                 // palindrome length
    int64_t hashA1 = 0, hashA2 = 0;  // hashA = hash(s[0:r]) (inclusive)
    int64_t hashB1 = 0, hashB2 = 0;  // hashB = hash(s[r:0]) (inclusive)
    int64_t B1r = 1, B2r = 1;        // B^r
    for (auto r = 0; r < n; ++r) {
      hashA1 = (hashA1 + s[r] * B1r) % M1;
      hashA2 = (hashA2 + s[r] * B2r) % M2;

      hashB1 = (hashB1 * B1 + s[r]) % M1;
      hashB2 = (hashB2 * B2 + s[r]) % M2;

      B1r = (B1r * B1) % M1;
      B2r = (B2r * B2) % M2;

      if (hashA1 == hashB1 && hashA2 == hashB2) {
        maxLen = r + 1;
      }
    }

    // Answer
    auto s2 = s.substr(maxLen);  // copy
    reverse(s2.begin(), s2.end());
    return s2 + s;
  }
};
