// Source: https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string
// Title: Find the Index of the First Occurrence in a String
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two strings `needle` and `haystack`, return the index of the first occurrence of `needle` in `haystack`, or `-1` if `needle` is not part of `haystack`.
//
// **Example 1:**
//
// ```
// **Input:** haystack = "sadbutsad", needle = "sad"
// **Output:** 0
// **Explanation:** "sad" occurs at index 0 and 6.
// The first occurrence is at index 0, so we return 0.
// ```
//
// **Example 2:**
//
// ```
// **Input:** haystack = "leetcode", needle = "leeto"
// **Output:** -1
// **Explanation:** "leeto" did not occur in "leetcode", so we return -1.
// ```
//
// **Constraints:**
//
// - `1 <= haystack.length, needle.length <= 10^4`
// - `haystack` and `needle` consist of only lowercase English characters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <cstring>
#include <string>

using namespace std;

// Built-in
class Solution {
 public:
  int strStr(string haystack, string needle) {  //
    return haystack.find(needle);
  }
};

// Double Rolling Hash (Robin-Karp)
//
// The hash is B^(l-1) s[0] + B^(l-2) s[1] + ... + B^0 s[l-1].
class Solution2 {
  constexpr static int64_t M1 = 1e9 + 7;  // modulo
  constexpr static int64_t M2 = 1e9 + 9;  // modulo

  constexpr static int64_t B1 = 131;    // base
  constexpr static int64_t B2 = 13331;  // base

  inline int64_t mod(int64_t x, int64_t m) {  //
    return ((x % m) + m) % m;
  }

 public:
  int strStr(string haystack, string needle) {
    int n = haystack.size(), l = needle.size();

    if (l == 0) return 0;
    if (n < l) return -1;

    // Compute B^l
    int64_t B1l = 1, B2l = 1;
    for (auto i = 0; i < l; ++i) {
      B1l = mod(B1l * B1, M1);
      B2l = mod(B2l * B2, M2);
    }

    // Init hashs
    int64_t hashH1 = 0, hashH2 = 0;  // hash of haystack [0, l)
    int64_t hashN1 = 0, hashN2 = 0;  // hash of needle
    for (auto i = 0; i < l; ++i) {
      hashN1 = mod(hashN1 * B1 + needle[i], M1);
      hashN2 = mod(hashN2 * B2 + needle[i], M2);

      hashH1 = mod(hashH1 * B1 + haystack[i], M1);
      hashH2 = mod(hashH2 * B2 + haystack[i], M2);
    }

    // Loop haystack [i, i+l)
    for (auto i = 0; i + l <= n; ++i) {
      // Compare
      if (hashH1 == hashN1 && hashH2 == hashN2) return i;

      // Shift, remove s[i] * B^l and add [i+l]
      if (i + l < n) {  // not end
        hashH1 = mod(hashH1 * B1 + haystack[i + l] - haystack[i] * B1l, M1);
        hashH2 = mod(hashH2 * B2 + haystack[i + l] - haystack[i] * B2l, M2);
      }
    }

    return -1;
  }
};
