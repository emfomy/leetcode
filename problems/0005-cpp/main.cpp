// Source: https://leetcode.com/problems/longest-palindromic-substring
// Title: Longest Palindromic Substring
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s`, return the longest **palindromic substring** in `s`.
//
// A string is **palindromic** if it reads the same forward and backward.
// A **substring** is a contiguous non-empty sequence of characters within a string.
//
// **Example 1:**
//
// ```
// Input: s = "babad"
// Output: "bab"
// Explanation: "aba" is also a valid answer.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "cbbd"
// Output: "bb"
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 1000`
// - `s` consist of only digits and English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

using namespace std;

// O(n^2)
class Solution {
 public:
  string longestPalindrome(string s) {
    int n = s.size();
    string ans;

    for (auto i = 0; i < n; ++i) {
      // Odd substring
      for (auto l = i, r = i; l >= 0 && r < n && s[l] == s[r]; --l, ++r) {
        auto len = r - l + 1;
        if (len > ans.size()) {
          ans = s.substr(l, len);
        }
      }

      // Even substring
      for (auto l = i, r = i + 1; l >= 0 && r < n && s[l] == s[r]; --l, ++r) {
        auto len = r - l + 1;
        if (len > ans.size()) {
          ans = s.substr(l, len);
        }
      }
    }

    return ans;
  }
};
