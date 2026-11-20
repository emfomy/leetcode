// Source: https://leetcode.com/problems/maximum-length-substring-with-two-occurrences
// Title: Maximum Length Substring With Two Occurrences
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s`, return the **maximum** length of a <button>substring</button>such that it contains at most two occurrences of each character.
//
// **Example 1:**
//
// ```
// Input: s = "bcbbbcba"
// Output: 4
// Explanation:
// The following substring has a length of 4 and contains at most two occurrences of each character: `"bcbbbcba"`.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "aaaa"
// Output: 2
// Explanation:
// The following substring has a length of 2 and contains at most two occurrences of each character: `"aaaa"`.
// ```
//
// **Constraints:**
//
// - `2 <= s.length <= 100`
// - `s` consists only of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <string>

using namespace std;

class Solution {
 public:
  int maximumLengthSubstring(const string& s) {
    const int n = s.size();
    auto count = array<int, 128>();

    int maxLen = 0;
    int l = 0;
    for (int r = 0; r < n; ++r) {  // [l, r]
      char ch = s[r];
      ++count[ch];
      while (count[ch] > 2) {
        --count[s[l++]];
      }

      maxLen = max(maxLen, r - l + 1);
    }

    return maxLen;
  }
};
