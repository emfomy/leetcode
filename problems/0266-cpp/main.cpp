// Source: https://leetcode.com/problems/palindrome-permutation
// Title: Palindrome Permutation
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s`, return `true` if a permutation of the string could form a **palindrome** and `false` otherwise.
//
// A **palindrome** is a string that reads the same forward and backward.
//
// **Example 1:**
//
// ```
// Input: s = "code"
// Output: false
// ```
//
// **Example 2:**
//
// ```
// Input: s = "aab"
// Output: true
// ```
//
// **Example 3:**
//
// ```
// Input: s = "carerac"
// Output: true
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 5000`
// - `s` consists of only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  bool canPermutePalindrome(string s) {
    // Count chars
    auto counter = unordered_map<char, int>();
    for (auto c : s) {
      counter[c]++;
    }

    // Count odds
    auto odds = 0;
    for (auto [_, cnt] : counter) {
      if (cnt % 2 == 1) odds++;
    }

    return odds <= 1;
  }
};
