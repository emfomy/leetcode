// Source: https://leetcode.com/problems/count-the-number-of-special-characters-i
// Title: Count the Number of Special Characters I
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `word`. A letter is called **special** if it appears **both** in lowercase and uppercase in `word`.
//
// Return the number of **special** letters in `word`.
//
// **Example 1:**
//
// ```
// Input: word = "aaAbcBC"
// Output: 3
// Explanation:
// The special characters in `word` are `'a'`, `'b'`, and `'c'`.
// ```
//
// **Example 2:**
//
// ```
// Input: word = "abc"
// Output: 0
// Explanation:
// No character in `word` appears in uppercase.
// ```
//
// **Example 3:**
//
// ```
// Input: word = "abBCab"
// Output: 1
// Explanation:
// The only special character in `word` is `'b'`.
// ```
//
// **Constraints:**
//
// - `1 <= word.length <= 50`
// - `word` consists of only lowercase and uppercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <string>

using namespace std;

class Solution {
  using Bool = unsigned char;

 public:
  int numberOfSpecialChars(const string &word) {
    array<Bool, 128> chSet = {};
    for (char ch : word) chSet[ch] = true;

    int count = 0;
    for (char ch = 'a'; ch <= 'z'; ++ch) {
      count += chSet[ch] && chSet[ch - 'a' + 'A'];
    }

    return count;
  }
};
