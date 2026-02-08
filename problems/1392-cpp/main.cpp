// Source: https://leetcode.com/problems/longest-happy-prefix
// Title: Longest Happy Prefix
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A string is called a **happy prefix** if is a **non-empty** prefix which is also a suffix (excluding itself).
//
// Given a string `s`, return the **longest happy prefix** of `s`. Return an empty string `""` if no such prefix exists.
//
// **Example 1:**
//
// ```
// **Input:** s = "level"
// **Output:** "l"
// **Explanation:** s contains 4 prefix excluding itself ("l", "le", "lev", "leve"), and suffix ("l", "el", "vel", "evel"). The largest prefix which is also suffix is given by "l".
// ```
//
// **Example 2:**
//
// ```
// **Input:** s = "ababab"
// **Output:** "abab"
// **Explanation:** "abab" is the largest prefix which is also suffix. They can overlap in the original string.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s` contains only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <string>

using namespace std;

// Rolling Hash
class Solution {
  constexpr static int64_t M1 = 1e9 + 7;
  constexpr static int64_t M2 = 1e9 + 9;

  constexpr static int64_t B1 = 131;
  constexpr static int64_t B2 = 13331;

 public:
  string longestPrefix(string s) {
    int n = s.size();

    int maxLen = 0;
    int64_t pre1 = 0, pre2 = 0;
    int64_t suf1 = 0, suf2 = 0;
    int64_t B1i = 1, B2i = 1;  // B^i
    for (int i = 0; i < n - 1; ++i) {
      int j = n - i - 1;
      pre1 = (pre1 * B1 + s[i]) % M1;
      pre2 = (pre2 * B2 + s[i]) % M2;

      suf1 = (suf1 + s[j] * B1i) % M1;
      suf2 = (suf2 + s[j] * B2i) % M2;

      B1i = (B1i * B1) % M1;
      B2i = (B2i * B2) % M2;

      if (pre1 == suf1 && pre2 == suf2) maxLen = i + 1;
    }

    return s.substr(0, maxLen);
  }
};
