// Source: https://leetcode.com/problems/valid-anagram
// Title: Valid Anagram
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two strings `s` and `t`, return `true` if `t` is an **anagram** of `s`, and `false` otherwise.
//
// An **anagram** is a word or phrase formed by rearranging the letters of a different word or phrase, using all the original letters exactly once.
//
// **Example 1:**
//
// ```
// Input: s = "anagram", t = "nagaram"
// Output: true
// ```
//
// **Example 2:**
//
// ```
// Input: s = "rat", t = "car"
// Output: false
// ```
//
// **Constraints:**
//
// - `1 <= s.length, t.length <= 5 * 10^4`
// - `s` and `t` consist of lowercase English letters.
//
// **Follow up:** What if the inputs contain Unicode characters? How would you adapt your solution to such a case?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <string>

using namespace std;

// Use counter
class Solution {
 public:
  bool isAnagram(string s, string t) {
    array<int, 26> sCounter;
    array<int, 26> tCounter;

    for (auto ch : s) {
      sCounter[ch - 'a']++;
    }
    for (auto ch : t) {
      tCounter[ch - 'a']++;
    }

    return sCounter == tCounter;
  }
};
