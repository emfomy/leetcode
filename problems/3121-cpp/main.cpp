// Source: https://leetcode.com/problems/count-the-number-of-special-characters-ii
// Title: Count the Number of Special Characters II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `word`. A letter`c` is called **special** if it appears **both** in lowercase and uppercase in `word`, and **every** lowercase occurrence of `c` appears before the **first** uppercase occurrence of `c`.
//
// Return the number of **special** letters in `word`.
//
// **Example 1:**
//
// ```
// Input: word = "aaAbcBC"
// Output: 3
// Explanation:
// The special characters are `'a'`, `'b'`, and `'c'`.
// ```
//
// **Example 2:**
//
// ```
// Input: word = "abc"
// Output: 0
// Explanation:
// There are no special characters in `word`.
// ```
//
// **Example 3:**
//
// ```
// Input: word = "AbBCab"
// Output: 0
// Explanation:
// There are no special characters in `word`.
// ```
//
// **Constraints:**
//
// - `1 <= word.length <= 2 * 10^5`
// - `word` consists of only lowercase and uppercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <cctype>
#include <string>

using namespace std;

// Scan 26 times
class Solution {
 public:
  int numberOfSpecialChars(const string &word) {
    int count = 0;
    for (char alpha = 'a'; alpha <= 'z'; ++alpha) {
      bool valid = true;
      bool hasLower = false;
      bool hasUpper = false;

      for (char ch : word) {
        if (ch == alpha) {
          hasLower = true;
          if (hasUpper) valid = false;
        } else if (ch == alpha - 'a' + 'A') {
          hasUpper = true;
        }
      }

      count += valid && hasLower && hasUpper;
    }

    return count;
  }
};

// Single scan
class Solution2 {
  using Bool = unsigned char;

 public:
  int numberOfSpecialChars(const string &word) {
    array<Bool, 26> invalid = {};
    array<Bool, 26> hasLower = {};
    array<Bool, 26> hasUpper = {};

    for (char ch : word) {
      if (islower(ch)) {
        hasLower[ch - 'a'] = true;
        if (hasUpper[ch - 'a']) invalid[ch - 'a'] = true;
      } else if (isupper(ch)) {
        hasUpper[ch - 'A'] = true;
      }
    }

    int count = 0;
    for (char ch = 0; ch < 26; ++ch) {
      count += !invalid[ch] && hasLower[ch] && hasUpper[ch];
    }

    return count;
  }
};
