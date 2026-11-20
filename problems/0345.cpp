// Source: https://leetcode.com/problems/reverse-vowels-of-a-string
// Title: Reverse Vowels of a String
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s`, reverse only all the vowels in the string and return it.
//
// The vowels are `'a'`, `'e'`, `'i'`, `'o'`, and `'u'`, and they can appear in both lower and upper cases, more than once.
//
// **Example 1:**
//
// ```
// Input: s = "IceCreAm"
// Output: "AceCreIm"
// Explanation:
// The vowels in `s` are `['I', 'e', 'e', 'A']`. On reversing the vowels, s becomes `"AceCreIm"`.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "leetcode"
// Output: "leotcede"
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 3 * 10^5`
// - `s` consist of **printable ASCII** characters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

using namespace std;

class Solution {
 public:
  string reverseVowels(string s) {
    int n = s.size();
    auto l = 0, r = n - 1;

    auto isVowel = [](char ch) -> bool {
      return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'A' || ch == 'E' || ch == 'I' ||
             ch == 'O' || ch == 'U';
    };

    while (l < r) {
      if (isVowel(s[l]) && isVowel(s[r])) {
        swap(s[l], s[r]);
        ++l, --r;
        continue;
      }

      if (!isVowel(s[l])) ++l;
      if (!isVowel(s[r])) --r;
    }

    return s;
  }
};
