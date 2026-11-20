// Source: https://leetcode.com/problems/smallest-palindromic-rearrangement-i
// Title: Smallest Palindromic Rearrangement I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **palindromic** string `s`.
//
// Return the **lexicographically smallest** palindromic permutation of `s`.
//
// **Example 1:**
//
// ```
// Input: s = "z"
// Output: "z"
// Explanation:
// A string of only one character is already the lexicographically smallest palindrome.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "babab"
// Output: "abbba"
// Explanation:
// Rearranging `"babab"` → `"abbba"` gives the smallest lexicographic palindrome.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "daccad"
// Output: "acddca"
// Explanation:
// Rearranging `"daccad"` → `"acddca"` gives the smallest lexicographic palindrome.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s` consists of lowercase English letters.
// - `s` is guaranteed to be palindromic.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <string>

using namespace std;

// Count
class Solution {
 public:
  string smallestPalindrome(const string &s) {
    auto freq = array<int, 128>();
    for (char ch : s) {
      ++freq[ch];
    }

    // Find odd letter
    char oddCh = '\0';
    for (char ch = 'a'; ch <= 'z'; ++ch) {
      if (freq[ch] % 2) {
        oddCh = ch;
        break;
      }
    }

    // Construct
    string ans;
    ans.reserve(s.size());
    for (char ch = 'a'; ch <= 'z'; ++ch) {
      ans.append(freq[ch] / 2, ch);
    }
    if (oddCh) ans.push_back(oddCh);
    for (char ch = 'z'; ch >= 'a'; --ch) {
      ans.append(freq[ch] / 2, ch);
    }

    return ans;
  }
};
