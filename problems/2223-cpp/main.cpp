// Source: https://leetcode.com/problems/sum-of-scores-of-built-strings
// Title: Sum of Scores of Built Strings
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are **building** a string `s` of length `n` **one** character at a time, **prepending** each new character to the **front** of the string. The strings are labeled from `1` to `n`, where the string with length `i` is labeled `s_i`.
//
// - For example, for `s = "abaca"`, `s_1 == "a"`, `s_2 == "ca"`, `s_3 == "aca"`, etc.
//
// The **score** of `s_i` is the length of the **longest common prefix** between `s_i` and `s_n` (Note that `s == s_n`).
//
// Given the final string `s`, return the **sum** of the **score** of every `s_i`.
//
// **Example 1:**
//
// ```
// **Input:** s = "babab"
// **Output:** 9
// **Explanation:**
// For s_1 == "b", the longest common prefix is "b" which has a score of 1.
// For s_2 == "ab", there is no common prefix so the score is 0.
// For s_3 == "bab", the longest common prefix is "bab" which has a score of 3.
// For s_4 == "abab", there is no common prefix so the score is 0.
// For s_5 == "babab", the longest common prefix is "babab" which has a score of 5.
// The sum of the scores is 1 + 0 + 3 + 0 + 5 = 9, so we return 9.```
//
// **Example 2:**
//
// ```
// **Input:** s = "azbazbzaz"
// **Output:** 14
// **Explanation:**
// For s_2 == "az", the longest common prefix is "az" which has a score of 2.
// For s_6 == "azbzaz", the longest common prefix is "azb" which has a score of 3.
// For s_9 == "azbazbzaz", the longest common prefix is "azbazbzaz" which has a score of 9.
// For all other s_i, the score is 0.
// The sum of the scores is 2 + 3 + 9 = 14, so we return 14.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s` consists of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  long long sumScores(string s) {
    int n = s.size();

    // Loop through all i
    int64_t ans = 0;
    for (int i = 0; i < n; ++i) {
      int j;
      for (j = 0; j < n - i; ++j) {
        if (s[j] != s[i + j]) break;
      }
      ans += j;
    }

    return ans;
  }
};

// Rolling Hash + Prefix Sum + Binary Search
//
// First compute the hash of all the prefixs of s.
// We also compute all the power of the hash base.
// Note that the hash H[0, i) = s[i-1] + s[i-2]B + s[i-3]B^2 + ... + s[0]B^(i-1).
// H[i, j) = s[j-1] + s[j-2]B + s[j-3]B^2 + ... + s[i]B^(j-i-1).
//         = H[0, j) - H[0, i) * B^(j-i)
//
// Next for each i, we want find the maximum common prefix.
// Note that all prefix of the maximum common prefix is also a common prefix,
// so that we can use binary search to find it.
class Solution2 {
  constexpr static int64_t M1 = 1e9 + 7;
  constexpr static int64_t M2 = 1e9 + 9;

  constexpr static int64_t B1 = 131;
  constexpr static int64_t B2 = 13331;

  // Compute x mod m
  inline int64_t mod(int64_t x, int64_t m) { return ((x % m) + m) % m; }

 public:
  long long sumScores(string s) {
    int n = s.size();

    // Compute the hashs
    auto prefixHash1s = vector<int64_t>(n + 1, 0);
    auto prefixHash2s = vector<int64_t>(n + 1, 0);
    auto b1Powers = vector<int64_t>(n + 1, 1);
    auto b2Powers = vector<int64_t>(n + 1, 1);
    for (int i = 0; i < n; ++i) {
      prefixHash1s[i + 1] = mod(prefixHash1s[i] * B1 + s[i], M1);
      prefixHash2s[i + 1] = mod(prefixHash2s[i] * B2 + s[i], M2);
      b1Powers[i + 1] = mod(b1Powers[i] * B1, M1);
      b2Powers[i + 1] = mod(b2Powers[i] * B2, M2);
    }

    // Helper, check if [i, j) is a common prefix
    auto check = [&](int i, int j) -> bool {  //
      int l = j - i;
      auto hash1 = mod(prefixHash1s[j] - prefixHash1s[i] * b1Powers[l], M1);
      auto hash2 = mod(prefixHash2s[j] - prefixHash2s[i] * b2Powers[l], M2);
      return hash1 == prefixHash1s[l] && hash2 == prefixHash2s[l];
    };

    // Loop through all suffix
    int64_t ans = 0;
    for (int i = 0; i < n; ++i) {
      // check [i, j)
      // check(j=lo-1) = true, check(j=hi) = false
      int lo = i + 1, hi = n + 1;
      while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(i, mid)) {
          lo = mid + 1;
        } else {
          hi = mid;
        }
      }
      ans += lo - 1 - i;
    }

    return ans;
  }
};
